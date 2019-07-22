#include <algorithm> // swap
#include <cstddef>   // size_t
#include <cstring>   // strlen, strcpy
#include <iostream>
using namespace std;

struct String {

  String(const char *str = "") {
    size_t size = strlen(str);
    this->size = size;
    this->str = new char[size + 1];
    strcpy(this->str, str);
  }

  String(size_t n, char c) {
    this->str = new char[n + 1];
    char *moving_str = this->str;
    for (size_t i = 0; i < n; i++) {
      *moving_str = c;
      moving_str++;
    }
    *moving_str = '\0';
    this->size = n;
  }

  ~String() { delete[] this->str; }

  String(const String &other) : size(other.size), str(new char[size + 1]) {
    for (size_t i = 0; i < size + 1; ++i) {
      *(str + i) = *(other.str + i);
    }
  }

  String &operator=(const String &other) {
    if (this != &other)
      String(other).swap(*this);
    return *this;
  }

  void swap(String &other) {
    std::swap(this->size, other.size);
    std::swap(this->str, other.str);
  }

  void append(String &other) {
    char *new_str = new char[this->size + other.size + 1];
    memcpy(new_str, this->str, this->size);
    strcpy(new_str + size, other.str);
    delete[] this->str;
    this->str = new_str;
    this->size += other.size;
  }

  struct StringProxy {
    StringProxy(char *str, int i) : str(str), i(i) {}

    String operator[](int j) const {
      char substr[j - i + 1];
      memcpy(substr, str + i, j - i);
      substr[j - i] = '\0';
      return String(substr);
    }

    char *str;
    int i;
  };

  StringProxy operator[](int i) const { return StringProxy(this->str, i); }

  size_t size;
  char *str;
};

int main() {
  String s = String("append");
  String s1 = s[2][4];

  // Unsafe, s[3] is now broken!
  // cout << s[3] << endl;
  cout << s1.str << endl;
  cout << s1.size << endl;
  return 0;
}