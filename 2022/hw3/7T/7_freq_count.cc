/*

================================ Подсчёт частот ===============================

На вход подаётся строка, состоящая из букв A-Z. Необходимо вывести все буквы,
которые встречаются в строке в порядке убывания частот вместе с частотой. В
случае равенства частот первой должна идти буква, которая встречается в алфавите
раньше.

================================= Input format ================================

Строка из букв A-Z

================================ Output format ================================

L_1 C_1

...

L_k C_k

где L_i - буква, входящая с строку, C_i - число вхожданий буквы в строку.

================================== Examples ===================================

------- Input --------
ABRACADABRA

------- Output -------
A 5
B 2
R 2
C 1
D 1

*/

#include <algorithm>
#include <array>
#include <iostream>
#include <string>

using FreqArrElem = std::pair<unsigned, char>;
using FreqArr = std::array<FreqArrElem, 26>;

int main()
{
  std::string input{};
  std::cin >> input;

  FreqArr fa{};
  std::for_each(fa.begin(), fa.end(),
                [c = 'A'](auto &e) mutable { e.second = c++; });

  for (auto &c : input)
    fa[c - 'A'].first++;

  std::sort(fa.begin(), fa.end(), [](const auto &fae1, const auto &fae2) {
    if (fae1.first != fae2.first)
      return fae1.first > fae2.first;
    return fae1.second < fae2.second;
  });

  for (const auto &p : fa)
    if (p.first > 0)
      std::cout << p.second << ' ' << p.first << std::endl;

  return 0;
}
