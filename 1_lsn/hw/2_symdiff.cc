#include <iostream>
#include <stdexcept>
#include <vector>

namespace Tako
{

class Set
{
  public:
    using ChunkT = uint32_t;
    static constexpr uint32_t CHUNK_SIZE = 32;

  private:
    size_t max_elem_;
    std::vector<ChunkT> data_;

  public:
    Set(size_t max_elem) : max_elem_(max_elem), data_(max_elem, 0)
    {
    }

    bool insert(size_t elnum)
    {
        if (elnum >= max_elem_)
            return false;

        data_[elnum / CHUNK_SIZE] |= 1 << (elnum % CHUNK_SIZE);
        return true;
    }

    bool erase(size_t elnum)
    {
        if (elnum >= max_elem_)
            return false;

        data_[elnum / CHUNK_SIZE] &= ~(1 << (elnum % CHUNK_SIZE));
        return true;
    }

    bool in(size_t elnum)
    {
        return (data_[elnum / CHUNK_SIZE] >> (elnum % CHUNK_SIZE)) & 1;
    }

    const Set &operator^=(const Set &rhs)
    {
        if (max_elem_ != rhs.max_elem_)
            throw std::runtime_error{"Tako::Set::operator^=: max_elem_ != rhs.max_elem_"};

        for (size_t i = 0; i < max_elem_; ++i)
            data_[i] ^= rhs.data_[i];

        return *this;
    }

    void print()
    {
        for (size_t i = 1; i < max_elem_; ++i)
            if (in(i))
                std::cout << i << " ";

        std::cout << std::endl;
    }
};

Set operator^(const Set &lhs, const Set &rhs)
{
    auto lhs_cpy = lhs;
    return lhs_cpy ^= rhs;
}

Set read_set(size_t max_elem)
{
    Set res{max_elem};

    Set::ChunkT elem = 0;
    std::cin >> elem;

    while (elem != 0)
    {
        res.insert(elem);
        std::cin >> elem;
    }

    return res;
}

} // namespace Tako

int main()
{
    constexpr size_t max_elem = 20000;

    auto s1 = Tako::read_set(max_elem);
    auto s2 = Tako::read_set(max_elem);

    auto sres = s1 ^ s2;
    sres.print();
    return 0;
}