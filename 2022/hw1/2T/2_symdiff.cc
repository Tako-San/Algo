/*
==================Симметрическая разность множеств==================

Симметрическая разность множеств — множество элементов, входящих строго в одно
из множеств-операндов.

==================Input format==================

На вход подаётся последовательность чисел в диапазоне от 1 до 2000000000,
разделённых пробелами и заканчивающаяся нулём — ограничителем
последовательности, не входящим в множество. Все эти элементы образуют множество
A, то есть, среди нет одинаковых пар. После разделителя подаются элементы
множества B, тоже завершающиеся нулём, не входящим в множество.

==================Output format==================

На выход программы нужно вывести симметрическую разность множеств A и B в
порядке возрастания элементов. Элементы выходного множества должны быть
разделены пробелами. Для сортировки допустим любой алгоритм.

==================Examples==================

------------------Input------------------
1 2 3 4 5 0 1 7 5 8 0

------------------Output------------------
2 3 4 7 8

------------------Input------------------
1 2 6 8 7 3 0 4 1 6 2 3 9 0

------------------Output------------------
4 7 8 9
*/

#include <iostream>
#include <map>

using ElemT = uint32_t;
using ChunkT = uint32_t;
using Set = std::map<size_t, ChunkT>;

constexpr size_t ChunkSize = 8 * sizeof(ChunkT);

size_t chunkNum(ElemT elem)
{
  return elem / static_cast<ElemT>(ChunkSize);
}

size_t posInChunk(ElemT elem)
{
  return elem % static_cast<ElemT>(ChunkSize);
}

bool in(const Set &set, ElemT elem)
{
  auto chunkIt = set.find(chunkNum(elem));
  if (set.end() == chunkIt)
    return false;

  return (chunkIt->second >> posInChunk(elem)) & 1;
}

void readSet(Set &set)
{
  ElemT elem = 0;
  do
  {
    std::cin >> elem;
    set[chunkNum(elem)] ^= 1 << posInChunk(elem);
  } while (0 != elem);
}

void printChunk(size_t pos, ChunkT chunk)
{
  auto inChunk = [chunk](ChunkT elem) { return (chunk >> elem) & 1; };
  for (ChunkT i = 0, end = ChunkSize; i < end; ++i)
    if (inChunk(i))
      std::cout << (i + pos * ChunkSize) << " ";
}

int main()
{
  Set set{};

  readSet(set);
  readSet(set);

  for (const auto [pos, chunk] : set)
    printChunk(pos, chunk);

  return 0;
}
