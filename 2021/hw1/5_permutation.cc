#include <array>
#include <iostream>
#include <list>
#include <numeric>
#include <vector>

constexpr std::array<size_t, 21> FACT{1,
                                      1,
                                      2,
                                      6,
                                      24,
                                      120,
                                      720,
                                      5040,
                                      40320,
                                      362'880,
                                      3'628'800,
                                      39'916'800,
                                      479'001'600,
                                      6'227'020'800,
                                      87'178'291'200,
                                      1'307'674'368'000,
                                      20'922'789'888'000,
                                      355'687'428'096'000,
                                      6'402'373'705'728'000,
                                      121'645'100'408'832'000,
                                      2'432'902'008'176'640'000};

std::list<size_t> getPermImpl(std::vector<size_t> &elems, size_t permNum);
std::list<size_t> getPerm(size_t elemAmount, size_t permNum);
void printPerm(const std::list<size_t> &perm);

int main()
{
  size_t elemAmount = 0;
  size_t permNum = 0;

  std::cin >> elemAmount >> permNum;

  printPerm(getPerm(elemAmount, permNum - 1));
  return 0;
}

std::list<size_t> getPermImpl(std::vector<size_t> &elems, size_t permNum)
{
  if (elems.size() == 0)
    return {};

  const auto regionLen =
      FACT[elems.size() - 1]; /* == FACT[elems.size()] / elems.size(); */
  const auto curNumIdx = permNum / regionLen;

  const auto curNum = elems[curNumIdx];

  elems.erase(elems.begin() + curNumIdx);
  const auto newIdx = permNum % regionLen;

  auto res = getPermImpl(elems, newIdx);
  res.push_front(curNum);
  return res;
}

std::list<size_t> getPerm(size_t elemAmount, size_t permNum)
{
  std::vector<size_t> elems{};
  elems.resize(elemAmount);
  std::iota(elems.begin(), elems.end(), 1);

  return getPermImpl(elems, permNum);
}

void printPerm(const std::list<size_t> &perm)
{
  for (auto elem : perm)
    std::cout << elem << " ";
  std::cout << std::endl;
}
