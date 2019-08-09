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

int main() {
  using primes = IntList<2, 3, 5, 7, 11, 13>;
  constexpr int head = primes::Head;
  using odd_primes = primes::Tail;

  std::cout << Length<primes>::value << std::endl;

  return 0;
}