#include <iostream>
#include <string>
#include <utility>

template <class T>
void do_math() noexcept(noexcept(std::declval<T>() + std::declval<T>()) &&
                        std::is_nothrow_copy_assignable<T>::value &&
                        std::is_nothrow_copy_constructible<T>::value &&
                        std::is_nothrow_move_assignable<T>::value &&
                        std::is_nothrow_move_constructible<T>::value) {}

int main() {
  bool b1 = noexcept(do_math<int>());         // true
  bool b2 = noexcept(do_math<std::string>()); // false

  std::cout << b1 << std::endl << b2 << std::endl;

  return 0;
}