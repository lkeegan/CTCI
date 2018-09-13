#include "arrays_and_strings.h"
#include "catch.hpp"

// Unit tests

TEST_CASE("is_unique_a", "[arrays_and_strings]") {
  REQUIRE(is_unique_a("11") == false);
  REQUIRE(is_unique_a("abc") == true);
  REQUIRE(is_unique_a("123 876-x") == true);
  REQUIRE(is_unique_a("abcda") == false);
  REQUIRE(is_unique_a("abcXzX") == false);
}

TEST_CASE("is_unique_b", "[arrays_and_strings]") {
  REQUIRE(is_unique_b("11") == false);
  REQUIRE(is_unique_b("abc") == true);
  REQUIRE(is_unique_b("123 876-x") == true);
  REQUIRE(is_unique_b("abcda") == false);
  REQUIRE(is_unique_b("abcXzX") == false);
}

TEST_CASE("check_permutation", "[arrays_and_strings]") {
  REQUIRE(check_permutation("aa", "ab") == false);
  REQUIRE(check_permutation("abc", "bca") == true);
  REQUIRE(check_permutation("aab", "aba") == true);
  REQUIRE(check_permutation("aaabtbtbt", "aaabtbtbt") == true);
  REQUIRE(check_permutation("aaabtbtbt", "aaabtbtbb") == false);
  REQUIRE(check_permutation("", "") == true);
  REQUIRE(check_permutation("", "a") == false);
  REQUIRE(check_permutation("Abesg", "gesbA") == true);
}

TEST_CASE("URLify", "[arrays_and_strings]") {
  std::string str;

  str = "";
  URLify(str, 0);
  REQUIRE(str == "");

  str = "   ";
  URLify(str, 1);
  REQUIRE(str == "%20");

  str = "abc";
  URLify(str, 3);
  REQUIRE(str == "abc");

  str = "a bc  ";
  URLify(str, 4);
  REQUIRE(str == "a%20bc");

  str = "a b c       ";
  URLify(str, 5);
  REQUIRE(str == "a%20b%20c   ");

  str = "a b c       ";
  URLify(str, 6);
  REQUIRE(str == "a%20b%20c%20");

  str = "a   b                 ";
  URLify(str, 5);
  REQUIRE(str == "a%20%20%20b           ");
}

TEST_CASE("is_permutation_of_palindrome", "[arrays_and_strings]") {
  REQUIRE(is_permutation_of_palindrome("") == true);
  REQUIRE(is_permutation_of_palindrome("a") == true);
  REQUIRE(is_permutation_of_palindrome("aa") == true);
  REQUIRE(is_permutation_of_palindrome("aba") == true);
  REQUIRE(is_permutation_of_palindrome("cacaca") == false);
  REQUIRE(is_permutation_of_palindrome("b aa") == true);
  REQUIRE(is_permutation_of_palindrome("Zs qZZsq sqZq s") == true);
  REQUIRE(is_permutation_of_palindrome("abasdfRQ") == false);
  REQUIRE(is_permutation_of_palindrome("aaa") == true);
  REQUIRE(is_permutation_of_palindrome("ksjdhf") == false);
}