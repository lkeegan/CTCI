#ifndef LKEEGAN_CTCI_ARRAYS_AND_STRINGS_H
#define LKEEGAN_CTCI_ARRAYS_AND_STRINGS_H
#include <algorithm>
#include <array>
#include <stdexcept>
#include <string>
#include <vector>

namespace CTCI {
namespace arrays_and_strings {

// 1.1a
// check if string contains only unique characters
bool is_unique_a(const std::string &str);
// 1.1b
// ditto without using additional data structures
bool is_unique_b(const std::string &str);

// 1.2
// check if two strings are permutations of each other
bool check_permutation(const std::string &strA, const std::string &strB);

// 1.3
// in-place replacement of " " with "%20"
// can assume string has required space
// and that length of string (without this buffer) is supplied
void URLify(std::string &str, int length);

// 1.4
// check if string can be permuted into a palindrome (ignoring spaces)
bool is_permutation_of_palindrome(const std::string &str);

// 1.5
// check if strings can be made equal by either inserting,
// removing or replacing at most 1 character
bool one_away(const std::string &strA, const std::string &strB);

// 1.6
// compress string: replace repeated letters with letter&count,
// e.g. aaabb -> a3b2
// if "compressed" string not shorter than original, return original
std::string string_compression(const std::string &str);

// 1.7
// NxN matrix, each element 4 bytes
// implemented as 2-d vector mat[row][col]
// rotate in-place by 90 degrees, i.e. M_(x,y) -> M_(y,N-1-x)
typedef std::vector<std::vector<int>> matrix;
void rotate_matrix(matrix &M);

// 1.8
// MxN matrix: if an element is zero, set row and column
// containing element to zero
void zero_matrix(matrix &M);

// 1.9
// check if strA can be rotated (cyclically permuted) into strB
bool is_rotation(const std::string &strA, const std::string &strB);
// using one call to is_substring: which determines if a string
// is a substring of another, e.g.:
inline bool is_substring(const std::string &strA, const std::string &strB) {
  return strB.find(strA) != std::string::npos;
}

}  // namespace arrays_and_strings
}  // namespace CTCI

#endif  // LKEEGAN_CTCI_ARRAYS_AND_STRINGS_H
