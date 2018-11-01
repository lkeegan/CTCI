#ifndef LKEEGAN_CTCI_MODERATE_H
#define LKEEGAN_CTCI_MODERATE_H
#include <array>
#include <cstddef>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

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
// all words in book: O(n) cost to set up, then O(1) look-up (but O(n) space)
std::unordered_map<std::string, int> word_frequency_map(
    const std::string& book, const std::string& delims = " ,.;:-?");

// 16.4 Tic-tac-toe win
// NxN board contains:
// '.' for empty square (0),
// 'x' for cross (+1),
// 'o' for circle (-1)
template <std::size_t N>
class tic_tac_toe {
 private:
  std::array<std::array<char, N>, N> board;
  std::array<int, N> row_count;
  std::array<int, N> col_count;
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

#endif  // LKEEGAN_CTCI_MODERATE_H
