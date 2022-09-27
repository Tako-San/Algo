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
