#include "hard.hpp"
#include "catch.hpp"

// Unit tests
using namespace ctci::hard;

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
  for (auto& d : deck) {
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

TEST_CASE("missing_number", "[hard]") {
  std::vector<unsigned int> A{0, 1, 2, 4, 5, 6};
  REQUIRE(missing_number(A) == 3);
  std::vector<unsigned int> B{1, 2, 3, 4};
  REQUIRE(missing_number(B) == 0);
  std::vector<unsigned int> C{0, 1, 2, 3, 4};
  REQUIRE(missing_number(C) == 5);
  std::vector<unsigned int> D{0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
                              10, 11, 12, 14, 15, 16, 17, 18, 19, 20};
  REQUIRE(missing_number(D) == 13);
}

TEST_CASE("longest_even_substring", "[hard]") {
  REQUIRE(longest_even_substring("") == "");
  REQUIRE(longest_even_substring("a") == "");
  REQUIRE(longest_even_substring("9") == "");
  REQUIRE(longest_even_substring("a7") == "a7");
  REQUIRE(longest_even_substring("a7a") == "7a");
  REQUIRE(longest_even_substring("a77") == "a7");
  REQUIRE(longest_even_substring("99a7b") == "9a7b");
  REQUIRE(longest_even_substring("asdf345") == "sdf345");
  REQUIRE(longest_even_substring("aab") == "");
  REQUIRE(longest_even_substring("462") == "");
  REQUIRE(longest_even_substring("aadfsgsdg6fgjjg") == "6f");
  REQUIRE(longest_even_substring("60aaaaa66") == "60aa");
}

TEST_CASE("count_of_twos", "[hard]") {
  std::vector<int> n_vals{0,  1,  2,  4,  11,  12,   19,    20,      21,
                          22, 31, 32, 99, 341, 4631, 74437, 2345234, 12421312};
  for (auto n : n_vals) {
    CAPTURE(n);
    REQUIRE(count_of_twos(n) == count_of_twos_debug(n));
  }
}

TEST_CASE("merge_synonyms", "[hard]") {
  using string_pair = std::pair<std::string, std::string>;
  std::unordered_map<std::string, int> frequencies;
  frequencies["Jon"] = 42;
  frequencies["John"] = 142;
  frequencies["Sam"] = 3;
  frequencies["Samuel"] = 32;
  std::vector<string_pair> name_pairs;
  name_pairs.push_back({"Jon", "John"});
  name_pairs.push_back({"Sam", "Samuel"});
  merge_synonyms(frequencies, name_pairs);
  REQUIRE(frequencies["Jon"] == 184);
  REQUIRE(frequencies["Sam"] == 35);
  REQUIRE(frequencies["Samuel"] == false);
  REQUIRE(frequencies["John"] == false);
}

TEST_CASE("kth_multiple", "[hard]") {
  for (int k : {1, 2, 3, 4, 5, 6, 7, 8, 9, 12, 15, 20, 55}) {
    CAPTURE(k)
    REQUIRE(kth_multiple(k) == kth_multiple_debug(k));
  }
}

TEST_CASE("majority_element", "[hard]") {
  std::vector<int> v;
  v = {8};
  REQUIRE(majority_element(v) == 8);
  v = {8, 1};
  REQUIRE(majority_element(v) == -1);
  v = {5, 2, 5};
  REQUIRE(majority_element(v) == 5);
  v = {2, 5, 2, 4, 2, 3};
  REQUIRE(majority_element(v) == -1);
  v = {2, 5, 2, 4, 2, 3, 2};
  REQUIRE(majority_element(v) == 2);
  v = {1, 1, 5, 1, 9, 1, 4, 7, 7, 7, 1, 1, 1};
  REQUIRE(majority_element(v) == 1);
}