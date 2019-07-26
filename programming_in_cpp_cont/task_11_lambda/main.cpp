#include <iostream>

template <class F> void for_each_int(int *p, int *q, F f) {
  for (; p != q; ++p)
    f(*p);
}

auto square_fun = [](int &x) { x = x * x; };

int main() {
  int m[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  for (auto const &i : m)
    std::cout << i << " ";
  std::cout << std::endl;

  for_each_int(m, m + 10, square_fun);

  for (auto const &i : m)
    std::cout << i << " ";
  std::cout << std::endl;

  return 0;
}