#include <iostream>

struct Point {
  constexpr Point(double x, double y) : x(x), y(y) {}

  double x = 0;
  double y = 0;
};

constexpr Point const operator+(Point const &a, Point const &b) {
  return Point(a.x + b.x, a.y + b.y);
}

constexpr Point const operator-(Point const &a, Point const &b) {
  return Point(a.x - b.x, a.y - b.y);
}

constexpr double const operator*(Point const &a, Point const &b) {
  return a.x * b.x + b.y * a.y;
}

int main() {
  Point a(3, 5);
  Point b(2, 4);
  auto c = a + b;
  std::cout << c.x << " " << c.y << std::endl;

  auto d = a * b;
  std::cout << d << std::endl;

  return 0;
}