/*
============================Последовательность строк============================

Последовательность строк формируется следующим образом:

* Первая строка состоит из цифры 1.
* Каждая из последующих строк формируется из номера строки, записанного в виде
последовательности десятичных цифр, за которым дописана предыдущая строка и
затем перевёрнутая предыдущая строка.

Вот несколько первых строк:

1
211
3211112
432111122111123
5432111122111123321111221111234

Заметьте, что десятая строка начнётся с символов 10, одиннадцатая — с символов
11 и так далее. Ваша задача заключается в том, чтобы по заданному номеру строки
и номеру её элемента вывести символ, стоящий в ней на указанном месте.

===========================Input format===========================
N M

P1 P2 ... PM

Ограничения:

1<=N<=30

1<=M<=100000

1<=Pi<=length(string).

Нумерация строк и символов в строках начинается с единицы.

===========================Output format===========================

M символов, не разделённых пробелами, соответствующие позициям Pi.

===========================Examples===========================

---------------------------Input---------------------------
5 5
2 4 6 8 10

---------------------------Output---------------------------
42112

*/

#include <iostream>
#include <vector>

size_t prev_str_len(size_t strnum)
{
  if (strnum < 9)
    return (1ull << strnum) - 1;

  return (1ull << strnum) - 1 + (1ull << (strnum - 9)) - 1;
}

int get_sym(size_t strnum, size_t pos)
{
  size_t strnum_len = (strnum < 9) ? 1 : 2;

  if (pos == 0)
  {
    if (strnum_len == 1)
      return 1 + strnum;

    return (strnum + 1) / 10;
  }

  if ((pos == 1) && (strnum_len == 2))
    return (strnum + 1) % 10;

  size_t sublen = prev_str_len(strnum);
  size_t new_pos = (pos < (sublen + strnum_len))
                       ? (pos - strnum_len)
                       : (2 * sublen + strnum_len - pos - 1);
  return get_sym(strnum - 1, new_pos);
}

int main()
{
  size_t strnum = 0, numnum = 0;

  std::cin >> strnum >> numnum;

  std::vector<int> idxs(numnum);
  for (size_t i = 0; i < numnum; ++i)
    std::cin >> idxs[i];

  for (auto idx : idxs)
    std::cout << get_sym(strnum - 1, idx - 1);

  std::cout << std::endl;

  return 0;
}
