/*

f n p =
  if p == 1 then 'a' + n - 1
  else if p <= 2 ^ (n - 1) then f (n - 1) (p - 1)
  else f (n - 1) (p - 2 ^ (n - 1))

*/

int pow2(int n)
{
  return 1 << n;
}

int f(int n, int p)
{
  if (1 == p)
    return 'a' + n;
  else if (p <= pow2(n - 1))
    return f(n - 1, p - 1);
  else
    return f(n - 1, p - pow2(n - 1));
}

int main()
{
  return 0;
}
