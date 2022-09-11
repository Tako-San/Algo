#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <list>

void hit(std::vector<int> &hps, size_t p, size_t q)
{
  auto fst = hps.front() - p;
  std::pop_heap(hps.begin(), hps.end());
  hps.pop_back();

  for (auto cur = hps.begin(), end = hps.end(); cur != end; ++cur)
    *cur -= q;

  hps.push_back(fst);
  std::push_heap(hps.begin(), hps.end());
}

int main()
{
  size_t n = 0;
  size_t p = 0;
  size_t q = 0;

  std::cin >> n >> p >> q;

  std::vector<int> hps(n);
  for (size_t i = 0; i < n; ++i)
    std::cin >> hps[i];

  std::make_heap(hps.begin(), hps.end());

  size_t count = 0;
  while (hps.front() > 0)
    hit(hps, p, q), ++count;

  std::cout << count << std::endl;

  return 0;
}
