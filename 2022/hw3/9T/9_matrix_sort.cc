#include <algorithm>
#include <iostream>
#include <limits>
#include <tuple>
#include <vector>

using Matrix = std::vector<std::vector<uint32_t>>;

void print(const Matrix &mx)
{
  for (const auto &line : mx)
  {
    for (const auto &elem : line)
      std::cout << elem << " ";
    std::cout << std::endl;
  }
}

void transpose(Matrix &mx)
{
  auto rowNum = mx.size();
  auto colNum = mx[0].size();

  Matrix res(colNum);
  for (size_t i = 0; i < colNum; i++)
  {
    res[i].resize(rowNum);
    for (size_t j = 0; j < rowNum; j++)
      res[i][j] = mx[j][i];
  }

  mx = std::move(res);
}

int main()
{
  size_t N = 0;
  size_t M = 0;
  std::cin >> N;
  std::cin >> M;

  Matrix mx(N);
  std::tuple min{std::numeric_limits<uint32_t>::max(), size_t{}, size_t{}};
  for (size_t i = 0; i < N; i++)
  {
    mx[i].resize(M);
    for (size_t j = 0; j < M; j++)
    {
      std::cin >> mx[i][j];
      auto &[minVal, minY, minX] = min;
      if (mx[i][j] < minVal)
      {
        minVal = mx[i][j];
        minY = i;
        minX = j;
      }
    }
  }

  std::sort(mx.begin(), mx.end(),
            [minX = std::get<2>(min)](const auto &lhs, const auto &rhs) {
              return lhs[minX] < rhs[minX];
            });

  transpose(mx);

  std::sort(mx.begin(), mx.end(),
            [](const auto &lhs, const auto &rhs) { return lhs[0] < rhs[0]; });

  transpose(mx);
  print(mx);

  return 0;
}
