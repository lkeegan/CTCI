#include "arrays_and_strings.hpp"
#include "catch.hpp"

// Unit tests
using namespace CTCI::arrays_and_strings;

TEST_CASE("is_unique_a", "[arrays_and_strings]") {
  REQUIRE(is_unique_a("") == true);
  REQUIRE(is_unique_a("c") == true);
  REQUIRE(is_unique_a("11") == false);
  REQUIRE(is_unique_a("abc") == true);
  REQUIRE(is_unique_a("123 876-x") == true);
  REQUIRE(is_unique_a("abcda") == false);
  REQUIRE(is_unique_a("abcXzX") == false);
  REQUIRE(is_unique_a(std::string(150, 'a')) == false);
}

TEST_CASE("is_unique_b", "[arrays_and_strings]") {
  REQUIRE(is_unique_a("") == true);
  REQUIRE(is_unique_a("c") == true);
  REQUIRE(is_unique_b("11") == false);
  REQUIRE(is_unique_b("abc") == true);
  REQUIRE(is_unique_b("123 876-x") == true);
  REQUIRE(is_unique_b("abcda") == false);
  REQUIRE(is_unique_b("abcXzX") == false);
  REQUIRE(is_unique_b(std::string(150, 'a')) == false);
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

  str = "";
  REQUIRE_THROWS_AS(URLify(str, 1), std::invalid_argument);

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

TEST_CASE("one_away", "[arrays_and_strings]") {
  REQUIRE(one_away("", "") == true);
  REQUIRE(one_away("abc", "abc") == true);
  REQUIRE(one_away("abc", "abd") == true);
  REQUIRE(one_away("abc", "ab") == true);
  REQUIRE(one_away("abc", "bc") == true);
  REQUIRE(one_away("abc", "ac") == true);
  REQUIRE(one_away("abcd", "bcd") == true);
  REQUIRE(one_away("ab", "abr") == true);
  REQUIRE(one_away("cd", "Qcd") == true);
  REQUIRE(one_away("cd", "cQd") == true);
  REQUIRE(one_away("", "  ") == false);
  REQUIRE(one_away("abc", "acb") == false);
  REQUIRE(one_away("abc", "abcde") == false);
  REQUIRE(one_away("abc", "ba") == false);
  REQUIRE(one_away("abc", "bca") == false);
  REQUIRE(one_away("abc", "a") == false);
  REQUIRE(one_away("abcd", "bdca") == false);
  REQUIRE(one_away("ab", "a b ") == false);
  REQUIRE(one_away("cd", "cd  ") == false);
  REQUIRE(one_away("cd", " cd ") == false);
}

TEST_CASE("string_compression", "[arrays_and_strings]") {
  REQUIRE(string_compression("abc") == "abc");
  REQUIRE(string_compression("aaabbc") == "aaabbc");
  REQUIRE(string_compression("aaabbbc") == "a3b3c1");
  REQUIRE(string_compression("aaaaabbbcCCC") == "a5b3c1C3");
}

TEST_CASE("rotate_matrix", "[arrays_and_strings]") {
  matrix m1(1);
  m1[0] = {1};
  rotate_matrix(m1);
  matrix m1r(1);
  m1r[0] = {1};
  REQUIRE(m1[0] == m1r[0]);

  matrix m2(2);
  m2[0] = {1, 2};
  m2[1] = {3, 4};
  rotate_matrix(m2);
  matrix m2r(2);
  m2r[0] = {3, 1};
  m2r[1] = {4, 2};
  REQUIRE(m2[0] == m2r[0]);
  REQUIRE(m2[1] == m2r[1]);

  matrix m3(3);
  m3[0] = {1, 2, 3};
  m3[1] = {4, 5, 6};
  m3[2] = {7, 8, 9};
  rotate_matrix(m3);
  matrix m3r(3);
  m3r[0] = {7, 4, 1};
  m3r[1] = {8, 5, 2};
  m3r[2] = {9, 6, 3};
  REQUIRE(m3[0] == m3r[0]);
  REQUIRE(m3[1] == m3r[1]);
  REQUIRE(m3[2] == m3r[2]);
}

TEST_CASE("zero_matrix", "[arrays_and_strings]") {
  matrix m1(1);
  m1[0] = {1};
  zero_matrix(m1);
  matrix m1r(1);
  m1r[0] = {1};
  REQUIRE(m1[0] == m1r[0]);

  m1 = matrix(1);
  m1[0] = {0};
  zero_matrix(m1);
  m1r = matrix(1);
  m1r[0] = {0};
  REQUIRE(m1[0] == m1r[0]);

  matrix m2(2);
  m2[0] = {1, 0};
  m2[1] = {3, 4};
  zero_matrix(m2);
  matrix m2r(2);
  m2r[0] = {0, 0};
  m2r[1] = {3, 0};
  REQUIRE(m2[0] == m2r[0]);
  REQUIRE(m2[1] == m2r[1]);

  m2 = matrix(2);
  m2[0] = {1, 2};
  m2[1] = {3, 4};
  zero_matrix(m2);
  m2r = matrix(2);
  m2r[0] = {1, 2};
  m2r[1] = {3, 4};
  REQUIRE(m2[0] == m2r[0]);
  REQUIRE(m2[1] == m2r[1]);

  matrix m3(5);
  m3[0] = {1, 2, 0};
  m3[1] = {4, 0, 2};
  m3[2] = {7, 8, 9};
  m3[3] = {4, 1, 2};
  m3[4] = {8, 5, 3};
  zero_matrix(m3);
  matrix m3r(5);
  m3r[0] = {0, 0, 0};
  m3r[1] = {0, 0, 0};
  m3r[2] = {7, 0, 0};
  m3r[3] = {4, 0, 0};
  m3r[4] = {8, 0, 0};
  REQUIRE(m3[0] == m3r[0]);
  REQUIRE(m3[1] == m3r[1]);
  REQUIRE(m3[2] == m3r[2]);
  REQUIRE(m3[3] == m3r[3]);
  REQUIRE(m3[4] == m3r[4]);
}

TEST_CASE("is_rotation", "[arrays_and_strings]") {
  REQUIRE(is_rotation("abc", "bca") == true);
  REQUIRE(is_rotation("abc", "acb") == false);
  REQUIRE(is_rotation("abc", "abca") == false);
  REQUIRE(is_rotation("abcde", "cdeab") == true);
  REQUIRE(is_rotation("abcde", "eacbd") == false);
  REQUIRE(is_rotation("abc-d e", " eabc-d") == true);
}
