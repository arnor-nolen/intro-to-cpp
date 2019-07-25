#include <iostream>
#include <ostream>
#include <typeinfo>

void print_values(std::ostream &os) {}

template <typename T, typename... Args>
void print_values(std::ostream &os, T value, Args... args) {
  os << typeid(value).name() << ": " << value << std::endl;
  print_values(os, args...);
}

int main() {
  print_values(std::cout, 0, 3.5, "Hello");
  print_values(std::cout);
  return 0;
}