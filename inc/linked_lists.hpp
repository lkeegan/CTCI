#ifndef LKEEGAN_CTCI_LINKED_LISTS_H
#define LKEEGAN_CTCI_LINKED_LISTS_H
#include <algorithm>
#include <forward_list>
#include <iostream>  //for debugging
#include <list>
#include <unordered_map>

// 2.1
// remove duplicates from unsorted doubly-linked list
template <class T>
void remove_dups(std::list<T>& lst, bool USE_DATA_BUFFER = true) {
  using iter = typename std::list<T>::iterator;
  if (USE_DATA_BUFFER) {
    // use hash table to check if char has already been seen.
    // best case: O(N)
    // average: O(N)
    // worst case: O(N^2)
    std::unordered_map<T, bool> element_exists;
    for (iter i = lst.begin(); i != lst.end();) {
      if (element_exists[*i]) {
        // if this element already exists, erase from list
        i = lst.erase(i);
        // erase returns iterator pointing to next item in list
      } else {
        element_exists[*i] = true;
        ++i;
      }
    }
  } else {
    // No additional data structure used, instead:
    // for each item iterate over following items and remove duplicates
    // best case: O(N^2)
    // average: O(N^2)
    // worst case: O(N^2)
    for (iter i = lst.begin(); i != lst.end(); ++i) {
      for (iter j = std::next(i); j != lst.end();) {
        // remove all duplicates of item i
        if (*j == *i) {
          j = lst.erase(j);
        } else {
          ++j;
        }
      }
    }
  }
}

// 2.2
// return "k-th to last" element [last-k] of forward-linked list
template <class T>
T kth_to_last(const std::forward_list<T>& lst, int k = 0) {
  // iterate through list twice, only dereference desired element
  // if k is negative ignore sign
  // if k is too large, return first item in list
  // best case: O(N)
  // average: O(N)
  // worst case: O(N)
  using it = typename std::forward_list<T>::const_iterator;
  it k_before_last = lst.begin();
  it last = k_before_last;
  // advance "last" iterator by k items
  // treat k as positive, i.e. ignore minus sign
  // NB if we are sure k < number of items in list
  // could just do std::next(last, k) instead
  for (int i = 0; i < abs(k); ++i) {
    ++last;
    if (last == lst.end()) {
      // k too large: not enough elements in list
      // so just return first element
      return *k_before_last;
    }
  }
  // advance both iterators until last is at the end
  while (++last != lst.end()) {
    ++k_before_last;
  }
  // return item k items before last
  return *k_before_last;
}
#endif  // LKEEGAN_CTCI_LINKED_LISTS_H
