#include <algorithm>
#include <iostream>

struct Rational {
  Rational(int numerator = 0, int denominator = 1)
      : numerator_(numerator), denominator_(denominator){};

  void add(Rational rational) {
    numerator_ =
        numerator_ * rational.denominator_ + rational.numerator_ * denominator_;
    denominator_ *= rational.denominator_;
  }

  void sub(Rational rational) {
    numerator_ =
        numerator_ * rational.denominator_ - rational.numerator_ * denominator_;
    denominator_ *= rational.denominator_;
  }

  void mul(Rational rational) {
    numerator_ *= rational.numerator_;
    denominator_ *= rational.denominator_;
  }

  void div(Rational rational) {
    numerator_ *= rational.denominator_;
    denominator_ *= rational.numerator_;
  }

  void neg() { numerator_ = -numerator_; }

  void inv() { std::swap(numerator_, denominator_); }

  double to_double() const { return numerator_ / (double)denominator_; }

  Rational operator+() const { return *this; }

  Rational operator-() const { return Rational(-numerator_, denominator_); }

  Rational &operator+=(Rational const &rational) {
    add(rational);
    return *this;
  }

  Rational &operator-=(Rational const &rational) {
    sub(rational);
    return *this;
  }

  Rational &operator*=(Rational const &rational) {
    mul(rational);
    return *this;
  }

  Rational &operator/=(Rational const &rational) {
    div(rational);
    return *this;
  }

 private:
  int numerator_;
  int denominator_;
};

int main() {
  Rational r1(1, 2);
  Rational r2(1, 3);
  Rational r3(5);

  // Compiler is implicitly calling constructor Rational(3, 1)
  std::cout << (r3 += 3).to_double() << std::endl;
  std::cout << (r3 -= -r1).to_double() << std::endl;
  std::cout << (r3 *= r1).to_double() << std::endl;
  std::cout << (r3 /= r1).to_double() << std::endl;
}