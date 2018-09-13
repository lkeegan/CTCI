#include "arrays_and_strings.h"

bool is_unique_a(const std::string &str) {
  // use hash table to check if char has already been seen.
  // best case: O(1)
  // average: O(N)
  // worst case: O(N^2)
  std::unordered_map<char, bool> char_exists;
  for (char c : str) {
    if (char_exists[c]) {
      return false;
    } else {
      char_exists[c] = true;
    }
  }
  return true;
}

bool is_unique_b(const std::string &str) {
  // for each char, search rest of string for match
  // best case: O(1)
  // average: O(N^2)
  // worst case: O(N^2)
  for (int i = 0; i < static_cast<int>(str.size() - 1); ++i) {
    if (str.find(str[i], i + 1) != std::string::npos) {
      return false;
    }
  }
  return true;
}

bool check_permutation(const std::string &strA, const std::string &strB) {
  // best case: O(1)
  // average: O(N)
  // worst case: O(N^2)
  if (strA.size() != strB.size()) {
    // cannot be permutation of each other if different length
    return false;
  }
  // make hash table of frequency of each char in strA
  std::unordered_map<char, int> char_count;
  for (char c : strA) {
    ++char_count[c];
  }
  // decrement each char in strB from hash table
  for (char c : strB) {
    --char_count[c];
  }
  // if all values are zero then strings made of same set
  // of chars, i.e. they are permutations of each other
  for (const auto &pair : char_count) {
    if (pair.second != 0) {
      return false;
    }
  }
  return true;
}

void URLify(std::string &str, int length) {
  // best case: O(N)
  // average: O(N)
  // worst case: O(N)
  std::vector<int> space_loc;
  // find location of all spaces in first length chars of str
  for (int i = 0; i < length; ++i) {
    if (str[i] == ' ') space_loc.push_back(i);
  }
  int n_spaces = static_cast<int>(space_loc.size());
  // need two extra chars per space
  int buffer = static_cast<int>(str.size()) - length;
  if (buffer < 2 * n_spaces) {
    throw("STRING_TOO_SMALL");
  }
  // move each char[i] that needs moving
  // directly to its final destination char[i+shift]
  // starting from the end and working backwards
  // need to shift 2 to the right for each preceeding space
  int i = length - 1;
  while (n_spaces > 0) {
    int shift = 2 * n_spaces;
    // shift char right by 2 for each preceeding space
    while (i > space_loc[n_spaces - 1]) {
      str[i + shift] = str[i];
      --i;
    }
    // insert "%20" in place of " "
    str[i + shift] = '0';
    str[i + shift - 1] = '2';
    str[i + shift - 2] = '%';
    --i;
    --n_spaces;
  }
}

bool is_permutation_of_palindrome(const std::string &str) {
  // best case: O(N)
  // average: O(N)
  // worst case: O(N)

  // ignoring spaces, given n chars, can make palindrome iff:
  // -for even n: each char comes in pairs, i.e. even count, e.g abbssbba
  // -if n is odd: single char with odd count, the rest even, e.g. atzta

  // get frequency count of chars
  std::unordered_map<char, int> char_count;
  int n_chars = 0;
  for (char c : str) {
    if (c != ' ') {
      ++char_count[c];
      ++n_chars;
    }
  }
  // count chars with odd frequency counts
  int odd_count_chars = 0;
  for (const auto &pair : char_count) {
    if (pair.second % 2 == 1) {
      ++odd_count_chars;
    }
  }
  if (n_chars % 2 == 0 && odd_count_chars == 0) {
    return true;
  } else if (n_chars % 2 == 1 && odd_count_chars == 1) {
    return true;
  } else {
    return false;
  }
}
