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
template <Dimension<> D> struct Quantity {};

// -----End of code-----

using NumberQ = Quantity<Dimension<>>; // число без размерности
using LengthQ = Quantity<Dimension<1>>;          // метры
using MassQ = Quantity<Dimension<0, 1>>;         // килограммы
using TimeQ = Quantity<Dimension<0, 0, 1>>;      // секунды
using VelocityQ = Quantity<Dimension<1, 0, -1>>; // метры в секунду
using AccelQ =
    Quantity<Dimension<1, 0, -2>>; // ускорение, метры в секунду в квадрате
using ForceQ = Quantity<Dimension<1, 1, -2>>; // сила в ньютонах

int main() {

  LengthQ l{30000}; // 30 км
  TimeQ t{10 * 60}; // 10 минут
  // вычисление скорости
  VelocityQ v = l / t; // результат типа VelocityQ, 50 м/с

  AccelQ a{9.8}; // ускорение свободного падения
  MassQ m{80};   // 80 кг
  // сила притяжения, которая действует на тело массой 80 кг
  ForceQ f = m * a; // результат типа ForceQ

  return 0;
}