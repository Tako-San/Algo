#include <iostream>
#include <vector>

int get_sym(size_t strnum, size_t pos)
{
    if (0 == pos)
        return 1 + strnum;

    size_t sublen = 1ull << strnum;
    size_t new_pos = (pos < sublen) ? (pos - 1) : (2 * sublen - pos - 2);
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
