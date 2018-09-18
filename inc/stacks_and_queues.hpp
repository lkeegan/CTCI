#ifndef LKEEGAN_CTCI_STACKS_AND_QUEUES_H
#define LKEEGAN_CTCI_STACKS_AND_QUEUES_H
#include <algorithm>
#include <deque>
#include <queue>
#include <vector>

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
  void push(const T &item, int stack_index) {
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

#endif  // LKEEGAN_CTCI_STACKS_AND_QUEUES_H
