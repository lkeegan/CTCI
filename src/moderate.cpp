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

unsigned int factorial_trailing_zeros(unsigned int n) {
  unsigned long long sig_digits = 1;
  unsigned int zeros = 0;
  for (unsigned int i = 1; i <= n; ++i) {
    unsigned long long old_sig_digits = sig_digits;
    sig_digits *= i;
    // if multiplying by i results in a smaller
    // unsigned long integer, then we have overflow
    if (sig_digits < old_sig_digits) {
      throw std::overflow_error("integer overflow in factorial_trailing_zeros");
    }
    // remove and count trailing 0's
    while ((sig_digits % 10) == 0) {
      sig_digits /= 10;
      ++zeros;
    }
  }
  return zeros;
}

int smallest_difference(std::vector<int> a, const std::vector<int>& b) {
  // brute force: O(n_a n_b) check all pairs - requires no extra storage
  // this implementation:
  // -sort array a: O(n_a log(n_a))
  // -for each value in b, find the closest not-smaller-than-it
  // value in a and compare resulting difference: O(n_b log(n_a))
  // -overall: O((n_a + n_b) log(n_a))
  // -plus O(n_a) storage for sorted copy of a
  int min_diff = std::numeric_limits<int>::max();
  std::sort(a.begin(), a.end());
  for (int b_val : b) {
    auto a_gtr_than_b = std::lower_bound(a.begin(), a.end(), b_val);
    if (a_gtr_than_b != a.end()) {
      min_diff = std::min(min_diff, *a_gtr_than_b - b_val);
    }
  }
  return min_diff;
}