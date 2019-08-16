#include <iostream>
#include <tuple>

template <int... Integers> struct IntList;
template <int H, int... Integers> struct IntList<H, Integers...> {
  static const int Head = H;
  using Tail = IntList<Integers...>;
};
template <> struct IntList<> {};

template <typename IntList> struct Length {
  static const int value = 1 + Length<typename IntList::Tail>::value;
};
template <> struct Length<IntList<>> { static const int value = 0; };

template <int H, typename IntList> struct IntCons;
template <int H, int... Integers> struct IntCons<H, IntList<Integers...>> {
  using type = IntList<H, Integers...>;
};

template <int N, int I = 0> struct Generate {
  using type = typename IntCons<I, typename Generate<N - 1, I + 1>::type>::type;
};
template <int I> struct Generate<0, I> { using type = IntList<>; };

template <typename F, typename... Args,
          typename Idx = typename Generate<sizeof...(Args)>::type>
auto apply(const F &f, const std::tuple<Args...> &t)
    -> decltype(apply_(f, t, Idx())) {
  return apply_(f, t, Idx());
}
template <typename F, typename Tuple, int... Idx>
auto apply_(const F &f, const Tuple &t, const IntList<Idx...> &)
    -> decltype(f(std::get<Idx>(t)...)) {
  return f(std::get<Idx>(t)...);
}

template <int a, int b> struct Plus { static int const value = a + b; };

template <typename A, typename B, template <int, int> class F> struct Zip {
  using type = typename IntCons<
      F<A::Head, B::Head>::value,
      typename Zip<typename A::Tail, typename B::Tail, F>::type>::type;
};
template <template <int, int> class F> struct Zip<IntList<>, IntList<>, F> {
  using type = IntList<>;
};

template <int m = 0, int kg = 0, int s = 0, int A = 0, int K = 0, int mol = 0,
          int cd = 0>
using Dimension = IntList<m, kg, s, A, K, mol, cd>;

// -----Code is here-----
template <typename D> struct Quantity;
template <int... Integers> struct Quantity<IntList<Integers...>> {
  Quantity() : v(0){};
  explicit Quantity(double val) : v(val){};
  double value() const { return v; }
  double const v;
};

// Sum
template <int... Integers>
Quantity<IntList<Integers...>>
operator+(const Quantity<IntList<Integers...>> &lhs,
          const Quantity<IntList<Integers...>> &rhs) {
  return Quantity<IntList<Integers...>>(lhs.v + rhs.v);
}

// Subtraction
template <int... Integers>
Quantity<IntList<Integers...>>
operator-(const Quantity<IntList<Integers...>> &lhs,
          const Quantity<IntList<Integers...>> &rhs) {
  return Quantity<IntList<Integers...>>(lhs.v - rhs.v);
}

// Multiplication
template <int... Ints1, int... Ints2>
Quantity<IntList<(Ints1 + Ints2)...>>
operator*(const Quantity<IntList<Ints1...>> &lhs,
          const Quantity<IntList<Ints2...>> &rhs) {
  return Quantity<IntList<(Ints1 + Ints2)...>>(lhs.v * rhs.v);
}
template <int... Ints2>
Quantity<IntList<Ints2...>> operator*(const double &lhs,
                                      const Quantity<IntList<Ints2...>> &rhs) {
  return Quantity<IntList<Ints2...>>(lhs * rhs.v);
}
template <int... Ints1>
Quantity<IntList<Ints1...>> operator*(const Quantity<IntList<Ints1...>> &lhs,
                                      const double &rhs) {
  return Quantity<IntList<Ints1...>>(lhs.v * rhs);
}

// Division
template <int... Ints1, int... Ints2>
Quantity<IntList<(Ints1 - Ints2)...>>
operator/(const Quantity<IntList<Ints1...>> &lhs,
          const Quantity<IntList<Ints2...>> &rhs) {
  return Quantity<IntList<(Ints1 - Ints2)...>>(lhs.v / rhs.v);
}
template <int... Ints2>
Quantity<IntList<-Ints2...>> operator/(const double &lhs,
                                       const Quantity<IntList<Ints2...>> &rhs) {
  return Quantity<IntList<-Ints2...>>(lhs / rhs.v);
}
template <int... Ints1>
Quantity<IntList<Ints1...>> operator/(const Quantity<IntList<Ints1...>> &lhs,
                                      const double &rhs) {
  return Quantity<IntList<Ints1...>>(lhs.v / rhs);
}
// -----End of code-----

using NumberQ = Quantity<Dimension<>>;
using LengthQ = Quantity<Dimension<1>>;
using MassQ = Quantity<Dimension<0, 1>>;
using TimeQ = Quantity<Dimension<0, 0, 1>>;
using VelocityQ = Quantity<Dimension<1, 0, -1>>;
using AccelQ = Quantity<Dimension<1, 0, -2>>;
using ForceQ = Quantity<Dimension<1, 1, -2>>;

int main() {

  LengthQ l(30000);
  TimeQ t{10 * 60};
  TimeQ t2{20 * 60};
  auto t3 = t + t2;
  std::cout << t3.value() << " " << typeid(t3).name() << std::endl;
  auto t4 = t2 - t;
  std::cout << t4.value() << " " << typeid(t4).name() << std::endl;
  VelocityQ v = l / t;
  std::cout << v.value() << " " << typeid(v).name() << std::endl;

  AccelQ a{9.8};
  MassQ m{80};
  ForceQ f = m * a;
  std::cout << f.value() << " " << typeid(f).name() << std::endl;

  LengthQ l2{10000};
  auto l3 = 2.0 / l2;
  std::cout << l3.value() << " " << typeid(l3).name() << std::endl;

  return 0;
}