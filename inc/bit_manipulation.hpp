#ifndef LKEEGAN_CTCI_BIT_MANIPULATION_H
#define LKEEGAN_CTCI_BIT_MANIPULATION_H
#include <bitset>
#include <cmath>
#include <iostream>
// 5.1
// insert M into N starting at bit j and ending at bit i
// e.g. [..N..[j..M..i]..]
int insertion(int N, int M, int i, int j);

// 5.2
// given double in [0,1)
// print digits as binary
// if it doesn't fit in 32 bits, print "ERROR"
// e.g. 0.17 -> 17 in binary = 16 + 1 = 10001?
// presumably ignore rounding?
// (e.g. the double 0.17 is equivalent to 0.1699999999999999999999999)
// (would the latter be an ERROR?)
// TODO std::string binary_to_string(double x);

// 5.3
// given (signed) integer, return length of longest possible
// sequence of 1's possible using a single flip of a bit from 0 to 1
// e.g. 1775 (aka 11011101111) -> 8 (length of longest possible 1's)
int flip_bit_to_win(int input);

// 5.4
// given number, find nearest smaller and larger values
// which contain the same number of 1's in the binary
void next_number(int x, int &smaller, int &larger);

// 5.5
// what does ((n&(n-1)) == 0) do?
bool debugger(int n);

// 5.6
// number of bits to flip to convert A to B
int conversion(int A, int B);

// 5.7
// pairwise swap odd/even bits: 0<->1, 2<->3, etc
// e.g. 0110101101 -> 1001011110
int pairwise_swap(int x);
#endif  // LKEEGAN_CTCI_BIT_MANIPULATION_H
