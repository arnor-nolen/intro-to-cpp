#include <functional>
#include <iostream>
#include <map>
#include <typeindex>
#include <typeinfo>

struct Shape {
  virtual ~Shape(){};
};
struct Rectangle : Shape {};
struct Triangle : Shape {};

bool is_intersect_r_r(Shape *a, Shape *b) { return true; };
bool is_intersect_r_t(Shape *a, Shape *b) { return true; };

template <class Base, class Result, bool Commutative> struct Multimethod2 {
  void addImpl(std::type_index t1, std::type_index t2,
               std::function<Result(Base *a, Base *b)> f) {
    map_.insert({{t1, t2}, f});
  }

  bool hasImpl(Base *a, Base *b) const {
    auto pair = {std::type_index(typeid(*a)), std::type_index(typeid(*b))};
    bool swapped = false;
    if (findImpl(a, b, swapped) != map_.end())
      return true;
    return false;
  }

  Result call(Base *a, Base *b) const {
    bool swapped = false;
    auto func = findImpl(a, b, swapped)->second;
    if (!swapped)
      return func(a, b);
    return func(b, a);
  }

private:
  std::map<std::pair<std::type_index, std::type_index>,
           std::function<Result(Base *a, Base *b)>>
      map_;

  auto findImpl(Base *a, Base *b, bool &swapped) const -> decltype(map_.end()) {
    swapped = false;
    auto entry = map_.find({typeid(*a), typeid(*b)});
    auto entry_commutative = map_.find({typeid(*a), typeid(*b)});
    auto end = map_.end();
    if (entry != end) {
      return entry;
    } else if (Commutative) {
      if (entry_commutative != end) {
        swapped = true;
        return entry_commutative;
      }
    }
    return map_.end();
  }
};

int main() {
  Shape *s1 = new Triangle();
  Shape *s2 = new Rectangle();

  Multimethod2<Shape, bool, true> is_intersect;

  is_intersect.addImpl(typeid(Rectangle), typeid(Rectangle), is_intersect_r_r);
  is_intersect.addImpl(typeid(Rectangle), typeid(Triangle), is_intersect_r_t);

  bool intersect = is_intersect.hasImpl(s2, s1);
  if (intersect) {
    bool res = is_intersect.call(s2, s1);
    std::cout << res << std::endl;
  }
  std::cout << intersect << std::endl;

  return 0;
}