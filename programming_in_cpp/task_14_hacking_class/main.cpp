// Getting access to the Cls members, even though they are private
#include <iostream>
using namespace std;

struct Cls {
  Cls(char c, double d, int i) {
    this->c = c;
    this->d = d;
    this->i = i;
  }

 private:
  char c;
  double d;
  int i;
};

// Fake version of a Cls class (make it public)
struct ClsPubl {
  ClsPubl(char c, double d, int i);

 public:
  char c;
  double d;
  int i;
};

char &get_c(Cls &cls) {
  // Trick is to have similar struct (since they take space in memory in the
  // similar way)
  // Using that, you should cast to void *, then to required type
  void *void_ptr = (void *)(&cls);
  struct ClsPubl *fake_cls = (ClsPubl *)(void_ptr);
  return fake_cls->c;
}

double &get_d(Cls &cls) {
  void *void_ptr = (void *)(&cls);
  struct ClsPubl *fake_cls = (ClsPubl *)(void_ptr);
  return fake_cls->d;
}

int &get_i(Cls &cls) {
  void *void_ptr = (void *)(&cls);
  struct ClsPubl *fake_cls = (ClsPubl *)(void_ptr);
  return fake_cls->i;
}

int main() {
  Cls *cls = new Cls('c', 3.1415, 85);
  cout << get_c(*cls) << endl;
  cout << get_d(*cls) << endl;
  cout << get_i(*cls) << endl;

  return 0;
}