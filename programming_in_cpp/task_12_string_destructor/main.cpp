#include <cstddef>  // size_t
#include <cstring>  // strlen, strcpy
#include <iostream>
using namespace std;

// Trying out google style guides
struct String {
  String(size_t n, char c) {
    this->str = new char[n + 1];
    char* moving_str = this->str;
    for (size_t i = 0; i < n; i++) {
      *moving_str = c;
      moving_str++;
    }
    *moving_str = '\0';
    this->size = n;
  }
  ~String() { delete[] this->str; }
  size_t size;
  char* str;
};

int main() {
  String s = String(8, 'f');
  cout << s.str << endl;
  cout << s.size << endl;
  return 0;
}