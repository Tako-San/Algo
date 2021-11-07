#include <iostream>
#include <set>
#include <string>

int get_pow_of_10(int num)
{
  int pow10 = 1;
  while (pow10 * 10 <= num)
    pow10 *= 10;
  return pow10;
}

int get_pos(int K, int pow10)
{
  int pos = 0;
  while (pow10 >= 1)
  {
    pos += (K - pow10 + 1);
    pow10 /= 10;
    K /= 10;
  }
  return pos;
}

int main()
{
  int K = 0;
  int N = 0;
  std::cin >> N >> K;

  int pow10 = get_pow_of_10(K);
  int pos = get_pos(K, pow10);

  if (K != pow10)
    while (true)
    {
      pow10 *= 10;

      if (pow10 > N)
        break;

      K *= 10;
      if (N <= K)
      {
        pos += (N - pow10 + 1);
        break;
      }
      else
        pos += (K - pow10);
    }

  std::cout << pos << std::endl;
  return 0;
}
