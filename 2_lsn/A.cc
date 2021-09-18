#include <array>
#include <iostream>
#include <limits>

using std::array;
using std::cin;
using std::cout;
using std::endl;

int main() {
  size_t N = 0;
  cin >> N;
  array<ssize_t, 23> W{};

  ssize_t total = 0;
  for (size_t i = 0; i < N; ++i) {
    cin >> W[i];
    total += W[i];
  }

  ssize_t min = std::numeric_limits<ssize_t>::max();

  // iterating over all heap splitting
  // 1 - left heap, 0 right heap
  for (size_t gen = 0, end = 1u << N; gen < end; ++gen) {
    ssize_t sum = 0;
    for (size_t i = 0, u = gen; u != 0; ++i, u >>= 1)
      sum += (u & 1) * W[i];

    // not 2 * sum, because signed mul is not shift
    ssize_t diff = total - sum - sum;
    if (diff < 0)
      diff = -diff;

    if (diff < min)
      min = diff;
  }

  cout << min << endl;
  return 0;
}
