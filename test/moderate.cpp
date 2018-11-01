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