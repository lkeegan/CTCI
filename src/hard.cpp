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
