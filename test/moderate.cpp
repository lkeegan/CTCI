#include "moderate.hpp"
#include "catch.hpp"

// Unit tests
using namespace ctci::moderate;

TEST_CASE("16.1 number_swapper", "[moderate]") {
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

TEST_CASE("16.2 word_frequency", "[moderate]") {
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

TEST_CASE("16.3 Intersection", "[moderate]") {
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

TEST_CASE("16.4 tic_tac_win", "[moderate]") {
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
  CAPTURE(T);
  REQUIRE(T.cross_wins() == true);
  REQUIRE(T.circle_wins() == false);

  auto T2 = tic_tac_toe<3>("xxoooxxxo");
  CAPTURE(T2);
  REQUIRE(T2.cross_wins() == false);
  REQUIRE(T2.circle_wins() == false);

  auto T3 = tic_tac_toe<3>("xxoooxoxo");
  CAPTURE(T3);
  REQUIRE(T3.cross_wins() == false);
  REQUIRE(T3.circle_wins() == true);
}

TEST_CASE("16.5 factorial_trailing_zeros", "[moderate]") {
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

TEST_CASE("16.6 smallest_difference", "[moderate]") {
  std::vector<int> A{1, 4, 16, 5};
  std::vector<int> B{7, 3, 9, 11};
  std::vector<int> C{66, 51, 22, 11};
  REQUIRE(smallest_difference(A, B) == 1);
  REQUIRE(smallest_difference(B, A) == 2);
  REQUIRE(smallest_difference(C, A) == 6);
  REQUIRE(smallest_difference(C, B) == 0);
  REQUIRE(smallest_difference(B, C) == 0);
}

TEST_CASE("16.7 number_max", "[moderate]") {
  REQUIRE(number_max(4, 7) == 7);
  REQUIRE(number_max(11, 1) == 11);
  REQUIRE(number_max(88, 88) == 88);
  REQUIRE(number_max(11.234, 1.123) == 11.234);
  REQUIRE(number_max<double>(11.234, 5) == 11.234);
  REQUIRE(number_max(-11.234, static_cast<double>(5)) == -11.234);
  REQUIRE(number_max(4.3f, 4.299f) == 4.3f);
  REQUIRE(number_max(4.3f, 4.3f) == 4.3f);
}

TEST_CASE("16.8 english_int", "[moderate]") {
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

TEST_CASE("16.9 operations_minus", "[moderate]") {
  REQUIRE(operations_minus(7, 2) == 7 - 2);
  REQUIRE(operations_minus(17547, 2312) == 17547 - 2312);
  REQUIRE(operations_minus(7, -2) == 9);
  REQUIRE(operations_minus(-7, 2) == -9);
  REQUIRE(operations_minus(2, 7) == 2 - 7);
  REQUIRE(operations_minus(-7, -2) == -5);
  REQUIRE(operations_minus(-2, -7) == 5);
  REQUIRE(operations_minus(-4, -4) == 0);
}

TEST_CASE("16.9 operations_multiply", "[moderate]") {
  REQUIRE(operations_multiply(3, 5) == 3 * 5);
  REQUIRE(operations_multiply(5, 3) == 3 * 5);
  REQUIRE(operations_multiply(3, -5) == -3 * 5);
  REQUIRE(operations_multiply(-5, 3) == -3 * 5);
  REQUIRE(operations_multiply(-5, -3) == 3 * 5);
}

TEST_CASE("16.9 operations_divide", "[moderate]") {
  REQUIRE(operations_divide(10, 3) == 3);
  REQUIRE(operations_divide(9, 3) == 3);
  REQUIRE(operations_divide(8, 3) == 2);
  REQUIRE(operations_divide(3, 8) == 0);
  REQUIRE(operations_divide(8, 8) == 1);
  REQUIRE(operations_divide(-8, 8) == -1);
  REQUIRE(operations_divide(-8, 2) == -4);
  REQUIRE(operations_divide(8, -2) == -4);
  REQUIRE(operations_divide(-8, -2) == 4);
  REQUIRE(operations_divide(-3, 4) == 0);
}

TEST_CASE("16.10 year_with_most_people", "[moderate]") {
  std::vector<std::pair<int, int>> years;
  years.push_back({1900, 2000});
  REQUIRE(year_with_most_people(years) == 1900);
  years.push_back({1940, 1960});
  REQUIRE(year_with_most_people(years) == 1940);
  years.push_back({1910, 1950});
  years.push_back({1950, 1980});
  REQUIRE(year_with_most_people(years) == 1950);
  years.push_back({1944, 1944});
  years.push_back({1944, 1944});
  years.push_back({1944, 1944});
  REQUIRE(year_with_most_people(years) == 1944);
}

TEST_CASE("16.11 enumerate_lengths", "[moderate]") {
  using set = std::unordered_set<int>;
  REQUIRE(enumerate_lengths(1, 1, 1) == set{1});
  REQUIRE(enumerate_lengths(1, 3, 5) == set{3, 5});
  REQUIRE(enumerate_lengths(2, 3, 5) == set{6, 8, 10});
  REQUIRE(enumerate_lengths(2, 5, 5) == set{10});
  REQUIRE(enumerate_lengths(4, 2, 3) == set{8, 9, 10, 11, 12});
  REQUIRE(enumerate_lengths(5, 12, 6) == set{30, 36, 42, 48, 54, 60});
}

TEST_CASE("16.23 rand7", "[moderate]") {
  rand_n rand5(5, 12345);
  std::array<int, 7> count{};
  constexpr int N_RAND = 100000;
  for (int i = 0; i < N_RAND; ++i) {
    ++count[rand7(rand5)];
  }
  for (auto c : count) {
    double stoch_one =
        7.0 * static_cast<double>(c) / static_cast<double>(N_RAND);
    CAPTURE(stoch_one);
    REQUIRE(stoch_one == Approx(1.0).margin(0.1));
  }
}