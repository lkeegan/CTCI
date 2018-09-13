#ifndef LKEEGAN_CTCI_ARRAYS_AND_STRINGS_H
#define LKEEGAN_CTCI_ARRAYS_AND_STRINGS_H
#include <algorithm>
#include <iostream>  //for debugging
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

// 1.1a
// check if string contains only unique characters
bool is_unique_a(const std::string &str);
// 1.1b
// ditto without additional data structures
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

#endif  // LKEEGAN_CTCI_ARRAYS_AND_STRINGS_H
