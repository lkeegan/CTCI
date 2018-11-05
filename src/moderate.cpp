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

std::string english_int(unsigned long long int number) {
  std::array<std::string, 20> digits{
      "",        "One",     "Two",       "Three",    "Four",
      "Five",    "Six",     "Seven",     "Eight",    "Nine",
      "Ten",     "Eleven",  "Twelve",    "Thirteen", "Fourteen",
      "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
  std::array<std::string, 10> tens{"",       "",      "Twenty", "Thirty",
                                   "Forty",  "Fifty", "Sixty",  "Seventy",
                                   "Eighty", "Ninety"};
  // assuming ULL int can go up to 2^64-1 < 10^20
  // can safely express any number in this range with
  // powers of 1000 up to 7, i.e. 10^21 == Sextillion:
  // https://simple.wikipedia.org/wiki/Names_for_large_numbers
  std::array<std::string, 8> thousand_to_nth_power{
      "",          " Thousand",    " Million",     " Billion",
      " Trillion", " Quadrillion", " Quintillion", " Sextillion"};
  auto str_thousand_power = thousand_to_nth_power.begin();
  std::string int_as_text;
  while (number > 0) {
    if (int_as_text.size() > 0) {
      // add space between previous part and new part
      int_as_text = " " + int_as_text;
    }
    // text for 3rd least significant digit (hundreds)
    std::string str_ls3;
    int ls3 = (number % 1000) / 100;
    int ls2 = number % 100;
    if (ls3 > 0) {
      str_ls3 = digits[ls3] + " Hundred";
      if (ls2 > 0) {
        // if there is more to come, add a space
        str_ls3 += " ";
      }
    }
    // text for two least significant digits (0-99)
    if (ls2 < 20) {
      // 1-19
      str_ls3 += digits[ls2];
    } else {
      // 20-99
      str_ls3 += tens[ls2 / 10];
      if (ls2 % 10 > 0) {
        str_ls3 += " " + digits[ls2 % 10];
      }
    }
    // add text from these 3 digits to result
    if (str_ls3.size() > 0) {
      int_as_text = str_ls3 + *str_thousand_power + int_as_text;
    }
    // remove last 3 digits from number
    number /= 1000;
    // increment 10^3 factor
    ++str_thousand_power;
  }
  return int_as_text;
}

// a - b
int operations_minus(int a, int b) {
  if (a < b) {
    return -operations_minus(b, a);
  }
  int result = 0;
  while (a > b) {
    ++b;
    ++result;
  }
  return result;
}

// a * b
int operations_multiply(int a, int b) {
  // if a, b have opposite sign, result will be negative
  bool result_neg = ((a < 0) != (b < 0));
  // multiply abs(a) and abs(b)
  int result = 0;
  for (int i = 0; i < abs(b); ++i) {
    result += abs(a);
  }
  // return result with correct sign
  return result_neg ? -result : result;
}
// a / b
int operations_divide(int a, int b) {
  // if a, b have opposite sign, result will be negative
  bool result_neg = ((a < 0) != (b < 0));
  int result = 0;
  int mult = abs(b);
  // do abs(a) / abs(b)
  while (mult <= abs(a)) {
    ++result;
    mult += abs(b);
  }
  // return result with correct sign
  return result_neg ? -result : result;
}

int year_with_most_people(
    const std::vector<std::pair<int, int>>& birth_death_years) {
  // O(n) for n people
  constexpr int MIN_YEAR = 1900;
  constexpr int MAX_YEAR = 2000;
  constexpr int N_YEARS = MAX_YEAR - MIN_YEAR + 1;
  // delta[i] = n : change of n in net for year i + MIN_YEAR
  // e.g. a birth in year y --> +1 at year y
  // and a death in year z --> -1 at year z+1
  std::array<int, N_YEARS + 1> delta_people{};
  for (const auto& p : birth_death_years) {
    ++delta_people[p.first - MIN_YEAR];       // birth (at start of year)
    --delta_people[p.second + 1 - MIN_YEAR];  // death (at end of year)
  }
  int max_count = 0;
  int cur_count = 0;
  std::size_t max_i = 0;
  for (std::size_t i = 0; i < delta_people.size(); ++i) {
    cur_count += delta_people[i];
    if (cur_count > max_count) {
      max_count = cur_count;
      max_i = i;
    }
  }
  return static_cast<int>(max_i + MIN_YEAR);
}

std::unordered_set<int> enumerate_lengths(int k, int shorter, int longer) {
  std::unordered_set<int> lengths;
  // s shorter + l longer = length
  // for all (s,l) such that s + l = k
  for (int l = 0; l <= k; ++l) {
    int s = k - l;
    int length = s * shorter + l * longer;
    // add to unordered_set to ignore duplicates
    lengths.insert(length);
  }
  return lengths;
}

int rand7(rand_n& rand5) {
  // amortised cost = (50/21) ~ 2.5x rand5() calls
  // stochastically have 21/25 chance of getting a rand7
  // for each pair of rand5() calls
  int r7 = 7;
  while (r7 > 6) {
    // get flat sample in [0,25)
    // using 2x rand5 calls:
    r7 = rand5() + 5 * rand5();
    // divide by 3
    r7 /= 3;
    // {0,1,2}->0, {3,4,5}->1, ..., {18,19,20}->6,
    // {21,22,23}->7, {24}->8
    // i.e. flat distrib in [0,7)
    // plus 4/25 chance of higher number, in which case
    // we discard it and try again
  }
  return r7;
}