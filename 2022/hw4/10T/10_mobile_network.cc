/*

================================ Сотовая связь ================================

В городе имеется несколько операторов мобильной связи, каждый из которых
располагает несколькими вышками. У каждой вышки свои координаты и своя зона
уверенного приёма. Абонент находится в точке с заданными координатами. Требуется
определить количество операторов мобильной связи в городе и определить, для
скольких вышек у абонента, находящегося в данной точке, имеется устойчивая
связь.

================================= Input format ================================

В первой строке входного файла содержится целое число N(1 <= N <= 10000) —
количество базовых станций.

Далее следует N пар строк, в первой строке пары содержится имя оператора, во
второй - два целых числа с координатами станции X_i и Y_i
(−10000 <= Xi,Yi <= 10000), за которыми следует целочисленный радиус уверенного
приёма Ri(1 <= R <= 10000).

В последней строке — координаты абонента X_a и Y_a.

Названия операторов - строки символов, не содержащие пробелов и состоящие из
букв латинского алфавита и цифр.

================================ Output format ================================

В первой строке выходного файла нужно вывести количество операторов K, K⩽1000.

В следующих K строках требуется вывести название оператора (в порядке их
появления во входном файле) и через пробел количество базовых станций, доступных
для абонента.

================================== Examples ===================================

---------- Input ----------
8
Merizon -7 -5 2
K-Mobile -3 -5 4
BTT -2 -4 2
WarpLine -1 -4 5
Telephone -4 -6 2
BTT -1 -6 4
Near2 -6 -2 4
Merizon 7 7 6
3 5

---------- Output ---------
6
Merizon 1
K-Mobile 0
BTT 0
WarpLine 0
Telephone 0
Near2 0

---------- Input ----------
5
op2
0 3 1
op1
-6 9 0
op2
-7 6 3
op1
-9 1 2
op3
-2 -1 3
4 3

---------- Output ---------
3
op2 0
op1 0
op3 0

*/

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

struct Tower
{
  int r;
  int x;
  int y;

  bool cover(int x_, int y_)
  {
    return (x - x_) * (x - x_) + (y - y_) * (y - y_) < r * r;
  }
};

struct Elem
{
  size_t idx = 0;
  std::vector<Tower> towers;
};

int main()
{
  size_t N = 0;
  std::cin >> N;

  std::unordered_map<std::string, Elem> nameToIndex{};
  for (size_t i = 0; i < N; ++i)
  {
    std::string name{};
    int r = 0;
    int x = 0;
    int y = 0;

    std::cin >> name >> x >> y >> r;

    if (nameToIndex.find(name) == nameToIndex.end())
    {
      auto size = nameToIndex.size();
      nameToIndex[name].idx = size;
    }

    nameToIndex[name].towers.emplace_back(r, x, y);
  }

  int x = 0;
  int y = 0;
  std::cin >> x >> y;

  std::vector<std::pair<std::string, size_t>> res(nameToIndex.size());

  for (auto &elem : nameToIndex)
  {
    auto idx = elem.second.idx;
    res[idx].first = elem.first;

    auto &counter = res[idx].second;
    for (auto &tower : elem.second.towers)
      if (tower.cover(x, y))
        ++counter;
  }

  std::cout << nameToIndex.size() << std::endl;
  for (const auto &pair : res)
    std::cout << pair.first << " " << pair.second << std::endl;

  return 0;
}

/*

Мысли по решению.

Сортировать по координатам и радиусу мы ничего не будем. Это не нужно.

Завести мапу:
ключ - название оператора
значение - порядковый номер, список с параметрами вышек



*/
