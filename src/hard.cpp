#include "hard.hpp"

unsigned int add_without_plus(unsigned int a, unsigned int b) {
  unsigned int result = 0;
  unsigned int bit = 0;
  unsigned int carry = 0;
  // keep adding until we have processed all non-zero bits in a & b
  while ((a > 0) || (b > 0)) {
    // get lsb of a and b
    unsigned int a_lsb = (a & 1);
    unsigned int b_lsb = (b & 1);
    // bitwise addition of a_lsb, b_lsb and carry bit
    // each addition is an XOR (0+0=0, 0+1=1+0=1, 1+1=0 [+carry])
    result |= (a_lsb ^ b_lsb ^ carry) << bit;
    // carry is 1 if there were least 2x 1's in a,b & carry,
    // e.g. a&b=1 or a&carry=1 or b&carry=1
    carry = (a_lsb & b_lsb) | (carry & (a_lsb | b_lsb));
    // shift a,b to the right by one bit
    a >>= 1;
    b >>= 1;
    // increment bit location
    ++bit;
  }
  // may be a final carry bit left over
  // that we need to include in result
  result |= carry << bit;
  return result;
}

unsigned int missing_number(const std::vector<unsigned int>& A) {
  // O(n) - assumes that A is sorted in ascending order
  for (unsigned int n = 0; n < static_cast<unsigned int>(A.size()); ++n) {
    // find location of bit that differs for n, n+1
    unsigned int bit = 0;
    unsigned int bit_differs = n ^ (n + 1);
    while ((bit_differs & 1) == 0) {
      bit_differs >>= 1;
      ++bit;
    }
    // if bit doesn't match for n, we have found missing value
    if (get_bit(bit, n, A) != (((n >> bit) & 1) != 0)) {
      return n;
    }
  }
  // if all matched return A.size(), i.e. missing value is n+1
  return A.size();
}