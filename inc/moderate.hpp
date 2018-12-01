#ifndef LKEEGAN_CTCI_MODERATE_H
#define LKEEGAN_CTCI_MODERATE_H
#include <algorithm>
#include <array>
#include <cstddef>
#include <iostream>
#include <limits>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace CTCI {
namespace moderate {

// 16.1 swap two numbers in-place
// works for int, unsigned int
template <class T>
void number_swapper(T& left, T& right) {
  using myint = long long;
  left = static_cast<T>(static_cast<myint>(left) ^ static_cast<myint>(right));
  right = static_cast<T>(static_cast<myint>(right) ^ static_cast<myint>(left));
  left = static_cast<T>(static_cast<myint>(left) ^ static_cast<myint>(right));
}

// 16.2 count occurences of single word in book: O(n) cost
int word_frequency(const std::string& word, const std::string& book,
                   const std::string& delims = " ,.;:-?");
// for many words, can instead generate hash map of frequency counts for
// all words in book: O(n) computation & O(n) space to set up,
// then O(1) for each word look-up
std::unordered_map<std::string, int> word_frequency_map(
    const std::string& book, const std::string& delims = " ,.;:-?");

// 16.3
namespace MyIntersection {

struct point {
  double x;
  double y;
  point(double x = 0.0, double y = 0.0) : x(x), y(y) {}
};

struct line {
  point start;
  point end;
  line(const point& start = point(), const point& end = point())
      : start(start), end(end) {}
};

bool intersect(const line& a, const line& b,
               point* intersection_point = nullptr);
}  // namespace MyIntersection

// 16.4 Tic-tac-toe win
// NxN board contains:
// '.' for empty square (0),
// 'x' for cross (+1),
// 'o' for circle (-1)
template <std::size_t N>
class tic_tac_toe {
 private:
  std::array<std::array<char, N>, N> board;
  std::array<int, N> row_count{};
  std::array<int, N> col_count{};
  int diag_r_count = 0;
  int diag_l_count = 0;
  int winner = 0;

 public:
  // empty board constructor
  tic_tac_toe() {
    for (auto& row : board) {
      for (auto& site : row) {
        site = '.';
      }
    }
  }
  // constructor with board supplied as string, e.g. "x.ox..oox"
  explicit tic_tac_toe(const std::string& board_str) {
    auto board_char = board_str.cbegin();
    int count = 0;
    while ((board_char != board_str.cend()) &&
           (count < static_cast<int>(N * N))) {
      int row = count / N;
      int col = count % N;
      board[row][col] = '.';
      play(row, col, *board_char);
      ++count;
      ++board_char;
    }
  }
  // ouput board as ostream
  friend std::ostream& operator<<(std::ostream& s, const tic_tac_toe& tic) {
    for (const auto& row : tic.board) {
      for (char move_played : row) {
        s << move_played << " ";
      }
      s << std::endl;
    }
    return s;
  }
  void update_count(int& counter, int diff) {
    counter += diff;
    // N in a row?
    if (std::abs(counter) == N) {
      winner = diff;
    }
  }
  // returns true if game winning play
  bool play(int row, int col, char chr) {
    // check space is empty
    if (board[row][col] != '.') {
      std::cerr << "Invalid move: this space has already been used - please "
                   "try another location."
                << std::endl;
      return false;
    }
    // parse input chr: can play either 'x' (+1) or 'o' (-1)
    int val = 0;
    if (chr == 'x') {
      val = +1;
    } else if (chr == 'o') {
      val = -1;
    }
    // any other play is ignored, so return false
    if (val == 0) {
      board[row][col] = '.';
      return false;
    }
    // make play, update counts of row/col/diag n-in-a-row's
    board[row][col] = chr;
    update_count(row_count[row], val);
    update_count(col_count[row], val);
    if (row == col) {
      update_count(diag_r_count, val);
    }
    if ((row + col) == (N - 1)) {
      update_count(diag_l_count, val);
    }
    // if any of the above gave N in a row, winner was set to val
    if (winner == val) {
      return true;
    }
    // otherwise we didn't win, so return false
    return false;
  }
  bool circle(int row, int col) { return play(row, col, 'o'); }
  bool cross(int row, int col) { return play(row, col, 'x'); }
  bool cross_wins() { return winner == +1; }
  bool circle_wins() { return winner == -1; }
};

// 16.5
// count trailing zeros in factorial n!
unsigned int factorial_trailing_zeros(unsigned int n);

// 16.6
// smallest non-negative difference between pair of values
// one from each of two supplied integer arrays
int smallest_difference(std::vector<int> a, const std::vector<int>& b);

// 16.7
// return max (furthest from zero) of two numbers
// w/o if, else or comparison operator
template <typename T>
T number_max(T a, T b) {
  // (int)(a/b) = 0        for a <= b
  //            = non-zero for a  > b
  int a_factor = static_cast<T>(static_cast<int>(a / b));
  int b_factor = static_cast<T>(static_cast<int>(b / a));
  // if a>b: b_factor = 0, return a
  // if b>a: a_factor = 0, return b
  // if a==b: a_factor = b_factor, return (a+b)/2 == a == b
  return (a * a_factor + b * b_factor) / (a_factor + b_factor);
}

// 16.8
// print number as text
std::string english_int(unsigned long long int number);

// 16.9 implement - * / for integers using only +
// a - b
int operations_minus(int a, int b);
// a * b
int operations_multiply(int a, int b);
// a / b
int operations_divide(int a, int b);

// 16.10 list of birth & death years for people
// find year with the most people alive
// all years lie in range [1900, 2000]
int year_with_most_people(
    const std::vector<std::pair<int, int>>& birth_death_years);

// 16.11 diving board:
// k planks end-to-end, two sizes of plank
// enumerate all possible lengths
std::unordered_set<int> enumerate_lengths(int k, int shorter, int longer);

// 16.23
// rand7 generates random integer in [0,7) from supplied rand5() function
class rand_n {
  // rand_n() provides random int from flat dist in [0,n)
  // NB: NOT threadsafe
 private:
  std::ranlux48 rng;
  std::uniform_int_distribution<int> int_dist;

 public:
  explicit rand_n(int n = 2, int seed = 123) : rng(seed), int_dist(0, n - 1) {}
  inline int operator()() { return int_dist(rng); }
};
int rand7(rand_n& rand5);

}  // namespace moderate
}  // namespace CTCI
#endif  // LKEEGAN_CTCI_MODERATE_H
