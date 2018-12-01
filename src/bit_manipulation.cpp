#include "bit_manipulation.hpp"

namespace CTCI {
namespace bit_manipulation {

int insertion(int N, int M, int i, int j) {
  // check that M contains j-i+1 bits
  // if not return zero
  int tmpM = M;
  int size_of_M = 0;
  while (tmpM != 0) {
    tmpM = tmpM >> 1;
    ++size_of_M;
  }
  if (size_of_M != (j - i) + 1) {
    throw std::invalid_argument("i,j do not match size of M");
  }
  // check that bits i through j of N are zero
  // otherwise return zero
  int mask = ((1 << (j - i + 1)) - 1) << i;
  if ((mask & N) != 0) {
    throw std::invalid_argument("N does not have space to insert M");
  }
  // shift M left by i bits, then or with N
  return (N | (M << i));
}

int flip_bit_to_win(int input) {
  int max_length = 0;
  int length_before = 0;
  while (input != 0) {
    int length_after = 0;
    // count consecutive 1's
    while ((input & 1) == 1) {
      ++length_after;
      input >>= 1;
    }
    // update best possible set of 1's
    max_length = std::max(max_length, length_before + length_after);
    // skip over a single zero
    input >>= 1;
    // if next bit is a 1, we could combine
    // the next set of 1's with the previous set of 1's
    if ((input & 1) == 1) {
      length_before = length_after;
    } else {
      // otherwise we can't:
      length_before = 0;
      // skip over zeros until we hit a 1
      while (((input & 1) == 0) && (input != 0)) {
        input >>= 1;
      }
    }
  }
  // max_length = size of two largest 1's separated by single 0
  // add one for the 0->1 flip:
  return max_length + 1;
}

void next_number(int x, int &smaller, int &larger) {
  // closest larger: swap least-significant (01) pair of bits
  // closest smaller: swap least-significant (10) pair of bits
  smaller = x;
  larger = x;
  int y = 1;
  int first_bit = (x & 1);
  // find where value of bit changes (either 0->1 or 1->0)
  while ((x & 1) == first_bit) {
    x >>= 1;
    y <<= 1;
    if (x == 0) {
      // if x was of form 00..00 or 00..0011..11,
      // we can't form a smaller number using same number of 1's
      throw std::invalid_argument("No smaller value possible");
    }
  }
  if (first_bit == 0) {
    // found location of 1 in first 10 pair, where
    // 00..00100..00 = y, so swapping 1 <-> 0
    // equivalent to replacing y contribution with y/2 in x:
    smaller -= y / 2;
  } else {
    // found location of 0 in first 01 pair, so swapping them
    // equivalent to replacing y/2 contribution with y in x:
    larger += y / 2;
  }
  // find next change of bit value
  while ((x & 1) != first_bit) {
    x >>= 1;
    y <<= 1;
  }
  if (first_bit == 0) {
    larger += y / 2;
  } else {
    smaller -= y / 2;
  }
}

bool debugger(int n) {
  // returns true if n is zero or an integer power of 2

  // if n is negative, sign bit will remain 1 so always returns false.

  // for positive n, consider LSB's of n: assume there are
  // x zeroes followed by a 1
  // (n-1) flips these x+1 LSB's
  // so n&(n-1) sets the least significant x+1 bits to zero
  // For n&(n-1) == 0 to return true, the remaining MSB's must be zeros
  // i.e. n must be of the form [00..00100..00] i.e. a power of 2

  // NB: largest negative number may also return true,
  // since n-1 would be undefined behaviour but might give 0

  return ((n & (n - 1)) == 0);
}

int conversion(int A, int B) {
  int flips = 0;
  while (A != 0 || B != 0) {
    flips += (A & 1) ^ (B & 1);
    A >>= 1;
    B >>= 1;
  }
  return flips;
}

int pairwise_swap(int x) {
  // 0101 = 5 in hex
  int mask_odd = 0x55555555;  // repeating 01 pairs
  // 1010 = A in hex
  int mask_even = 0xAAAAAAAA;  // repeating 10 pairs
  return ((x & mask_odd) << 1) + ((x & mask_even) >> 1);
}

// TODO
/*
void draw_line(std::vector<std::uint_8> &screen, int width, int x1, int x2,
               int y) {
  // ...[x1].....[x2].... -> ...1111111....
  int screen_size = static_cast<int>(screen.size()) * 8;
  int height = screen_size / width;
  int line_width = x2 - x1 + 1;
  int lsb = (screen_size - 1) - ((y - 1) * width + x1);
  for (int bit = lsb; bit>=lsb-line_width; --bit){
      int index = bit / 8;

  } (lsb >= msb) {
      int bit = (screen_size - 8) - lsb;
      int local_bit = lsb % 8;
      screen[index] = ;
      ++lsb;
    }
}
*/
}  // namespace bit_manipulation
}  // namespace CTCI