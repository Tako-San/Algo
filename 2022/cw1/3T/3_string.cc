/*

f n p =
  if p == 1 then 'a' + n - 1
  else if p <= 2 ^ (n - 1) then f (n - 1) (p - 1)
  else f (n - 1) (p - 2 ^ (n - 1))

*/

#include <iostream>

int pow2(int n)
{
  return 1 << n;
}

int f(int n, int p)
{
  if (p <= 0)
    return 'a' + n;
  else if (p < pow2(n))
    return f(n - 1, p - 1);
  else
    return f(n - 1, p - pow2(n));
}

int main()
{
  int level = 0;
  int from = 0;
  int to = 0;

  std::cin >> level >> from >> to;
  --level;
  --from;

  for (int i = from; i < to; ++i)
    std::cout << static_cast<char>(f(level, i));

  std::cout << std::endl;
  return 0;
}
