#include <iostream>
using namespace std;

struct Base {
  // Make the class polymorphic, otherwise won't work
  virtual void do_nothing() { return; }
};

struct Child : Base {};

template <class T> bool isSameObject(T const *p, T const *q) {
  return dynamic_cast<void const *>(p) == dynamic_cast<void const *>(q);
}

int main() {
  Child const A, B;
  Base const C, D;
  cout << isSameObject(&A, &A) << endl;
  cout << isSameObject(&A, &B) << endl;
  cout << isSameObject(&C, &C) << endl;
  cout << isSameObject(&C, &D) << endl;
  return 0;
}