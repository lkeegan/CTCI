#include "moderate.hpp"

int word_frequency(const std::string& word, const std::string& book,
                   const std::string& delims) {
  int count = 0;
  std::size_t next = -1;
  do {
    std::size_t curr = next + 1;
    next = book.find_first_of(delims, curr);
    if (book.substr(curr, next - curr) == word) {
      ++count;
    }
  } while (next != std::string::npos);
  return count;
}

std::unordered_map<std::string, int> word_frequency_map(
    const std::string& book, const std::string& delims) {
  std::unordered_map<std::string, int> counts;
  std::size_t next = -1;
  do {
    std::size_t curr = next + 1;
    next = book.find_first_of(delims, curr);
    ++counts[book.substr(curr, next - curr)];
  } while (next != std::string::npos);
  return counts;
}
