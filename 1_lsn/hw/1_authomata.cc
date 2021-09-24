/*
================Торговый автомат================

Одна фирма обслуживает автоматы по продаже чая и кофе. Стоимость стакана чая и кофе в автомате равна пяти
рублям. Автомат принимает монеты по 5 и 10 рублей, а также купюры в 10, 50 и 100 рублей. Когда покупателю
надо выдавать сдачу (т.е. когда пассажир бросил в автомат десятирублёвую монету или 10-, 50- или
100-рублёвую купюру), автомат выдаёт сдачу пятирублёвыми монетами; если же покупатель бросил в автомат
пятирублёвую монету, то автомат её сохраняет и может использовать для сдачи следующим покупателям. Ясно,
что, чтобы обеспечить возможность выдачи сдачи всем покупателям, может потребоваться изначально загрузить
в автомат некоторое количество пятирублёвых монет.

Сейчас автоматы проходят испытания с целью определить минимальное количество монет, которые надо загрузить
в автомат перед началом дня. Вам дан протокол одного из таких испытаний: известен порядок, в котором
покупатели оплачивали свои покупки различными монетами и купюрами. Определите, какое минимальное количество
пятирублёвых монет должно было изначально находиться в автомате, чтобы всем покупателям хватило сдачи.

================Input format================

В первой строке входных данных находится одно натуральное число N — количество покупок в автомате, которые
были совершены в ходе испытания 1 <= N <= 50000.

Во второй строке находятся N натуральных чисел, каждое из которых равно номиналу монеты или купюры, которую
использовал очередной покупатель для оплаты; каждый номинал может принимать одно из четырёх значений:
5, 10, 50 или 100.

================Output format================

Выведите одно число — минимальное количество пятирублёвых монет, которые надо было загрузить в автомат
изначально, чтобы всем покупателям хватило сдачи.

================Examples================

----------------Input----------------
3
10 5 100

----------------Output----------------
19

----------------Input----------------
3
5 5 10

*/

#include <iostream>
#include <vector>

int main() {
  std::vector<uint> bills{};
  size_t cup_num = 0;

  // read number of cups
  std::cin >> cup_num;
  bills.reserve(cup_num);

  // read all bills
  uint have5 = 0;
  uint debt5 = 0;

  for (size_t i = 0; i < cup_num; ++i) {
    uint val = 0;
    std::cin >> val;

    if (5 == val) {
      ++have5;
      continue;
    }

    val -= 5;
    while ((val > 0) && (have5 > 0)) {
      val -= 5;
      --have5;
    }

    debt5 += val / 5;
  }

  std::cout << debt5 << std::endl;
  return 0;
}
