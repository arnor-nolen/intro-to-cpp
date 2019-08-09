#include <iostream>

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

int main() {
  using primes = IntList<2, 3, 5, 7, 11, 13>;
  constexpr int head = primes::Head;
  using odd_primes = primes::Tail;

  using L1 = IntList<2, 3, 4>;
  using L2 = IntCons<1, L1>::type;
  using L3 = Generate<5>::type;

  std::cout << Length<L2>::value << " " << L2::Head << std::endl;
  std::cout << Length<L3>::value << " " << L3::Head << std::endl;

  return 0;
}