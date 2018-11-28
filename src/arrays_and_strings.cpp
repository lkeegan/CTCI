#include "arrays_and_strings.hpp"

bool is_unique_a(const std::string &str) {
  // use look-up table to check if char has already been seen.
  // NOTE: assume 7-bit ASCII chars
  // best case: O(1)
  // worst case: O(N) where N is number of unique chars, i.e. max 2^7
  if (str.size() > 128) {
    // there are only 128 unique possible chars
    return false;
  }
  std::array<bool, 128> char_exists{};
  for (char c : str) {
    if (char_exists[static_cast<unsigned int>(c)]) {
      return false;
    } else {
      char_exists[static_cast<unsigned int>(c)] = true;
    }
  }
  return true;
}

bool is_unique_b(const std::string &str) {
  // for each char, search rest of string for match
  // best case: O(1)
  // average: O(N^2)
  // worst case: O(N^2)
  if (str.size() > 128) {
    // there are only 128 unique possible chars
    return false;
  }
  for (int i = 0; i < static_cast<int>(str.size()) - 1; ++i) {
    if (str.find(str[i], i + 1) != std::string::npos) {
      return false;
    }
  }
  return true;
}

bool check_permutation(const std::string &strA, const std::string &strB) {
  // assume 7-bit ASCII chars
  // best case: O(1)
  // worst case: O(N)
  if (strA.size() != strB.size()) {
    // cannot be permutation of each other if different length
    return false;
  }
  // frequency count of each char in strA
  std::array<int, 128> char_count{};
  for (char c : strA) {
    ++char_count[static_cast<std::size_t>(c)];
  }
  // decrement each char in strB from frequency count
  for (char c : strB) {
    --char_count[static_cast<std::size_t>(c)];
  }
  // if all values are zero then strings made of same set
  // of chars, i.e. they are permutations of each other
  for (int count : char_count) {
    if (count != 0) {
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
    throw std::invalid_argument("STRING_TOO_SMALL");
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
  // assume 7-bit ASCII chars
  // best case: O(N)
  // average: O(N)
  // worst case: O(N)

  // frequency count: is it odd or even for each char
  std::array<bool, 128> char_odd_count{};
  int n_chars = 0;
  for (char c : str) {
    if (c != ' ') {
      char_odd_count[c] = !char_odd_count[c];
      ++n_chars;
    }
  }
  // count chars with odd frequency counts
  int odd_count_chars = 0;
  for (bool is_odd : char_odd_count) {
    if (is_odd) {
      ++odd_count_chars;
    }
  }
  // can make palindrome iff:
  // -for even n_chars: even count of each char, i.e. no odd counts, e.g. abba
  // -if n is odd: single char with odd count, the rest even, e.g. aba
  if (n_chars % 2 == odd_count_chars) {
    return true;
  } else {
    return false;
  }
}

bool one_away(const std::string &strA, const std::string &strB) {
  // best case: O(1)
  // average: O(N)
  // worst case: O(N)

  int n_A = static_cast<int>(strA.size());
  int n_B = static_cast<int>(strB.size());
  int diff = n_A - n_B;
  // +1: can try removing one char from A
  //  0: can try replacing one char in A
  // -1: can try inserting one char to A
  // otherwise: more than one edit away
  if (abs(diff) > 1) {
    return false;
  }
  int n_changes = 0;
  for (int i = 0; i < n_A; ++i) {
    if (strA[i] != strB[i - n_changes * diff]) {
      ++n_changes;
      if (n_changes > 1) {
        return false;
      }
    }
  }
  return true;
}

std::string string_compression(const std::string &str) {
  // best case: O(N)
  // average: O(N)
  // worst case: O(N)
  std::string str_compressed;
  int chars_compressed = 0;
  for (std::string::const_iterator i = str.begin(); i != str.end(); ++i) {
    str_compressed += *i;
    int count = 1;
    while (i != str.end() && *(i + 1) == *i) {
      ++count;
      ++i;
    }
    str_compressed += std::to_string(count);
    chars_compressed += count - 2;
  }
  if (chars_compressed > 0) {
    return str_compressed;
  } else {
    return str;
  }
}

void rotate_matrix(matrix &M) {
  // best case: O(N) [where N is number of matrix elements]
  // average: O(N)
  // worst case: O(N)
  int N = static_cast<int>(M.size());
  // for x,y modulo N-1, 4x90deg rotations form a closed set:
  // M(x,y) -> M(y,-x)
  // M(y,-x) -> M(-x,-y)
  // M(-x,-y) -> M(-y,x)
  // M(-y,x) -> M(x,y)
  // So can rotate the above 4 elements
  // by 90deg with 3 swaps
  // without affecting the rest of the matrix
  // Repeat for all x,y in upper left corner to rotate all elements
  for (int x = 0; x < (N + 1) / 2; ++x) {
    for (int y = 0; y < N / 2; ++y) {
      std::swap(M[x][y], M[y][N - 1 - x]);
      std::swap(M[x][y], M[N - 1 - x][N - 1 - y]);
      std::swap(M[x][y], M[N - 1 - y][x]);
    }
  }
}

void zero_matrix(matrix &M) {
  // best case: O(MN) [where ML is number of matrix elements]
  // average: O(MN)
  // worst case: O(MN)
  int n_rows = static_cast<int>(M.size());
  int n_cols = static_cast<int>(M[0].size());
  std::vector<int> zero_rows(n_rows, 1);
  std::vector<int> zero_cols(n_cols, 1);
  // first pass: look for rows/columns containing zeros
  for (int row = 0; row < n_rows; ++row) {
    for (int col = 0; col < n_cols; ++col) {
      if (M[row][col] == 0) {
        zero_rows[row] = 0;
        zero_cols[col] = 0;
      }
    }
  }
  // second pass: apply zeros
  for (int row = 0; row < n_rows; ++row) {
    for (int col = 0; col < n_cols; ++col) {
      M[row][col] *= zero_rows[row] * zero_cols[col];
    }
  }
}

bool is_rotation(const std::string &strA, const std::string &strB) {
  if (strA.size() != strB.size()) {
    return false;
  }
  // if we can cyclically permute strA to form strB,
  // then strA must be contained in strB + strB, e.g.
  // "abcd" <-> "bcd[a""bcd]a"
  std::string strB_doubled = strB + strB;
  return is_substring(strA, strB_doubled);
}
