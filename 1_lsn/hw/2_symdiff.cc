#include <iostream>
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
        return (data_[elnum / CHUNK_SIZE] >> (elnum / CHUNK_SIZE)) & 1;
    }
};

} // namespace Tako

int main()
{
    return 0;
}