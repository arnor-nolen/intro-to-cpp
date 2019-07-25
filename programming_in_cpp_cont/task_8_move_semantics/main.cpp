#include <iostream>

template <class T> struct Array {

  explicit Array(size_t size, const T &value = T()) : size_(size) {
    data_ = (T *)new char[size_ * sizeof(T)];
    for (size_t i = 0; i != size_; ++i) {
      new (data_ + i) T(value);
    }
  }
  explicit Array(size_t size = 0) : size_(size) { data_ = nullptr; }

  Array(Array const &a) : size_(a.size()) {
    data_ = (T *)new char[size_ * sizeof(T)];
    for (size_t i = 0; i != size_; ++i) {
      new (data_ + i) T(a[i]);
    }
  }

  Array &operator=(Array const &other) {
    if (this != &other) {
      Array(other).swap(*this);
    }
    return *this;
  }

  void swap(Array &other) {
    std::swap(this->size_, other.size_);
    std::swap(this->data_, other.data_);
  }

  ~Array() {
    for (size_t i = 0; i != size_; ++i) {
      data_[i].~T();
    }
    delete[](char *) data_;
  }

  size_t size() const { return size_; }
  T &operator[](size_t i) { return data_[i]; }
  T const &operator[](size_t i) const { return data_[i]; }

  // Here goes the code
  Array(Array &&other) : Array() {
    std::cout << "Move constructor called!" << std::endl;
    swap(other);
  }
  Array &operator=(Array &&other) {
    std::cout << "Move assignment called!" << std::endl;
    swap(other);
    return *this;
  }

private:
  size_t size_;
  T *data_;
};

// For convenience
template <typename T>
std::ostream &operator<<(std::ostream &out, Array<T> &array) {
  size_t size = array.size();
  out << "Size: " << size << ", Data: ";
  for (size_t i = 0; i != size; ++i) {
    out << array[i] << " ";
  }
  return out;
}

int main() {
  Array<char> a(5, 'c');
  auto b = a;

  // Gets optimized by the compiler to auto c(std::move(b));
  auto c = std::move(b);
  Array<char> d;
  d = std::move(b);

  std::cout << "A. " << a << std::endl;
  std::cout << "B. " << b << std::endl;
  std::cout << "C. " << c << std::endl;
  std::cout << "D. " << d << std::endl;

  return 0;
}