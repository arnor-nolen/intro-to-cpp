#include <iostream>
#include <typeindex>
#include <typeinfo>

struct Shape {};

struct Rectangle : Shape {};

struct Triangle : Shape {};

bool is_intersect_r_r(Shape* a, Shape* b);

bool is_intersect_r_t(Shape* a, Shape* b);

// Base - базовый класс иерархии
// Result - тип возвращаемого значения мультиметода
// Commutative - флаг, который показывает, что
// мультиметод коммутативный (т.е. f(x,y) = f(y,x)).
template <class Base, class Result, bool Commutative>
struct Multimethod2 {
  // устанавливает реализацию мультиметода
  // для типов t1 и t2 заданных через typeid
  // f - это функция или функциональный объект
  // принимающий два указателя на Base
  // и возвращающий значение типа Result
  void addImpl(... t1, ... t2, ... f) {}

  // проверяет, есть ли реализация мультиметода
  // для типов объектов a и b
  bool hasImpl(Base* a, Base* b) const {
    // возвращает true, если реализация есть
    // если операция коммутативная, то нужно
    // проверить есть ли реализация для b и а
    return ...;
  }

  // Применяет мультиметод к объектам
  // по указателям a и b
  Result call(Base* a, Base* b) const {
    // возвращает результат применения реализации
    // мультиметода к a и b
    return ...;
  }
};

int main() {
  // мультиметод для наследников Shape
  // возращающий bool и являющийся коммутативным
  Multimethod2<Shape, bool, true> is_intersect;

  // добавляем реализацию мультиметода для двух прямоугольников
  is_intersect.addImpl(typeid(Rectangle), typeid(Rectangle), is_intersect_r_r);

  // добавляем реализацию мультиметода для прямоугольника и треугольника
  is_intersect.addImpl(typeid(Rectangle), typeid(Triangle), is_intersect_r_t);

  // создаём две фигуры
  Shape* s1 = new Triangle();
  Shape* s2 = new Rectangle();

  // проверяем, что реализация для s1 и s2 есть
  if (is_intersect.hasImpl(s1, s2)) {
    // вызывается функция is_intersect_r_t(s2, s1)
    bool res = is_intersect.call(s1, s2);

    // Замечание: is_intersect_r_t ожидает,
    // что первым аргументом будет прямоугольник
    // а вторым треугольник, а здесь аргументы
    // передаются в обратном порядке.
    // ваша реализация должна самостоятельно
    // об этом позаботиться
  }

  return 0;
}