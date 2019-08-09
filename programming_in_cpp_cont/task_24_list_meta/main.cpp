#include <iostream>

template <int... Integers> struct IntList;

template <int H, int... Integers> struct IntList<H, Integers...> {
  static const int Head = H;
  using Tail = IntList<Integers...>;
};

template <> struct IntList<> {};

int main() {
  using primes = IntList<2, 3, 5, 7, 11, 13>;
  constexpr int head = primes::Head;
  using odd_primes = primes::Tail;

  std::cout << head << std::endl;

  return 0;
}