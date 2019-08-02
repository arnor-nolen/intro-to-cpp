#include <algorithm>
#include <iostream>
#include <vector>

template <class FwdIt> FwdIt remove_nth(FwdIt p, FwdIt q, size_t n) {
  size_t pos = 0;
  return std::remove_if(p, q, [&n, &pos](decltype(*p)) { return pos++ == n; });
}

int main() {
  std::vector<int> v = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  v.erase(remove_nth(v.begin(), v.end(), 5), v.end());
  v.erase(remove_nth(v.begin(), v.end(), 3), v.end());

  for (auto &i : v)
    std::cout << i << std::endl;

  return 0;
}