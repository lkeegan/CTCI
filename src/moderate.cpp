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

bool MyIntersection::intersect(const line& a, const line& b,
                               point* intersection_point) {
  // want to find x such that
  // a_0 + a_1 x = b_0 + b_1 x
  double a1 = (a.end.y - a.start.y) / (a.end.x - a.start.x);
  double a0 = a.start.y - a1 * a.start.x;
  double b1 = (b.end.y - b.start.y) / (b.end.x - b.start.x);
  double b0 = b.start.y - b1 * b.start.x;
  double x = (b0 - a0) / (a1 - b1);
  // check that x lies between start and end x points for both lines
  // NB allows for case that "start.x" > "end.x"
  bool a_in_range = (((x >= a.start.x) && (x <= a.end.x)) ||
                     ((x >= a.end.x) && (x <= a.start.x)));
  bool b_in_range = (((x >= b.start.x) && (x <= b.end.x)) ||
                     ((x >= b.end.x) && (x <= b.start.x)));
  if (a_in_range && b_in_range) {
    // optionally write location to intersection_point
    if (intersection_point) {
      intersection_point->x = x;
      intersection_point->y = a0 + a1 * x;
    }
    return true;
  }
  return false;
}