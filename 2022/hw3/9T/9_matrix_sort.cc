/*

============================= Сортировка матрицы =============================

Если можно сравнивать строки, почему бы нельзя было сравнивать и матрицы, то
есть двумерные массивы? Для простоты положим, что операция сравнения определена
только для матриц с одинаковым количеством строк и столбцов.

Пронумеруем элементы матрицы слева направо и сверху вниз, например, матрица 3*4
будет пронумерована так: 1 2 3 4 5 6 7 8 9 10 11 12

Сравнение матриц заключается в следующем: сравниваются первые элементы. Если
один из них больше, то больше и соответствующая матрица. Если они равны, то
берётся второй элемент и т. д. Такое сравнение называется лексикографическим.

Вам дана матрица из N строк и M столбцов, 3⩽N,M⩽500, состоящая из различных
целых чисел от 1 до 231-1.

Разрешается переставлять произвольное количество раз любые две строки или любые
два столбца. Ваша задача получить такими перестановками лексикографически
наименьшую матрицу и вывести её.

================================ Input format ================================

N M
A11 A12 ... A1M
A21 A22 ... A2M
...
AN1 AN2 ... ANM

================================ Output format ===============================

Лексикографически наименьшая матрица из всех возможных после произвольного
количества перестановок строк и столбцов.

================================== Examples ==================================

---------- Input ----------
3 3
4 9 2
3 5 7
8 1 6

---------- Output ---------
1 6 8
5 7 3
9 2 4

---------- Input ----------
4 4
16 3 2 13
5 10 11 8
9 6 7 12
4 15 14 1

---------- Output ---------
1 4 14 15
8 5 11 10
12 9 7 6
13 16 2 3

*/

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
