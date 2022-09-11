/*
================Пересечение двух множеств================


В массивах A размером N и B размером M значения строго возрастают, Требуется
найти пересечение этих массивов.

2 <= N,M <= 100000. Элементы массива не превосходят по абсолютной величине
100000000;

================Examples================

----------------Input----------------
5
5
1 3 4 5 7
2 4 6 7 9

----------------Output----------------
4 7

*/

#include <iostream>
#include <vector>

int main()
{
  size_t size1 = 0;
  size_t size2 = 0;

  std::cin >> size1;
  std::cin >> size2;

  std::vector<int32_t> inp1(size1);
  for (size_t i = 0; i < size1; ++i)
    std::cin >> inp1[i];

  std::vector<int32_t> inp2(size1);
  for (size_t i = 0; i < size1; ++i)
    std::cin >> inp2[i];

  size_t i1 = 0, i2 = 0;
  while ((i1 < size1) && (i2 < size2))
  {
    if (inp1[i1] == inp2[i2])
    {
      std::cout << inp1[i1] << " ";
      ++i1, ++i2;
    }
    else if (inp1[i1] > inp2[i2])
      ++i2;
    else
      ++i1;
  }

  std::cout << std::endl;
  return 0;
}
