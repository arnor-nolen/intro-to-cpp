#include <iostream>
using namespace std;

struct ICloneable {
  virtual ICloneable* clone() const = 0;
  virtual ~ICloneable() {}
};

template <typename T>
struct ValueHolder : ICloneable {
  T data_;
  ValueHolder(const T& data) : data_(data) {}
  ValueHolder* clone() const { return new ValueHolder(data_); }
};

int main() {
  ValueHolder<int> v(5);
  cout << v.data_ << endl;
  ValueHolder<int>* s = v.clone();
  cout << s->data_ << endl;
}