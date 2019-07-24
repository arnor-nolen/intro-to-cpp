#include <iostream>
#include <string>

template <typename T, typename U>
bool compare(T const &a, T const &b, U (T::*mptr)() const) {
  U l = (a.*mptr)();
  U r = (b.*mptr)();
  if (l < r) {
    return true;
  }
  return false;
}

int main() {
  std::string s1("Elf");
  std::string s2("Archer");

  std::cout << compare(s1, s2, &std::string::size) << std::endl; // true
  std::cout << compare(s1, s1, &std::string::size) << std::endl; // false
  return 0;
}
