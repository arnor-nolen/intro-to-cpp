#include <iostream>
#include <list>
#include <thread>
#include <vector>

template <typename IterT, typename F1, typename F2>
auto map_reduce(IterT p, IterT q, const F1 &f1, const F2 &f2,
                const size_t threads) -> decltype(f1(*p)) {
  using return_type = decltype(f1(*p));
  size_t distance = std::distance(p, q);
  size_t thread_distance = distance / threads;
  std::vector<std::thread> promises;
  std::vector<return_type> results;
  results.resize(threads);
  size_t thread_id = 0;
  size_t thread_size = 0;
  IterT thread_start = p;

  auto chunk_map_reduce = [&f1, &f2](IterT p, IterT q) {
    auto result = f1(*p);
    while (++p != q)
      result = f2(result, f1(*p));
    return result;
  };

  while (thread_id != threads - 1) {
    ++p;
    if (++thread_size == thread_distance) {
      promises.push_back(std::thread(
          [&results, thread_id, thread_start, p, &chunk_map_reduce]() {
            results[thread_id] = chunk_map_reduce(thread_start, p);
          }));
      ++thread_id;
      thread_size = 0;
      thread_start = p;
    }
  }
  promises.push_back(
      std::thread([&results, thread_id, thread_start, q, &chunk_map_reduce]() {
        results[thread_id] = chunk_map_reduce(thread_start, q);
      }));

  promises[0].join();
  return_type result = results[0];
  for (size_t i = 1; i != promises.size(); ++i) {
    promises[i].join();
    result = f2(result, results[i]);
  }
  return result;
}

int main() {
  std::list<int> l = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  auto sum = map_reduce(
      l.begin(), l.end(), [](int i) { return i; }, std::plus<int>(), 3);
  auto has_even = map_reduce(
      l.begin(), l.end(), [](int i) { return i % 2 == 0; },
      std::logical_or<bool>(), 4);

  std::cout << sum << " " << has_even << std::endl;

  return 0;
}