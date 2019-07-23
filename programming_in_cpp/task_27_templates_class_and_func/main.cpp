#include <cstddef>
#include <iostream>
using namespace std;

template <typename T>
class Array {
  size_t _size;
  T* _p;

 public:
  explicit Array(size_t size, const T& value = T()) : _size(size) {
    _p = (T*)new char[_size * sizeof(T)];
    for (size_t i = 0; i != _size; ++i) {
      new (_p + i) T(value);
    }
  }

  Array(const Array& a) : _size(a.size()) {
    _p = (T*)new char[_size * sizeof(T)];
    for (size_t i = 0; i != _size; ++i) {
      new (_p + i) T(a[i]);
    }
  }

  Array() {
    _size = 0;
    _p = 0;
  }

  ~Array() {
    for (size_t i = 0; i != _size; ++i) {
      _p[i].~T();
    }
    delete[](char*) _p;
  }

  Array& operator=(Array& other) {
    if (this != &other) Array(other).swap(*this);
    return *this;
  }

  void swap(Array& other) {
    std::swap(this->_size, other._size);
    std::swap(this->_p, other._p);
  }

  size_t size() const { return _size; }

  T& operator[](size_t i) { return _p[i]; }

  const T& operator[](size_t i) const { return _p[i]; }
};

template <typename T, typename Comp>
T minimum(Array<T>& data, Comp comp) {
  T min = data[0];
  size_t size = data.size();
  for (size_t i = 1; i != size; ++i)
    if (comp(data[i], min)) min = data[i];
  return min;
}

bool my_less(int a, int b) { return a < b; }

struct Greater {
  bool operator()(int a, int b) const { return b < a; }
};

int main() {
  Array<int> array(3, 8);
  array = array;
  array[1] = 3;
  Array<int> array2;
  cout << minimum(array, my_less) << endl;
  cout << minimum(array, Greater()) << endl;
}