#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <vector>

template <class Iterator> size_t count_permutations(Iterator p, Iterator q) {
  using T = typename std::iterator_traits<Iterator>::value_type;
  std::vector<T> local(p, q);
  std::copy(p, q, local.begin());
  auto begin = local.begin();
  auto end = local.end();
  std::sort(begin, end);
  size_t permutations = std::adjacent_find(begin, end) == end;
  while (std::next_permutation(begin, end)) {
    if (std::adjacent_find(begin, end) == end)
      ++permutations;
  }
  return permutations;
}

int main() {
  std::array<const int, 3> a1 = {3, 2, 1};
  size_t c1 = count_permutations(a1.begin(), a1.end()); // 6
  std::cout << c1 << std::endl;

  std::array<int, 5> a2 = {1, 2, 3, 4, 4};
  size_t c2 = count_permutations(a2.begin(), a2.end()); // 36
  std::cout << c2 << std::endl;

  return 0;
}