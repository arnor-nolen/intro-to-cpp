#include <array>
#include <future>
#include <iostream>
#include <list>

template <typename IterT, typename F1, typename F2>
auto calculate(IterT p, IterT q, F1 f1, F2 f2) -> decltype(f1(*p)) {
  auto result = f1(*p);
  while (++p != q)
    result = f2(result, f1(*p));
  return result;
}

template <typename IterT, typename F1, typename F2>
using return_type = F1(*IterT);
auto map_reduce(IterT p, IterT q, F1 f1, F2 f2, size_t threads) -> return_type {
  size_t distance = std::distance(p, q);
  size_t thread_distance = distance / threads + 1;
  std::array<std::future<return_type>> result_array[distance];
  size_t i = 0;
  while (p != q) {
    if (true)
      auto promise = std::async(std::launch::async, calculate<IterT, F1, F2>, p,
                                q, f1, f2);
    ++i;
    ++p;
  }

  return_type result;
  // Change to f2
  for (auto &i : result_array) {
    result += result_array[i].get();
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