#include "hard.hpp"
#include "catch.hpp"

TEST_CASE("add_without_plus", "[hard]") {
  REQUIRE(add_without_plus(0, 0) == 0);
  REQUIRE(add_without_plus(1, 0) == 1);
  REQUIRE(add_without_plus(0, 1) == 1);
  REQUIRE(add_without_plus(1, 1) == 2);
  REQUIRE(add_without_plus(123, 568561) == 123 + 568561);
  REQUIRE(add_without_plus(127647543, 2423) == 127647543 + 2423);
}

TEST_CASE("shuffle_cards", "[hard]") {
  constexpr int N_CARDS_IN_DECK = 52;
  int N_SAMPLES = 10000;

  // start with ordered deck
  std::array<int, N_CARDS_IN_DECK> deck;
  int index = 0;
  for (auto &d : deck) {
    d = index++;
  }
  // sum card_index at each location for 1000 shuffles
  std::array<int, N_CARDS_IN_DECK> count{};
  for (int i_samples = 0; i_samples < N_SAMPLES; ++i_samples) {
    shuffle_cards(deck, i_samples);
    for (std::size_t i = 0; i < deck.size(); ++i) {
      count[i] += deck[i];
    }
  }
  // count at each location should be (stochastically) equal to
  // average_index * N_SAMPLES
  double average_index = 0;
  for (int i = 0; i < N_CARDS_IN_DECK; ++i) {
    average_index += static_cast<double>(i);
  }
  average_index /= static_cast<double>(N_CARDS_IN_DECK);

  int sum = 0;
  for (auto c : count) {
    sum += c;
    double stoch_one = static_cast<double>(c) / (average_index * N_SAMPLES);
    CAPTURE(stoch_one);
    REQUIRE(stoch_one == Approx(1.0).margin(0.05));
  }
  REQUIRE(sum == N_SAMPLES * N_CARDS_IN_DECK * average_index);
}

TEST_CASE("sub_set", "[hard]") {
  std::vector<int> v1{1, -3, 9, 14, 833, 71, 732, 10};
  int set_size = 3;
  int N_SAMPLES = 10000 * v1.size();
  // count how many times each value occurs in each element of the subset
  std::vector<std::unordered_map<int, int>> counts(3);
  for (int i_samples = 0; i_samples < N_SAMPLES; ++i_samples) {
    auto v1_sub = sub_set(v1, set_size, i_samples);
    for (int i = 0; i < set_size; ++i) {
      ++counts[i][v1_sub[i]];
    }
  }
  // compare to expected equal frequency for all values in v1
  // for every element of the subset
  for (int i = 0; i < set_size; ++i) {
    for (auto v : v1) {
      REQUIRE(counts[i][v] == Approx(N_SAMPLES / v1.size()).margin(50));
    }
  }
}