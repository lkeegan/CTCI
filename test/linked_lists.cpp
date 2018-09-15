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

TEST_CASE("delete_middle_node", "[linked_lists]") {
  std::forward_list<int> l{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::forward_list<int>::iterator i = l.begin();
  ++i;
  delete_middle_node(l, i);
  REQUIRE(l == std::forward_list<int>{0, 2, 3, 4, 5, 6, 7, 8, 9, 10});
  i = l.begin();
  ++i;
  ++i;
  delete_middle_node(l, i);
  REQUIRE(l == std::forward_list<int>{0, 2, 4, 5, 6, 7, 8, 9, 10});
  i = l.begin();
  ++i;
  ++i;
  ++i;
  ++i;
  delete_middle_node(l, i);
  REQUIRE(l == std::forward_list<int>{0, 2, 4, 5, 7, 8, 9, 10});
}

TEST_CASE("partition", "[linked_lists]") {
  std::list<int> l{-4, 12, 6, 2, 5, 0, 10, 5, 7, 6, 2, -1, 66, 7, 6, -21, 1};
  partition(l, 6);
  std::list<int>::const_iterator i = l.begin();
  for (int count = 0; count < 9; ++count) {
    REQUIRE(*i < 6);
    ++i;
  }
  while (i != l.end()) {
    REQUIRE(*i >= 6);
    ++i;
  }
}

TEST_CASE("sum_lists", "[linked_lists]") {
  std::list<int> lstA{9, 3, 5, 7};
  std::list<int> lstB{3, 2, 1, 4};
  std::list<int> lstS_b{2, 6, 6, 1, 1};
  std::list<int> lstS_f{1, 2, 5, 7, 1};
  REQUIRE(sum_lists_backwards(lstA, lstB) == lstS_b);
  REQUIRE(sum_lists_backwards(lstB, lstA) == lstS_b);
  REQUIRE(sum_lists_forwards(lstA, lstB) == lstS_f);
  REQUIRE(sum_lists_forwards(lstB, lstA) == lstS_f);

  lstA = std::list<int>{0, 9, 1};
  lstB = std::list<int>{9, 8};
  lstS_b = std::list<int>{9, 7, 2};
  lstS_f = std::list<int>{1, 8, 9};
  REQUIRE(sum_lists_backwards(lstA, lstB) == lstS_b);
  REQUIRE(sum_lists_backwards(lstB, lstA) == lstS_b);
  REQUIRE(sum_lists_forwards(lstA, lstB) == lstS_f);
  REQUIRE(sum_lists_forwards(lstB, lstA) == lstS_f);

  lstA = std::list<int>{};
  lstB = std::list<int>{9, 8};
  lstS_b = std::list<int>{9, 8};
  lstS_f = std::list<int>{9, 8};
  REQUIRE(sum_lists_backwards(lstA, lstB) == lstS_b);
  REQUIRE(sum_lists_backwards(lstB, lstA) == lstS_b);
  REQUIRE(sum_lists_forwards(lstA, lstB) == lstS_f);
  REQUIRE(sum_lists_forwards(lstB, lstA) == lstS_f);

  lstA = std::list<int>{0, 1, 0, 0};
  lstB = std::list<int>{9, 8};
  lstS_b = std::list<int>{9, 9};
  lstS_f = std::list<int>{1, 9, 8};
  REQUIRE(sum_lists_backwards(lstA, lstB) == lstS_b);
  REQUIRE(sum_lists_backwards(lstB, lstA) == lstS_b);
  REQUIRE(sum_lists_forwards(lstA, lstB) == lstS_f);
  REQUIRE(sum_lists_forwards(lstB, lstA) == lstS_f);
}

TEST_CASE("palindrome", "[linked_lists]") {
  REQUIRE(palindrome(std::list<char>{}) == true);
  REQUIRE(palindrome(std::list<char>{'a'}) == true);
  REQUIRE(palindrome(std::list<char>{'a', 'a'}) == true);
  REQUIRE(palindrome(std::list<char>{'a', 'b'}) == false);
  REQUIRE(palindrome(std::list<char>{'a', 'b', 'a'}) == true);
  REQUIRE(palindrome(std::list<char>{'a', 'b', 'b', 'a'}) == true);
  REQUIRE(palindrome(std::list<char>{'a', 'b', '?', 'b', 'a'}) == true);
  REQUIRE(palindrome(std::list<char>{'a', 'b', 'c'}) == false);
  REQUIRE(palindrome(std::list<char>{'a', 'a', 'b'}) == false);
}

TEST_CASE("intersection", "[linked_lists]") {
  double a = 1.0;
  double b = 3.0;
  double c = 5.0;
  double d = 8.0;
  double e = 8.0;
  std::forward_list<double*> lstA{&a, &b, &c};
  std::forward_list<double*> lstB{&d, &a};
  std::forward_list<double*> lstC{&b, &e};
  REQUIRE(intersection(lstA, lstB) == &a);
  REQUIRE(intersection(lstA, lstC) == &b);
  REQUIRE(intersection(lstB, lstC) == nullptr);
}

TEST_CASE("loop_detection", "[linked_lists]") {
  double a = 1.0;
  double b = 3.0;
  double c = 5.0;
  double d = 8.0;
  double e = 8.0;
  std::forward_list<double*> lst{&a, &b, &c, &d, &e, &b};
  REQUIRE(loop_detection(lst) == &b);
}