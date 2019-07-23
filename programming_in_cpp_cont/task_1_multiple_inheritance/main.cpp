#include <iostream>

struct Base {};

struct D1 : Base {};

struct D2 : Base {
  D2() : a(10) {}
  int a;
};

struct D3 : D1, D2 {};

Base const *D1BaseToD2Base(Base const *base) {
  D1 *temp_d1 = (D1 *)base;
  D3 *temp_d3 = (D3 *)temp_d1;
  D2 *temp_d2 = (D2 *)temp_d3;
  Base *temp_base = (Base *)temp_d2;
  return temp_base;
}

int main() {
  D3 d3;
  Base *ptr = (D1 *)&d3;
  Base *ptra = 0;

  ptra = (Base *)D1BaseToD2Base(ptr);
  std::cout << ((D2 const *)ptra)->a << std::endl;

  return 0;
}