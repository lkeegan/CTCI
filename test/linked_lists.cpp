#include "linked_lists.hpp"
#include "catch.hpp"

// Unit tests

TEST_CASE("remove_dups", "[linked_lists]") {
  for (bool USE_DATA_BUFFER : {true, false}) {
    SECTION("USE_DATA_BUFFER = " + std::to_string(USE_DATA_BUFFER)) {
      std::list<int> l_dups, l_no_dups;

      l_dups = std::list<int>{};
      l_no_dups = std::list<int>{};
      remove_dups(l_dups, USE_DATA_BUFFER);
      REQUIRE(l_dups == l_no_dups);

      l_dups = std::list<int>{1, 2, 3};
      l_no_dups = std::list<int>{1, 2, 3};
      remove_dups(l_dups, USE_DATA_BUFFER);
      REQUIRE(l_dups == l_no_dups);

      l_dups = std::list<int>{1, 2, 3, 1, 1, 5, 8, 4, 2, 7, 2, 3};
      l_no_dups = std::list<int>{1, 2, 3, 5, 8, 4, 7};
      remove_dups(l_dups, USE_DATA_BUFFER);
      REQUIRE(l_dups == l_no_dups);

      l_dups = std::list<int>{1, 1, 1, 1, 1, 1};
      l_no_dups = std::list<int>{1};
      remove_dups(l_dups, USE_DATA_BUFFER);
      REQUIRE(l_dups == l_no_dups);

      std::list<std::string> s_dups{"abs", "reg", "abs", "htt"};
      std::list<std::string> s_no_dups{"abs", "reg", "htt"};
      remove_dups(s_dups, USE_DATA_BUFFER);
      REQUIRE(s_dups == s_no_dups);
    }
  }
}

TEST_CASE("kth_to_last", "[linked_lists]") {
  std::forward_list<int> l{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  REQUIRE(kth_to_last(l, 0) == 10);
  REQUIRE(kth_to_last(l, 1) == 9);
  REQUIRE(kth_to_last(l, 5) == 5);
  REQUIRE(kth_to_last(l, -5) == 5);  // treats -k as k
  REQUIRE(kth_to_last(l, 10) == 0);
  REQUIRE(kth_to_last(l, 11) == 0);  // for k too large returns first item
  REQUIRE(kth_to_last(l, 200) == 0);
}