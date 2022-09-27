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
