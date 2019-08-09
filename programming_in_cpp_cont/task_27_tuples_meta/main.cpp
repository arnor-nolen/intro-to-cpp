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

int main() {
  using primes = IntList<2, 3, 5, 7, 11, 13>;
  constexpr int head = primes::Head;
  using odd_primes = primes::Tail;

  using L1 = IntList<2, 3, 4>;
  using L2 = IntCons<1, L1>::type;
  using L3 = Generate<5>::type;

  auto f = [](int x, double y, double z) { return x + y + z; };
  auto t = std::make_tuple(30, 5.0, 1.6);
  auto res = apply(f, t);

  std::cout << res << std::endl;

  return 0;
}