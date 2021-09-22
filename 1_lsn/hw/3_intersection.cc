#include <iostream>
#include <vector>

int main()
{
    size_t size1 = 0;
    size_t size2 = 0;

    std::cin >> size1;
    std::cin >> size2;

    std::vector<int32_t> inp1(size1);
    for (size_t i = 0; i < size1; ++i)
        std::cin >> inp1[i];

    std::vector<int32_t> inp2(size1);
    for (size_t i = 0; i < size1; ++i)
        std::cin >> inp2[i];

    size_t i1 = 0, i2 = 0;
    while ((i1 < size1) && (i2 < size2))
    {
        if (inp1[i1] == inp2[i2])
        {
            std::cout << inp1[i1] << " ";
            ++i1, ++i2;
        }
        else if (inp1[i1] > inp2[i2])
            ++i2;
        else
            ++i1;
    }

    std::cout << std::endl;
    return 0;
}
