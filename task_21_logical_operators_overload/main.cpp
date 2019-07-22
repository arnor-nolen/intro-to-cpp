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

  int get_numerator() const
  {
    return numerator_;
  }

  int get_denominator() const
  {
    return denominator_;

  }

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

Rational operator+(Rational left, Rational const &right) {
  return left += right;
}

Rational operator-(Rational left, Rational const &right) {
  return left -= right;
}

Rational operator*(Rational left, Rational const &right) {
  return left *= right;
}

Rational operator/(Rational left, Rational const &right) {
  return left /= right;
}

bool operator==(Rational const &left, Rational const &right) {
  return !(left.get_numerator() * right.get_denominator() 
    - left.get_denominator() * right.get_numerator());
}

bool operator!=(Rational const &left, Rational const &right) {
  return !(left == right);
}

bool operator<(Rational const &left, Rational const &right) {
  return left.get_numerator() * right.get_denominator() 
    < left.get_denominator() * right.get_numerator(); 
}

bool operator>(Rational const &left, Rational const &right) {
  return right < left;
}

bool operator<=(Rational const &left, Rational const &right) {
  return !(left > right);
}

bool operator>=(Rational const &left, Rational const &right) {
  return !(left < right);
}

int main() {
  Rational r1(1, 2);
  Rational r2(1, 3);
  Rational r3(5);

  std::cout << (r3 < 3) << std::endl;
  std::cout << (r3 > -r1) << std::endl;
  std::cout << (r3 <= r1) << std::endl;
  std::cout << (r3 >= 5) << std::endl;
}