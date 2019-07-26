#include <iostream>
#include <tuple>

template <int T, int U, typename V>
auto to_pair(V tuple)
    -> decltype(std::make_pair(std::get<T>(tuple), std::get<U>(tuple))) {
  return std::make_pair(std::get<T>(tuple), std::get<U>(tuple));
}

int main() {
  auto t = std::make_tuple(0, 3.5, "Hello");
  std::pair<double, char const *> p = to_pair<1, 2>(t);
  std::cout << p.first << std::endl;
  std::cout << p.second << std::endl;
  return 0;
}