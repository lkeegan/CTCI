#include "stacks_and_queues.hpp"
#include "catch.hpp"

// Unit tests

TEST_CASE("three_in_one", "[stacks_and_queues]") {
  n_in_one<double> s(3);
  s.push(1.0, 0);
  s.push(2.0, 0);
  s.push(8.0, 1);
  s.push(4.0, 1);
  s.push(-1.0, 2);
  REQUIRE(s.is_empty(0) == false);
  REQUIRE(s.is_empty(1) == false);
  REQUIRE(s.is_empty(2) == false);
  REQUIRE(s.peek(0) == 2.0);
  s.push(3.0, 0);
  REQUIRE(s.peek(0) == 3.0);
  REQUIRE(s.pop(0) == 3.0);
  REQUIRE(s.peek(0) == 2.0);
  REQUIRE(s.pop(2) == -1.0);
  REQUIRE(s.is_empty(2) == true);
}

TEST_CASE("stack_min", "[stacks_and_queues]") {
  stack_min<int> s;
  REQUIRE(s.empty() == true);
  s.push(2);
  REQUIRE(s.top() == 2);
  REQUIRE(s.min() == 2);
  REQUIRE(s.size() == 1);
  REQUIRE(s.empty() == false);
  s.push(4);
  REQUIRE(s.top() == 4);
  REQUIRE(s.min() == 2);
  s.push(1);
  REQUIRE(s.top() == 1);
  REQUIRE(s.min() == 1);
  s.push(7);
  REQUIRE(s.top() == 7);
  REQUIRE(s.min() == 1);
  s.push(-1);
  REQUIRE(s.top() == -1);
  REQUIRE(s.min() == -1);
  s.push(1);
  REQUIRE(s.top() == 1);
  REQUIRE(s.min() == -1);
  s.pop();
  REQUIRE(s.top() == -1);
  REQUIRE(s.min() == -1);
  s.pop();
  REQUIRE(s.top() == 7);
  REQUIRE(s.min() == 1);
  s.pop();
  s.pop();
  REQUIRE(s.top() == 4);
  REQUIRE(s.min() == 2);
  s.pop();
  REQUIRE(s.top() == 2);
  REQUIRE(s.min() == 2);
  s.pop();
  REQUIRE(s.empty() == true);
}

TEST_CASE("set_of_stacks", "[stacks_and_queues]") {
  // stack which is internally a vector of stacks of size 2
  // behaves like normal stack: push, pop, peek, empty
  // additionally can popAt(index) from a sub-stack
  set_of_stacks<uint> s(2);
  REQUIRE(s.empty() == true);
  s.push(2);
  REQUIRE(s.peek() == 2);
  REQUIRE(s.size() == 1);
  REQUIRE(s.empty() == false);
  s.push(4);
  REQUIRE(s.peek() == 4);
  REQUIRE(s.size() == 2);
  s.push(1);
  REQUIRE(s.peek() == 1);
  REQUIRE(s.peekAt(0) == 4);
  REQUIRE(s.peekAt(1) == 1);
  REQUIRE(s.size() == 3);
  s.push(7);
  s.push(11);
  REQUIRE(s.peek() == 11);
  REQUIRE(s.peekAt(0) == 4);
  REQUIRE(s.peekAt(1) == 7);
  REQUIRE(s.size() == 5);
  // pop from 0-th stack
  REQUIRE(s.popAt(0) == 4);
  REQUIRE(s.peek() == 11);
  REQUIRE(s.peekAt(0) == 2);
  REQUIRE(s.size() == 4);
  // pop from 0-th stack
  REQUIRE(s.popAt(0) == 2);
  REQUIRE(s.peek() == 11);
  REQUIRE(s.peekAt(0) == 7);
  REQUIRE(s.size() == 3);
  // pop from 0-th stack
  REQUIRE(s.popAt(0) == 7);
  REQUIRE(s.peek() == 11);
  REQUIRE(s.peekAt(0) == 1);
  REQUIRE(s.size() == 2);
  // pop from 0-th stack
  REQUIRE(s.popAt(0) == 1);
  REQUIRE(s.peek() == 11);
  REQUIRE(s.peekAt(0) == 11);
  REQUIRE(s.size() == 1);
  // pop from top
  REQUIRE(s.pop() == 11);
  REQUIRE(s.empty() == true);
}

TEST_CASE("sort_stack", "[stacks_and_queues]") {
  // sort stack using only another stack as temp storage
  std::stack<int> s;

  // trivial empty stack
  sort_stack(s);

  // trivial single item stack
  s.push(123);
  sort_stack(s);
  REQUIRE(s.top() == 123);
  s.pop();
  REQUIRE(s.empty() == true);

  // 2 item stack
  s.push(123);
  s.push(344);
  sort_stack(s);
  REQUIRE(s.top() == 123);
  s.pop();
  REQUIRE(s.top() == 344);
  s.pop();
  REQUIRE(s.empty() == true);

  // longer stack including duplicates
  s.push(4);
  s.push(8);
  s.push(-3);
  s.push(3);
  s.push(1);
  s.push(8);
  s.push(7);
  s.push(12);
  sort_stack(s);
  REQUIRE(s.top() == -3);
  s.pop();
  REQUIRE(s.top() == 1);
  s.pop();
  REQUIRE(s.top() == 3);
  s.pop();
  REQUIRE(s.top() == 4);
  s.pop();
  REQUIRE(s.top() == 7);
  s.pop();
  REQUIRE(s.top() == 8);
  s.pop();
  REQUIRE(s.top() == 8);
  s.pop();
  REQUIRE(s.top() == 12);
  s.pop();
  REQUIRE(s.empty() == true);
}