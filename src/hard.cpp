#include "hard.hpp"

unsigned int add_without_plus(unsigned int a, unsigned int b) {
  unsigned int result = 0;
  unsigned int bit = 0;
  unsigned int carry = 0;
  // keep adding until we have processed all non-zero bits in a & b
  while ((a > 0) || (b > 0)) {
    // get lsb of a and b
    unsigned int a_lsb = (a & 1);
    unsigned int b_lsb = (b & 1);
    // bitwise addition of a_lsb, b_lsb and carry bit
    // each addition is an XOR (0+0=0, 0+1=1+0=1, 1+1=0 [+carry])
    result |= (a_lsb ^ b_lsb ^ carry) << bit;
    // carry is 1 if there were least 2x 1's in a,b & carry,
    // e.g. a&b=1 or a&carry=1 or b&carry=1
    carry = (a_lsb & b_lsb) | (carry & (a_lsb | b_lsb));
    // shift a,b to the right by one bit
    a >>= 1;
    b >>= 1;
    // increment bit location
    ++bit;
  }
  // may be a final carry bit left over
  // that we need to include in result
  result |= carry << bit;
  return result;
}

unsigned int missing_number(const std::vector<unsigned int>& A) {
  // O(n) - assumes that A is sorted in ascending order
  for (unsigned int n = 0; n < static_cast<unsigned int>(A.size()); ++n) {
    // find location of bit that differs for n, n+1
    unsigned int bit = 0;
    unsigned int bit_differs = n ^ (n + 1);
    while ((bit_differs & 1) == 0) {
      bit_differs >>= 1;
      ++bit;
    }
    // if bit doesn't match for n, we have found missing value
    if (get_bit(bit, n, A) != (((n >> bit) & 1) != 0)) {
      return n;
    }
  }
  // if all matched return A.size(), i.e. missing value is n+1
  return A.size();
}

std::string longest_even_substring(const std::string& str,
                                   const std::string& NUMBER_CHARS) {
  // O(str.size() x NUMBER_CHARS.size())
  // convert any chars that match NUMBER_CHARS to +1, any other char to -1
  // start by assuming all -1's
  std::vector<int> val(str.size(), -1);
  int sum = -1 * static_cast<int>(str.size());
  // search for number_chars and flip appropriate
  // elemtnt of val from -1 to +1
  std::size_t i = str.find_first_of(NUMBER_CHARS);
  while (i != std::string::npos) {
    val[i] = +1;
    sum += 2;
    i = str.find_first_of(NUMBER_CHARS, i + 1);
  }
  std::size_t length = str.size();
  i = 0;
  // remove chars until substring is even
  while (sum != 0) {
    if (std::abs(sum - val[i]) < std::abs(sum)) {
      // if removing the first char brings us closer to even, do so
      sum -= val[i];
      ++i;
    } else {
      // otherwise remove last char
      sum -= val[i + length - 1];
    }
    --length;
  }
  return str.substr(i, length);
}

int count_of_twos_debug(int n) noexcept {
  // brute force for testing: O(n log_10(n))
  // look at every digit of every n
  int count = 0;
  while (n > 0) {
    int digit = n;
    while (digit > 0) {
      if (digit % 10 == 2) {
        ++count;
      }
      digit /= 10;
    }
    --n;
  }
  return count;
}

int count_of_twos(int n) noexcept {
  // better approach: O(log_10(n))
  int count = 0;             // running count of 2's
  int prev_pow10_count = 0;  // count of 2's from 0 to pow10/10
  int pow10 = 1;
  // sum all contributions from each digit of n
  while (n > pow10) {
    int digit = (n / pow10) % 10;
    // count currently contains count of 2's in numbers up to [xx...xx]
    // this is also the count for numbers of the form [digit][xx...xx]
    // then we need to add numbers of the form [{0,1,2,...,digit-1}][xx...xx]
    // where [xx...xx] can take any value up to [99...99]
    count += digit * prev_pow10_count;
    if (digit == 2) {
      // if digit=2, there are n%pow10+1 numbers starting with a
      // 2 that we need to count again to include the leading 2
      count += 1 + (n % pow10);
    } else if (digit > 2) {
      // if digit>2, then there are pow10 such numbers
      count += pow10;
    }
    // update count of 2's between 0 and pow10.
    // same logic as above for special case all digits=9:
    // 10 new leading digits for each previous number,
    // of which pow10 have leading 2's that need to be counted again
    prev_pow10_count = 10 * prev_pow10_count + pow10;
    pow10 *= 10;
  }
  return count;
}

void merge_synonyms(
    std::unordered_map<std::string, int>& frequencies,
    const std::vector<std::pair<std::string, std::string>>& name_pairs) {
  for (const auto& name_pair : name_pairs) {
    frequencies[name_pair.first] += frequencies[name_pair.second];
    frequencies.erase(name_pair.second);
  }
}

int majority_element(const std::vector<int>& arr) {
  // for N elements, majority element has N_m>N/2 entries

  // take first element, compare to following ones:
  // -once we have as many misses as hits x,
  //  can discard these elements: the majority element
  //  for the rest of the array remains unchanged
  //  [N_m > N/2] --> [N_m-x > (N-2x)/2] i.e. remains true
  auto iter = arr.cbegin();
  int element;
  int count = 1;  // count (hits - misses)
  while (iter != arr.end()) {
    element = *iter++;
    while (count > 0 && (iter != arr.end())) {
      (*iter == element) ? ++count : --count;
      ++iter;
    }
    count = 1;
  }
  // Given assumption that majority element exists we have found it
  // So need to check that assumption, i.e. is it majority for whole array?
  iter = arr.cbegin();
  count = 1;
  while (++iter != arr.end()) {
    if (*iter == element) {
      ++count;
    }
  }
  if (count > static_cast<int>(arr.size()) / 2) {
    return element;
  } else {
    return -1;
  }
}
