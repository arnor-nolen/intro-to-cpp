#include <cstddef>  // size_t
#include <cstring>  // strlen, strcpy
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

  void append(String &other) {
    char *new_str = new char[this->size + other.size + 1];
    memcpy(new_str, this->str, this->size);
    strcpy(new_str + size, other.str);
    delete[] this->str;
    this->str = new_str;
    this->size += other.size;
  }

  size_t size;
  char *str;
};

int main() {
  String s = String(8, 'f');
  String s2 = String("append");
  s.append(s2);
  cout << s.str << endl;
  cout << s.size << endl;
  return 0;
}