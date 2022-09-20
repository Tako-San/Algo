/*

MITM - Meet In The Middle

Задача: есть кучка камней, надо разбить на две кучи максимально близкого
размера.

деление задачи пополам
перебор
MITM

*/

#include <iostream>
#include <stdio.h>
#include <vector>

using T = unsigned long long;

std::pair<T, std::vector<int>> readW(unsigned N)
{
  T total = 0;
  std::vector<int> W(N);
  for (unsigned i = 0; i < N; i++)
  {
    std::cin >> W[i];
    total += W[i];
  }

  return {total, W};
}

T calcHeap(const std::vector<int> &W, T set)
{
  auto N = W.size();
  T heap = 0;
  for (unsigned i = 0; i < N; i++)
    heap += W[i] * ((set >> i) & 1);

  return heap;
}

int main()
{
  unsigned N = 0;
  std::cin >> N;
  auto [total, W] = readW(N);

  auto maxg = static_cast<T>(1) << N; // 2 ^ N
  auto min = static_cast<T>(1) << 62; // 2 ^ 62
  for (T g = 0; g < maxg; g++)
  {
    auto heap2 = calcHeap(W, g);
    auto heap1 = total - heap2;

    auto diff = (heap2 > heap1) ? heap2 - heap1 : heap1 - heap2;
    min = std::min(diff, min);
  }

  std::cout << min << std::endl;
}