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
