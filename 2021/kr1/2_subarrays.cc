#include <algorithm>
#include <iostream>
#include <vector>

void do_stuff(std::vector<uint32_t> &V, int num)
{
  size_t left = 0;
  size_t right = 1;

  uint32_t sum = V[0];

  auto n = V.size();
  while (right < n)
  {
    if (sum < num)
      sum += V[right++];
  }
}

int main()
{
  size_t N = 0;
  size_t M = 0;

  std::cin >> N >> M;

  std::vector<uint32_t> V(N);
  for (size_t i = 0; i < N; ++i)
    std::cin >> V[i];

  std::vector<int> P(M);
  for (size_t i = 0; i < M; ++i)
    std::cin >> P[i];

  std::sort(P.begin(), P.end());

  for (auto elem : P)
    do_stuff(V, elem);

  return 0;
}
