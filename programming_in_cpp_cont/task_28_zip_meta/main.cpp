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

int main() {
  using L1 = IntList<1, 2, 3, 4, 5>;
  using L2 = IntList<1, 3, 7, 7, 2>;

  using L3 = Zip<L1, L2, Plus>::type; // IntList<2, 5, 10, 11, 7>

  std::cout << Length<L3>::value << " " << L3::Head << std::endl;

  return 0;
}
