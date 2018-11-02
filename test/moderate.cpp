#include "moderate.hpp"
#include "catch.hpp"

// Unit tests
TEST_CASE("number_swapper", "[moderate]") {
  int ia = 4;
  int ib = -85;
  number_swapper(ia, ib);
  REQUIRE(ia == -85);
  REQUIRE(ib == 4);

  unsigned int da = 12;
  unsigned int db = 66;
  number_swapper(da, db);
  REQUIRE(da == 66);
  REQUIRE(db == 12);
}

TEST_CASE("word_frequency", "[moderate]") {
  std::string book =
      "Call me Ishmael. Some years ago- never mind how long precisely- "
      "having little or no money in my purse, and nothing particular to "
      "interest me on shore, I thought I would sail about a little and see "
      "the watery part of the world. It is a way I have of driving off the "
      "spleen and regulating the circulation. Whenever I find myself growing "
      "grim about the mouth; whenever it is a damp, drizzly November in my "
      "soul; whenever I find myself involuntarily pausing before coffin "
      "warehouses, and bringing up the rear of every funeral I meet; and "
      "especially whenever my hypos get such an upper hand of me, that it "
      "requires a strong moral principle to prevent me from deliberately "
      "stepping into the street, and methodically knocking people's hats "
      "off- then, I account it high time to get to sea as soon as I can. "
      "This is my substitute for pistol and ball. With a philosophical "
      "flourish Cato throws himself upon his sword; I quietly take to the "
      "ship. There is nothing surprising in this. If they but knew it, "
      "almost all men in their degree, some time or other, cherish very "
      "nearly the same feelings towards the ocean with me.";
  REQUIRE(word_frequency("IsIhImael", book) == 0);
  REQUIRE(word_frequency("Ishmael", book) == 1);
  REQUIRE(word_frequency("I", book) == 9);
  REQUIRE(word_frequency("the", book) == 10);
  auto counts = word_frequency_map(book);
  REQUIRE(counts["IsIhImael"] == 0);
  REQUIRE(counts["Ishmael"] == 1);
  REQUIRE(counts["I"] == 9);
  REQUIRE(counts["the"] == 10);
}

TEST_CASE("Intersection", "[moderate]") {
  using namespace MyIntersection;
  point intersect_point;
  line l1({0.0, 0.0}, {5.0, 5.0});
  line l2({0.0, 5.0}, {5.0, 0.0});
  REQUIRE(intersect(l1, l2) == true);
  REQUIRE(intersect(l1, l2, &intersect_point) == true);
  REQUIRE(intersect_point.x == 2.5);
  REQUIRE(intersect_point.y == 2.5);

  l2 = line({0.0, 5.0}, {1.0, 4.0});
  REQUIRE(intersect(l1, l2) == false);

  l2 = line({0.0, 5.0}, {2.5, 2.5});
  REQUIRE(intersect(l1, l2, &intersect_point) == true);
}

TEST_CASE("tic_tac_win", "[moderate]") {
  tic_tac_toe<3> T;
  REQUIRE(T.cross_wins() == false);
  REQUIRE(T.circle_wins() == false);
  T.cross(0, 0);
  REQUIRE(T.cross_wins() == false);
  REQUIRE(T.circle_wins() == false);
  T.circle(0, 1);
  REQUIRE(T.cross_wins() == false);
  REQUIRE(T.circle_wins() == false);
  T.cross(1, 1);
  REQUIRE(T.cross_wins() == false);
  REQUIRE(T.circle_wins() == false);
  T.circle(0, 2);
  REQUIRE(T.cross_wins() == false);
  REQUIRE(T.circle_wins() == false);
  T.cross(2, 2);
  REQUIRE(T.cross_wins() == true);
  REQUIRE(T.circle_wins() == false);
  std::cout << T << std::endl;

  T = tic_tac_toe<3>("xxoooxxxo");
  std::cout << T << std::endl;
  REQUIRE(T.cross_wins() == false);
  REQUIRE(T.circle_wins() == false);

  T = tic_tac_toe<3>("xxoooxoxo");
  std::cout << T << std::endl;
  REQUIRE(T.cross_wins() == false);
  REQUIRE(T.circle_wins() == true);
}

TEST_CASE("factorial_trailing_zeros", "[moderate]") {
  REQUIRE(factorial_trailing_zeros(0) == 0);
  REQUIRE(factorial_trailing_zeros(1) == 0);
  REQUIRE(factorial_trailing_zeros(2) == 0);
  REQUIRE(factorial_trailing_zeros(3) == 0);
  REQUIRE(factorial_trailing_zeros(4) == 0);
  REQUIRE(factorial_trailing_zeros(5) == 1);
  REQUIRE(factorial_trailing_zeros(6) == 1);
  REQUIRE(factorial_trailing_zeros(7) == 1);
  REQUIRE(factorial_trailing_zeros(8) == 1);
  REQUIRE(factorial_trailing_zeros(9) == 1);
  REQUIRE(factorial_trailing_zeros(10) == 2);
  REQUIRE(factorial_trailing_zeros(12) == 2);
  REQUIRE(factorial_trailing_zeros(15) == 3);
  REQUIRE(factorial_trailing_zeros(20) == 4);
  REQUIRE(factorial_trailing_zeros(24) == 4);
  REQUIRE_THROWS(factorial_trailing_zeros(99));
}

TEST_CASE("smallest_difference", "[moderate]") {
  std::vector<int> A{1, 4, 16, 5};
  std::vector<int> B{7, 3, 9, 11};
  std::vector<int> C{66, 51, 22, 11};
  REQUIRE(smallest_difference(A, B) == 1);
  REQUIRE(smallest_difference(B, A) == 2);
  REQUIRE(smallest_difference(C, A) == 6);
  REQUIRE(smallest_difference(C, B) == 0);
  REQUIRE(smallest_difference(B, C) == 0);
}

TEST_CASE("number_max", "[moderate]") {
  REQUIRE(number_max(4, 7) == 7);
  REQUIRE(number_max(11, 1) == 11);
  REQUIRE(number_max(88, 88) == 88);
  REQUIRE(number_max(11.234, 1.123) == 11.234);
  REQUIRE(number_max<double>(11.234, 5) == 11.234);
  REQUIRE(number_max(-11.234, static_cast<double>(5)) == -11.234);
  REQUIRE(number_max(4.3f, 4.299f) == 4.3f);
  REQUIRE(number_max(4.3f, 4.3f) == 4.3f);
}

TEST_CASE("english_int", "[moderate]") {
  REQUIRE(english_int(1) == "One");
  REQUIRE(english_int(6) == "Six");
  REQUIRE(english_int(12) == "Twelve");
  REQUIRE(english_int(18) == "Eighteen");
  REQUIRE(english_int(20) == "Twenty");
  REQUIRE(english_int(21) == "Twenty One");
  REQUIRE(english_int(48) == "Forty Eight");
  REQUIRE(english_int(82) == "Eighty Two");
  REQUIRE(english_int(99) == "Ninety Nine");
  REQUIRE(english_int(100) == "One Hundred");
  REQUIRE(english_int(101) == "One Hundred One");
  REQUIRE(english_int(107) == "One Hundred Seven");
  REQUIRE(english_int(113) == "One Hundred Thirteen");
  REQUIRE(english_int(127) == "One Hundred Twenty Seven");
  REQUIRE(english_int(735) == "Seven Hundred Thirty Five");
  REQUIRE(english_int(1000) == "One Thousand");
  REQUIRE(english_int(1001) == "One Thousand One");
  REQUIRE(english_int(1011) == "One Thousand Eleven");
  REQUIRE(english_int(1028) == "One Thousand Twenty Eight");
  REQUIRE(english_int(1828) == "One Thousand Eight Hundred Twenty Eight");
  REQUIRE(english_int(74828) ==
          "Seventy Four Thousand Eight Hundred Twenty Eight");
  REQUIRE(english_int(374828) ==
          "Three Hundred Seventy Four Thousand Eight Hundred Twenty Eight");
  REQUIRE(english_int(19000000) == "Nineteen Million");
  REQUIRE(english_int(99000000000) == "Ninety Nine Billion");
  REQUIRE(english_int(421000000000000) == "Four Hundred Twenty One Trillion");
  REQUIRE(english_int(5000000000000000) == "Five Quadrillion");
  REQUIRE(english_int(2000000000000000000) == "Two Quintillion");
  REQUIRE(english_int(0xffffffffffffffff) ==
          "Eighteen Quintillion Four Hundred Forty Six Quadrillion Seven "
          "Hundred Forty Four Trillion Seventy Three Billion Seven Hundred "
          "Nine Million Five Hundred Fifty One Thousand Six Hundred Fifteen");
}