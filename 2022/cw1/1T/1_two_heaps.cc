/*

MITM - Meet In The Middle

Задача: есть кучка камней, надо разбить на две кучи максимально близкого
размера.

деление задачи пополам
перебор
MITM

*/

#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using T = uint64_t;

std::pair<T, std::vector<int>> readW(unsigned N)
{
  T total = 0;
  std::vector<int> W(N);
  for (unsigned i = 0; i < N; i++)
  {
    std::cin >> W[i];
    total += W[i];
  }

  return {total, std::move(W)};
}

T calcHeap(const std::vector<int> &W, T set)
{
  auto N = W.size();
  T heap = 0;
  for (unsigned i = 0; i < N; i++)
    heap += W[i] * ((set >> i) & 1);

  return heap;
}

std::vector<T> getSums(const std::vector<int> &W, T total)
{
  auto N = W.size();
  /* 2 ^ (N - 1), because we may calc only half */
  auto maxg = static_cast<T>(1) << (N - 1);

  std::vector<T> sums{};
  sums.reserve(N);
  for (T g = 0; g < maxg; g++)
  {
    auto heap = calcHeap(W, g);
    sums.push_back(heap);
    sums.push_back(total - heap);
  }

  std::sort(sums.begin(), sums.end());
  return sums;
}

/* MITM - Meet In The Middle */
T mitm(const std::vector<T> &s1, const std::vector<T> &s2, T total)
{
  /* from small to large */
  auto cur1 = s1.begin();
  auto end1 = s1.end();

  /* from large to small */
  auto cur2 = s2.rbegin();
  auto end2 = s2.rend();

  auto half1 = total / 2;
  auto half2 = total - half1;
  auto minDiff = std::numeric_limits<T>::max();
  while (cur1 != end1 && cur2 != end2)
  {
    auto sum = *cur1 + *cur2;
    if (sum < half1)
    {
      minDiff = std::min(minDiff, (total - sum) - sum);
      ++cur1;
    }
    else if (sum > half2)
    {
      minDiff = std::min(minDiff, sum - (total - sum));
      ++cur2;
    }
    else
    {
      return half2 - half1;
    }
  }

  return minDiff;
}

int main()
{
  unsigned N = 0;
  std::cin >> N;

  auto N1 = N / 2;
  auto [total1, W1] = readW(N1);

  auto N2 = N - N1;
  auto [total2, W2] = readW(N2);

  auto sums1 = getSums(W1, total1);
  auto sums2 = getSums(W2, total2);

  std::cout << mitm(sums1, sums2, total1 + total2) << std::endl;
}
