#include "linked_lists.hpp"

std::list<int> sum_lists_backwards(const std::list<int>& lstA,
                                   const std::list<int>& lstB) {
  // O(N)
  std::list<int> lstS;
  std::list<int>::const_iterator a = lstA.begin();
  std::list<int>::const_iterator b = lstB.begin();
  int carry = 0;
  while (a != lstA.end() || b != lstB.end()) {
    int sum = carry;
    if (a != lstA.end()) {
      sum += *a;
      ++a;
    }
    if (b != lstB.end()) {
      sum += *b;
      ++b;
    }
    lstS.push_back(sum % 10);
    carry = sum / 10;
  }
  lstS.push_back(carry);
  // remove leading zeros
  std::list<int>::iterator s = lstS.end();
  while (*(--s) == 0) {
    lstS.erase(s);
  }
  return lstS;
}

std::list<int> sum_lists_forwards(const std::list<int>& lstA,
                                  const std::list<int>& lstB) {
  // O(N)
  std::list<int> lstS;
  std::list<int>::const_reverse_iterator a = lstA.rbegin();
  std::list<int>::const_reverse_iterator b = lstB.rbegin();
  int carry = 0;
  while (a != lstA.rend() || b != lstB.rend()) {
    int sum = carry;
    if (a != lstA.rend()) {
      sum += *a;
      ++a;
    }
    if (b != lstB.rend()) {
      sum += *b;
      ++b;
    }
    lstS.push_front(sum % 10);
    carry = sum / 10;
  }
  lstS.push_front(carry);
  // remove leading zeros
  std::list<int>::iterator s = lstS.begin();
  while (*s == 0) {
    s = lstS.erase(s);
  }
  return lstS;
}