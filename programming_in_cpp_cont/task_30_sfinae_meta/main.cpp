#include <iostream>
#include <string>
#include <type_traits>

template <typename T, size_t (T::*)() const = &T::size>
size_t get_size(const T &arg) {
  return arg.size();
}

template <typename T, const size_t T::* = &T::size>
size_t get_size(const T &arg) {
  return arg.size;
}

int main() {
  // Doesn't compile on MinGW for some reason
  std::string s{"Hello"};
  size_t s_size = get_size(s);
  std::cout << s_size << std::endl;

  struct CustomStruct {
    size_t size;
  };

  CustomStruct x{10};
  size_t x_size = get_size(x);
  std::cout << x_size << std::endl;
  return 0;
}