#include <bitset>
#include <iostream>
#include <string>
#include <vector>

constexpr void strCpyFast(char *&dest, const char *source)
{
  while ((*dest = *source++))
    dest++;
}
constexpr char *uintToString(unsigned int x, char *bufferEnd)
{
  if (x == 0)
    *--bufferEnd = '0';
  else
    while (x)
    {
      *--bufferEnd = '0' + x % 10;
      x /= 10;
    }
  return bufferEnd;
}

int main()
{
  int N = 0;
  int M = 0;

  std::cin >> N >> M;

  std::vector<bool> inverse_rows(N);
  std::vector<bool> inverse_cols(M);

  std::vector<int> sum_row(N);
  std::vector<int> sum_col(M);

  for (int i = N - 1; i >= 0; i--)
  {
    sum_row[i] = 0;
    inverse_rows[i] = false;
  }

  for (int j = M - 1; j >= 0; j--)
  {
    sum_col[j] = 0;
    inverse_cols[j] = false;
  }

  // allocate matrix
  std::vector<std::vector<int>> matrix(N);
  for (auto &line : matrix)
    line.resize(M);

  // read matrix
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < M; j++)
    {
      int input = 0;
      std::cin >> input;
      matrix[i][j] = input;
      sum_row[i] += input;
      sum_col[j] += input;
    }
  }

  // make cycle k times before declaring it is impossible
  bool stuffHappening = true;
  for (int k = 10; stuffHappening && k > 0; k--)
  {
    stuffHappening = false;

    // make matrix row-positive
    for (int i = 0; i < N; i++)
    {
      if (sum_row[i] >= 0)
        continue;

      for (int j = M - 1; j >= 0; j--)
      {
        sum_col[j] -= 2 * matrix[i][j];
        matrix[i][j] = -matrix[i][j];
      }

      sum_row[i] = -sum_row[i];
      inverse_rows[i] = inverse_rows[i] ^ true;
      stuffHappening = true;
    }

    // make matrix col-positive
    for (int j = M - 1; j >= 0; j--)
    {
      if (sum_col[j] >= 0)
        continue;

      for (int i = N - 1; i >= 0; i--)
      {
        sum_row[i] -= 2 * matrix[i][j];
        matrix[i][j] = -matrix[i][j];
      }

      sum_col[j] = -sum_col[j];
      inverse_cols[j] = inverse_cols[j] ^ true;
      stuffHappening = true;
    }
  }

  // output
  {
    bool impossible = false;
    // matrix now is col-positive
    // check is it is still row-positive
    if (stuffHappening)
    {
      for (int i = N - 1; i >= 0; i--)
      {
        if (sum_row[i] >= 0)
          continue;

        impossible = true;
        break;
      }
    }

    if (impossible)
    {
      std::cout << "Impossible" << std::endl;
    }
    else
    {
      char *const buffer = new char[5 * 100 * 100 + 1], *buffer_end = buffer;
      buffer[1] = buffer[5 * 100 * 100] = 0;

      for (int i = N - 1; i >= 0; i--)
      {
        if (inverse_rows[i])
        {
          strCpyFast(buffer_end, "\nl ");
          strCpyFast(buffer_end, uintToString(i, buffer + 5 * 100 * 100));
        }
      }

      for (int j = M - 1; j >= 0; j--)
      {
        if (inverse_cols[j])
        {
          strCpyFast(buffer_end, "\nc ");
          strCpyFast(buffer_end, uintToString(j, buffer + 5 * 100 * 100));
        }
      }
      std::cout << (buffer + 1) << std::endl;
      delete[] buffer;
    }
  }

  return 0;
}