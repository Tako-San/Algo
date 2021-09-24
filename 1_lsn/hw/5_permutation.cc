#include <algorithm>
#include <vector>
#include <iostream>
 
int main()
{
    std::string s = "1234";
    std::sort(s.begin(), s.end());
    do {
        std::cout << s << '\n';
    } while(std::next_permutation(s.begin(), s.end()));
}