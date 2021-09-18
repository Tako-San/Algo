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

    while (val > 0) {
      val -= 5;
      ++debt5;
    }
  }

  std::cout << debt5 << std::endl;
  return 0;
}