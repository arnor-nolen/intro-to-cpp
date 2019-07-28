#include <cstddef>
#include <iostream>
#include <list>

template <class It> size_t max_increasing_len(It p, It q) {
  size_t s = 0, tmp = 1;
  for (; p != q;) {
    auto p_prev = p++;
    if (p != q && *p_prev < *p)
      ++tmp;
    else {
      s = s < tmp ? tmp : s;
      tmp = 1;
    }
  }
  return s;
}

int main() {
  std::list<int> const l1 = {7, 8, 9, 4, 5, 6, 1, 2, 3, 4};
  // 4, corresponding to 1,2,3,4
  size_t len1 = max_increasing_len(l1.begin(), l1.end());
  std::cout << len1 << std::endl;

  std::list<int> const l2 = {-3, -2, -1, 0, 0, 1, 2, 3, 4, 5};
  // 6, corresponding to 0,1,2,3,4,5
  size_t len2 = max_increasing_len(l2.begin(), l2.end());
  std::cout << len2 << std::endl;

  std::list<int> const l3 = {2};
  // 1
  size_t len3 = max_increasing_len(l3.begin(), l3.end());
  std::cout << len3 << std::endl;
  return 0;
}