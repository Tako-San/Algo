#include <iostream>

char get_sym(size_t strnum, size_t pos) {
  if (0 == pos)
    return 'a' + strnum;

  size_t sublen = 1ull << strnum;
  size_t new_pos = (pos < sublen) ? (pos - 1) : (pos - sublen);
  return get_sym(strnum - 1, new_pos);
}

int main() {
  size_t strnum = 0, beg = 0, end = 0;

  std::cin >> strnum >> beg >> end;
  for (size_t i = beg; i <= end; ++i)
    std::cout << get_sym(strnum, i);

  std::cout << std::endl;
  return 0;
}
