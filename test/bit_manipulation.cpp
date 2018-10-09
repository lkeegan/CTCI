#include "bit_manipulation.hpp"
#include "catch.hpp"

// Unit tests

TEST_CASE("insertion", "[bit_manipulation]") {
  int N = 4096 + 1024 + 512 + 8 + 2 + 1;  // 1011000001011
  int M = 8 + 4 + 1;                      // [1101]
  int answer = N + M * (1 << 5);          // 1011[1101]01011
  REQUIRE(insertion(N, M, 5, 8) == answer);

  // wrong size of i,j for M:
  REQUIRE_THROWS_AS(insertion(N, M, 1, 9), std::invalid_argument);
  REQUIRE_THROWS_AS(insertion(N, M, 1, 2), std::invalid_argument);
  // N doesn't have zeros where M should go:
  REQUIRE_THROWS_AS(insertion(N + 256 + 128, M, 5, 8), std::invalid_argument);
  REQUIRE_THROWS_AS(insertion(N, M, 6, 9), std::invalid_argument);
}

TEST_CASE("flip_bit_to_win", "[bit_manipulation]") {
  REQUIRE(flip_bit_to_win(0) == 1);
  REQUIRE(flip_bit_to_win(1) == 2);
  REQUIRE(flip_bit_to_win(2 + 1) == 3);
  REQUIRE(flip_bit_to_win(4 + 1) == 3);
  REQUIRE(flip_bit_to_win(8 + 4 + 1) == 4);
  REQUIRE(flip_bit_to_win(128 + 64 + 32 + 8 + 4 + 1) == 6);
  REQUIRE(flip_bit_to_win(1024 + 512 + 128 + 64 + 16 + 8 + 2 + 1) == 5);
}

TEST_CASE("next_number", "[bit_manipulation]") {
  int smaller, larger;
  REQUIRE_THROWS_AS(next_number(0, smaller, larger), std::invalid_argument);
  REQUIRE_THROWS_AS(next_number(1, smaller, larger), std::invalid_argument);
  REQUIRE_THROWS_AS(next_number(16 + 8 + 4 + 2 + 1, smaller, larger),
                    std::invalid_argument);
  next_number(8 + 2 + 1, smaller, larger);
  REQUIRE(smaller == 4 + 2 + 1);
  REQUIRE(larger == 8 + 4 + 1);
  next_number(16 + 8 + 2, smaller, larger);
  REQUIRE(smaller == 16 + 8 + 1);
  REQUIRE(larger == 16 + 8 + 4);
}

TEST_CASE("debugger", "[bit_manipulation]") {
  REQUIRE(debugger(0) == true);
  REQUIRE(debugger(1) == true);
  REQUIRE(debugger(2) == true);
  REQUIRE(debugger(3) == false);
  REQUIRE(debugger(4) == true);
  REQUIRE(debugger(15) == false);
  REQUIRE(debugger(16) == true);
  REQUIRE(debugger(1023) == false);
  REQUIRE(debugger(1024) == true);
  REQUIRE(debugger(1 << 17) == true);
  REQUIRE(debugger((1 << 17) + 1) == false);
  REQUIRE(debugger(1 << 30) == true);
  REQUIRE(debugger((1 << 30) - 1) == false);
  REQUIRE(debugger(-1) == false);
  REQUIRE(debugger(-2) == false);
}

TEST_CASE("conversion", "[bit_manipulation]") {
  REQUIRE(conversion(29, 15) == 2);
  REQUIRE(conversion(15, 29) == 2);
  REQUIRE(conversion(16 + 8 + 4 + 2, 1) == 5);
  REQUIRE(conversion(64 + 16 + 4 + 1, 128 + 64 + 32 + 8 + 1) == 5);
}

// e.g. 1101 -> 1110
TEST_CASE("pairwise_swap", "[bit_manipulation") {
  REQUIRE(pairwise_swap(0) == 0);
  REQUIRE(pairwise_swap(1) == 2);
  REQUIRE(pairwise_swap(2) == 1);
  REQUIRE(pairwise_swap(8 + 4 + 1) == 8 + 4 + 2);
  REQUIRE(pairwise_swap(8 + 4 + 2) == 8 + 4 + 1);
  REQUIRE(pairwise_swap(32 + 8 + 4 + 1) == 16 + 8 + 4 + 2);
  REQUIRE(pairwise_swap(16 + 8 + 4 + 2) == 32 + 8 + 4 + 1);
}
