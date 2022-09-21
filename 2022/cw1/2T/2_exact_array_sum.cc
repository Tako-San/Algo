#include <iostream>
#include <numeric>
#include <vector>

void readArray(std::vector<uint32_t> &v, uint32_t size)
{
  v.resize(size);
  for (auto &elem : v)
    std::cin >> elem;
}

void printInterval(const std::vector<uint32_t> &v, uint32_t p)
{
  auto beg = v.begin();
  auto end = v.end();

  for (auto fst = beg, snd = beg; fst != end;)
  {
    auto val = std::accumulate(fst, snd, static_cast<uint32_t>(0));
    if (val < p)
    {
      if (snd == end)
        break;
      ++snd;
    }
    else if (val > p)
      ++fst;
    else
    {
      std::cout << std::distance(beg, fst) + 1 << " "
                << std::distance(beg, snd) + 1 << std::endl;
      return;
    }
  }

  std::cout << "Not found" << std::endl;
}

int main()
{
  uint32_t N = 0;
  uint32_t M = 0;

  std::cin >> N;
  std::cin >> M;

  std::vector<uint32_t> V{};
  readArray(V, N);

  std::vector<uint32_t> P{};
  readArray(P, M);

  for (auto p : P)
    printInterval(V, p);

  return 0;
}
