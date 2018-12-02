#ifndef LKEEGAN_CTCI_STACKS_AND_QUEUES_H
#define LKEEGAN_CTCI_STACKS_AND_QUEUES_H
#include <algorithm>
#include <deque>
#include <forward_list>
#include <limits>
#include <queue>
#include <stack>
#include <string>
#include <vector>

namespace ctci {
namespace stacks_and_queues {

// 3.1
// implement three stacks using a single array
template <class T>
class n_in_one {
  // n stacks: LIFO data structure
  // with items stored in vector/array
  // n-th stack is set of items in indices i%n of array
  // top item index for stack n stored in i_top[n]
  // so top item of stack n of N total stacks
  // is stored at stack[N*i_top[n] + n]
 private:
  int n_stacks;
  int array_size;
  std::vector<T> stack;
  std::vector<int> i_top;

  int top_index(int stack_index) const {
    return n_stacks * i_top[stack_index] + stack_index;
  }

  void grow_array() {
    array_size *= 2;
    stack.resize(array_size);
  }

 public:
  explicit n_in_one(int n_stacks = 3, int initial_stack_size = 1)
      : n_stacks(n_stacks),
        array_size(n_stacks * initial_stack_size),
        stack(n_stacks * initial_stack_size),
        i_top(n_stacks, -1){};

  // add item to stack in constant time
  // NB amortised constant, as we might have to grow array
  void push(const T& item, int stack_index) {
    if (top_index(stack_index) + n_stacks >= array_size) {
      grow_array();
    }
    ++i_top[stack_index];
    stack[top_index(stack_index)] = item;
  }
  // return read-only top item from stack (in constant time)
  T peek(int stack_index) const { return stack[top_index(stack_index)]; }
  // return and remove top item from stack (in constant time)
  T pop(int stack_index) {
    T tmp = stack[top_index(stack_index)];
    --i_top[stack_index];
    return tmp;
  }
  bool is_empty(int stack_index) const { return (i_top[stack_index] < 0); }
};

// 3.2
// a stack that can also return minimum element in O(1) time
// implemented as 2 stacks, one is the usual stack
// the second is a stack of the current minimum element
template <class T>
class stack_min {
 private:
  std::stack<T> s;
  std::stack<T> s_min;

 public:
  const T& min() const { return s_min.top(); }
  const T& top() const { return s.top(); }
  void push(const T& item) {
    s.push(item);
    if (s_min.empty() || item < s_min.top()) {
      s_min.push(item);
    } else {
      s_min.push(s_min.top());
    }
  }
  void pop() {
    s.pop();
    s_min.pop();
  }
  bool empty() { return s.empty(); }
  typename std::stack<T>::size_type size() { return s.size(); }
};

// 3.3
// a set of stacks that behaves like a normal stack
// but additionally one can pop from a sub-stack
// implemented as a vector of stacks
template <class T>
class set_of_stacks {
  using stack = std::stack<T>;

 private:
  std::vector<stack> s;
  typename stack::size_type max_stack_size;
  int element_count = 0;

 public:
  explicit set_of_stacks(typename stack::size_type max_size = 1024)
      : max_stack_size(max_size) {}
  void push(const T& item) {
    if (empty() || s.back().size() == max_stack_size) {
      s.push_back(stack());
    }
    s.back().push(item);
    ++element_count;
  }
  const T& peek() { return s.back().top(); }
  const T& peekAt(int index) { return s[index].top(); }
  T pop() { return popAt(s.size() - 1); }
  T popAt(int index) {
    typename std::vector<stack>::iterator it = s.begin() + index;
    T temp = (*it).top();
    (*it).pop();
    if ((*it).empty()) {
      s.erase(it);
    }
    --element_count;
    return temp;
  }
  bool empty() { return s.empty(); }
  int size() { return element_count; }
};

// 3.4
// queue (FIFO) implemented using two (LIFO) stacks
template <class T>
class queue_via_stacks {
  // average: O(1)
  // worst case: O(n)
  // queue.push: push to back stack
  // queue.pop: pop from front stack
  // if front stack is empty pop all items
  // from back stack and push to front stack
 private:
  std::stack<T> back, front;

 public:
  void push(const T& item) { back.push(item); }
  T pop() {
    if (front.empty()) {
      while (!back.empty()) {
        front.push(back.top());
        back.pop();
      }
    }
    T item = front.top();
    front.pop();
    return item;
  }
  bool empty() { return front.empty() && back.empty(); }
};

// 3.5
// sort stack -> smallest items at top (using only another temporary stack)
template <class T>
void sort_stack(std::stack<T>& s) {
  // O(n^2)
  // bubble sort the items between the two stacks
  // such that bottom half are in s in ascending order
  // and top half are in t is descending order
  // then combine to give all in s in ascending order
  std::stack<T> t;
  T lhs, rhs;
  // NB assuming we do not know the number of items in stack s
  int items_to_sort = std::numeric_limits<int>::max();
  // check for empty stack
  if (s.empty()) {
    return;
  }
  while (items_to_sort > 1) {
    // pop all unsorted items in s, push all except largest to t
    lhs = s.top();
    s.pop();
    // check for single item stack
    if (s.empty()) {
      items_to_sort = 1;
    }
    for (int i_item = 1; i_item < items_to_sort; ++i_item) {
      rhs = s.top();
      s.pop();
      if (lhs > rhs) {
        t.push(rhs);
      } else {
        t.push(lhs);
        lhs = rhs;
      }
      // for the first pass items_to_sort is not known
      // so we just keep iterating until s is empty
      // and count the number of items we have seen
      if (s.empty()) {
        items_to_sort = i_item + 1;
        break;
      }
    }
    // push largest to s
    s.push(lhs);
    --items_to_sort;
    // pop all unsorted items in t, push all except smallest to s
    if (items_to_sort > 1) {
      lhs = t.top();
      t.pop();
      for (int i_item = 1; i_item < items_to_sort; ++i_item) {
        rhs = t.top();
        t.pop();
        if (lhs < rhs) {
          s.push(rhs);
        } else {
          s.push(lhs);
          lhs = rhs;
        }
      }
      // push smallest to t
      t.push(lhs);
      --items_to_sort;
    }
  }
  // finally combine the two sorted stacks
  while (!t.empty()) {
    s.push(t.top());
    t.pop();
  }
}

// 3.6
// FIFO using linked list
// can either dequeue oldest animal of given species,
// or oldest animal of any species
namespace animal_shelter {
enum Species { CAT, DOG };
class animal {
 public:
  Species species;
  std::string name;
  explicit animal(Species species = CAT, const std::string& name = "")
      : species(species), name(name) {}
};
class queue {
 private:
  std::forward_list<animal> animal_list;
  std::forward_list<animal>::iterator oldest_animal =
      animal_list.before_begin();

 public:
  void enqueue(const animal& item);
  animal dequeue_any();
  animal dequeue(Species species);
};
}  // namespace animal_shelter

}  // namespace stacks_and_queues
}  // namespace ctci
#endif  // LKEEGAN_CTCI_STACKS_AND_QUEUES_H
