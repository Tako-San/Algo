/*

MITM - Meet In The Middle

Задача: есть кучка камней, надо разбить на две кучи максимально близкого
размера.

деление задачи пополам
перебор
MITM

*/

#include <algorithm>
#include <concepts>
#include <iostream>
#include <limits>
#include <span>
#include <vector>

using T = uint32_t;

template <std::unsigned_integral U> U pow2(size_t pow)
{
  return static_cast<U>(1) << pow;
}

T readW(unsigned N, std::span<int> W)
{
  T total = 0;
  for (unsigned i = 0; i < N; i++)
  {
    std::cin >> W[i];
    total += W[i];
  }

  return total;
}

T calcHeap(std::span<int> W, T set)
{
  auto N = W.size();
  T heap = 0;
  for (unsigned i = 0; i < N; i++)
    heap += W[i] * ((set >> i) & 1);

  return heap;
}

void getSums(std::span<int> W, T total, std::span<T> sums)
{
  auto N = W.size();
  /* 2 ^ (N - 1), because we may calc only half */
  auto maxg = pow2<T>(N - 1);

  for (T g = 0; g < maxg; g++)
  {
    auto heap = calcHeap(W, g);
    sums[2 * g] = heap;
    sums[2 * g + 1] = total - heap;
  }

  std::sort(sums.begin(), sums.end());
}

/* MITM - Meet In The Middle */
T mitm(std::span<T> s1, std::span<T> s2, T total)
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
  auto N2 = N - N1;

  std::vector<int> W(N);
  std::span W1{W.begin(), W.begin() + N1};
  std::span W2{W.begin() + N1, W.end()};

  auto total1 = readW(N1, W1);
  auto total2 = readW(N2, W2);

  auto twoPowN1 = pow2<size_t>(N1);
  auto twoPowN2 = pow2<size_t>(N2);
  std::vector<T> sums(twoPowN1 + twoPowN2);

  std::span sums1{sums.begin(), sums.begin() + twoPowN1};
  std::span sums2{sums.begin() + twoPowN1, sums.end()};

  getSums(W1, total1, sums1);
  getSums(W2, total2, sums2);

  std::cout << mitm(sums1, sums2, total1 + total2) << std::endl;
  return 0;
}
