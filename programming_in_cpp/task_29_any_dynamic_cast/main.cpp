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

class Any {
  ICloneable* vh_;

 public:
  Any() {}

  template <typename T>
  Any(T value) : vh_(new ValueHolder<T>(value)) {}

  Any(const Any& other) {
    if (other.vh_) {
      vh_ = other.vh_->clone();
    }
  }

  ~Any() { delete vh_; }

  Any& operator=(Any const& other) {
    if (other.vh_ && (this != &other)) {
      delete vh_;
      vh_ = other.vh_->clone();
    }
    return *this;
  }

  template <typename T>
  T* cast() {
    ValueHolder<T>* ref = dynamic_cast<ValueHolder<T>*>(vh_);
    if (ref) return &ref->data_;
    return 0;
  }
};

int main() {
  ValueHolder<int> v(5);
  cout << v.data_ << endl;
  ValueHolder<int>* s = v.clone();
  cout << s->data_ << endl;

  Any empty;
  cout << empty.cast<int>() << endl;  // Pointer is set to 0
  Any any1(10);
  cout << *any1.cast<int>() << endl;  // Can access value as usual
  Any any2(any1);
  cout << *any2.cast<int>() << endl;
  empty = any1;
  cout << *empty.cast<int>() << endl;  // Copy constructor
  empty = 0;
  cout << *empty.cast<int>() << endl;
}
