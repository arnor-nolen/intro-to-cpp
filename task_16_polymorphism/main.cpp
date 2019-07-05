#include <iostream>
struct Foo {
  void say() const { std::cout << "Foo says: " << msg << "\n"; }

 protected:
  Foo(const char *msg) : msg(msg) {}

 private:
  const char *msg;
};

void foo_says(const Foo &foo) { foo.say(); }

struct Bar : Foo {
  Bar(const char *msg) : Foo(msg) {}
};

const Foo get_foo(const char *msg) {
  Bar bar = Bar(msg);
  return bar;
}

int main() { foo_says(get_foo("Hello!")); }