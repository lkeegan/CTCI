#include "linked_lists.hpp"

namespace ctci {
namespace linked_lists {

std::list<int> sum_lists_backwards(const std::list<int>& lstA,
                                   const std::list<int>& lstB) {
  // O(N)
  std::list<int> lstS;
  std::list<int>::const_iterator a = lstA.begin();
  std::list<int>::const_iterator b = lstB.begin();
  int carry = 0;
  while ((a != lstA.end()) || (b != lstB.end())) {
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
  while ((lstS.back() == 0) && (!lstS.empty())) {
    lstS.pop_back();
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
  while ((lstS.front() == 0) && (!lstS.empty())) {
    lstS.pop_front();
  }
  return lstS;
}

}  // namespace linked_lists
}  // namespace ctci