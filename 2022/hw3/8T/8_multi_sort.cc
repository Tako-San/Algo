/*

======================== Сортировка по многим полям ========================

В базе данных хранится N записей, вида (Name,a1,a2,...,ak) — во всех записях
одинаковое число параметров.

На вход задачи подаётся приоритет полей — перестановка на числах 1,...,k —
записи нужно вывести в соответствии с этим приоритетом. В случае, если приоритет
полей таков: 3 4 2 1, то это следует воспринимать так: приоритет значений из 3
колонки самый высокий, приоритет значений из колонки 4 ниже, приоритет значений
из колонки 2 ещё ниже, а приоритет значений из колонки 1 самый низкий.

================================ Input format ===============================

N (1 <= N <= 1000)

k (1 <= k <= 10)

p1 p2 ... pk (перестановка на k числах, разделитель пробел)

N строк вида

Name a1 a2 ... ak (разделитель — пробел)

=============================== Output format ===============================

N строк с именами согласно приоритету

================================= Examples ==================================

---------- Input ----------
4
4
3 4 2 1
A 7 2 6 5
B 6 4 4 7
C 1 5 6 6
D 3 6 4 7

---------- Output ---------
C
A
D
B

*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct Elem
{
  std::string name;
  std::vector<unsigned> fields;
};

int main()
{
  size_t N = 0;
  size_t k = 0;
  std::cin >> N >> k;

  std::vector<unsigned> priors{}; // vector of ind
  priors.reserve(k);
  for (size_t i = 0; i < k; ++i)
  {
    unsigned tmp{};
    std::cin >> tmp;
    priors.push_back(--tmp);
  }

  std::vector<Elem> elems(N);
  for (auto &e : elems)
  {
    std::cin >> e.name;
    e.fields.resize(k);
    for (auto &fe : e.fields)
      std::cin >> fe;
  }

  std::sort(elems.begin(), elems.end(), [&priors, k](auto &lhs, auto &rhs) {
    for (size_t i = 0; i < k; ++i)
      if (auto idx = priors[i]; lhs.fields[idx] != rhs.fields[idx])
        return lhs.fields[idx] > rhs.fields[idx];
    return false;
  });

  for (auto &e : elems)
    std::cout << e.name << std::endl;
  std::cout << std::endl;

  return 0;
}
