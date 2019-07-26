#include <iostream>
#include <string>
#include <utility>

template <typename F, typename... Args>
auto apply(F func, Args &&... args)
    -> decltype(func(std::forward<Args>(args)...)) {
  return func(std::forward<Args>(args)...);
};

int main() {
  auto fun = [](std::string a, std::string const &b) { return a += b; };

  std::string s("world!");
  // First argument uses rvalue
  // Second argument uses lvalue
  s = apply(fun, std::string("Hello, "), s);

  std::cout << s << std::endl;

  return 0;
}