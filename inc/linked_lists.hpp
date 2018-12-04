#ifndef LKEEGAN_CTCI_LINKED_LISTS_H
#define LKEEGAN_CTCI_LINKED_LISTS_H
#include <algorithm>
#include <forward_list>
#include <list>
#include <memory>
#include <unordered_set>

namespace ctci {
namespace linked_lists {

template <class T>
struct dumb_list {
  T data;
  dumb_list* next = nullptr;
};

// simple single-linked list implementation
// each node contains a unique pointer to the next node
// and a value of type T
template <class T>
class single_list {
  typedef std::unique_ptr<single_list> list_uptr;

 private:
  T data;
  list_uptr next_node;

 public:
  explicit single_list(const T& d = T(), list_uptr n = list_uptr())
      : data(d), next_node(std::move(n)) {}
  single_list(const single_list&) = delete;
  single_list& operator=(const single_list&) = delete;
  ~single_list() = default;
  void delete_next() {
    if (next_node) {
      next_node = std::move(*next_node->next_node);
    }
  }
  void insert_after(const T& data) {
    next_node = list_uptr(new single_list(data, std::move(next_node)));
  }
  const T& get_value() const { return data; }
  void set_value(const T& new_data) { data = new_data; }
  single_list* next() const { return next_node.get(); }
  // give solution to 2.3 direct access to next_node pointer
  template <class S>
  friend void delete_middle_node(single_list<S>* lst);
};

// 2.1
// remove duplicates from unsorted doubly-linked list
template <class T>
void remove_dups(std::list<T>& lst, bool USE_DATA_BUFFER = true) {
  using iter = typename std::list<T>::iterator;
  if (USE_DATA_BUFFER) {
    // use hash table to check if element has already been seen.
    // best case: O(N)
    // average: O(N)
    // worst case: O(N^2)
    std::unordered_set<T> element_exists;
    for (iter i = lst.begin(); i != lst.end();) {
      if (element_exists.find(*i) != element_exists.end()) {
        // if this element already exists, erase from list
        i = lst.erase(i);
        // erase returns iterator pointing to next item in list
      } else {
        element_exists.insert(*i);
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

// 2.3
// "delete" given node without altering any other nodes
// if we can't modify the previous one that points to this one
// then put data from next one here and set this one to point to the one after
template <class T>
void delete_middle_node(single_list<T>* lst) {
  single_list<T>* nxt = lst->next();
  // set value of this node to value of next node
  lst->set_value(nxt->get_value());
  // set next node of this node to next-to-next node
  lst->next_node = std::move(nxt->next_node);
}

// 2.4
// rearrange order of list such that all items < x
// come before all items >= x
template <class T>
void partition(typename std::list<T>& lst, const T& x) {
  // O(N)
  typename std::list<T>::iterator smaller = lst.begin();
  typename std::list<T>::iterator larger = lst.end();
  --larger;
  while (smaller != larger) {
    // iterate forwards to an item >= x
    while (*smaller < x) {
      ++smaller;
    }
    // iterate backwards to an item < x
    while (*larger >= x && larger != smaller) {
      --larger;
    }
    // swap items
    std::swap(*smaller, *larger);
  }
}

// 2.5
// sum two numbers represented by digits listed in reverse order
// return sum in same format, e.g.
// 341+182=523: 1->4->3 + 2->8->1 = 3->2->5
std::list<int> sum_lists_backwards(const std::list<int>& lstA,
                                   const std::list<int>& lstB);
// ditto but with opposite ordering, e.g.
// 341+182=523: 3->4->1 + 1->8->2 = 5->2->3
std::list<int> sum_lists_forwards(const std::list<int>& lstA,
                                  const std::list<int>& lstB);

// 2.6
// check if list is palindrome
template <class T>
bool palindrome(const typename std::list<T>& lst) {
  // O(N)
  typename std::list<T>::const_iterator fwds = lst.begin();
  typename std::list<T>::const_iterator back = lst.end();
  --back;
  while (fwds != back) {
    // check items match
    if (*fwds != *back) {
      return false;
    }
    // increment in both directions
    ++fwds;
    if (fwds != back) {
      --back;
    }
  }
  return true;
}

// 2.7
// check if two single-link lists (of pointers) intersect, i.e.
// both contain a pointer to the same address,
// and return this address
template <class T>
T intersection(const typename std::forward_list<T>& lstA,
               const typename std::forward_list<T>& lstB) {
  // average: O(N)
  // worst case: O(N^2)
  // hash map of pointers in A
  std::unordered_set<T> seen_pointer;
  for (T a : lstA) {
    seen_pointer.insert(a);
  }
  // iterate through B, checking if each item was in A
  for (T b : lstB) {
    if (seen_pointer.find(b) != seen_pointer.end()) {
      return b;
    }
  }
  // if not found, return default (i.e. nullptr if T is a pointer)
  return T();
}

// 2.8
// check if single linked list contains a cycle
// if so return node at beginning of loop
template <class T>
dumb_list<T>* loop_detection(dumb_list<T>* node) {
  // average: O(N)
  // worst case: O(N^2)
  // hash map of pointers in A
  std::unordered_set<dumb_list<T>*> nodes{node};
  while (node->next) {
    node = node->next;
    if (nodes.find(node) != nodes.end()) {
      return node;
    } else {
      nodes.insert(node);
    }
  }
  return nullptr;
}

}  // namespace linked_lists
}  // namespace ctci
#endif  // LKEEGAN_CTCI_LINKED_LISTS_H
