#ifndef LKEEGAN_CTCI_HARD_H
#define LKEEGAN_CTCI_HARD_H
#include <algorithm>
#include <array>
#include <cstddef>
#include <iostream>
#include <limits>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// 17.1
// add function without +
unsigned int add_without_plus(unsigned int a, unsigned int b);

// 17.2
// shuffle deck of cards: each of 52! permutations must be equally likely
// assuming order of cards stored in std::array<int, 52>,
// with exactly one of each number from 0 to 51
// identifying each card in the array
template <std::size_t CARDS_IN_DECK>
void shuffle_cards(std::array<int, CARDS_IN_DECK>& deck, int rng_seed = 123) {
  std::ranlux48 rng(rng_seed);
  for (std::size_t card_index = 0; card_index < deck.size() - 1; ++card_index) {
    // cards below card_index are already shuffled
    // we must choose from any of the remaining cards to put
    // at card_index, with equal probability for each
    std::uniform_int_distribution<int> dist(card_index, deck.size() - 1);
    // swap randomly chosen card with the one already at card_index
    // (note they could be the same card)
    std::swap(deck[card_index], deck[dist(rng)]);
    // now the card at card_index is also shuffled
  }
  // NB equivalent to just calling std::shuffle(deck.begin(), deck.end(), rng)
}

// 17.3
// return random sub-set of m elements from vector of elements
// with equal probability of choosing each element
template <typename T>
std::vector<T> sub_set(const std::vector<T>& arr, std::size_t m,
                       int rng_seed = 123) {
  // assuming rng is most expensive part of this routine
  // want to minimise number of rng calls required
  // can do this by first generating a set of indices for entire arr
  std::ranlux48 rng(rng_seed);
  std::vector<std::size_t> shuffled_indices(arr.size());
  std::size_t index = 0;
  for (auto& i : shuffled_indices) {
    i = index++;
  }
  // reserve memory for subset that we will return
  std::vector<T> subset;
  subset.reserve(m);
  // then only shuffle first m indices, and push_back each
  // corresponding element of arr to subset
  for (std::size_t i_m = 0; i_m < m; ++i_m) {
    std::uniform_int_distribution<int> dist(i_m, arr.size() - 1);
    std::swap(shuffled_indices[i_m], shuffled_indices[dist(rng)]);
    subset.push_back(arr[shuffled_indices[i_m]]);
  }
  return subset;
}

// 17.4
// array A contains integers 0 to n, except one
// can only access jth bit of A[i] which takes constant time
// find missing integer in O(n) time
inline bool get_bit(unsigned int j, unsigned int i,
                    const std::vector<unsigned int>& A) {
  return ((A[i] >> j) & 1) != 0;
}

unsigned int missing_number(const std::vector<unsigned int>& A);
#endif  // LKEEGAN_CTCI_HARD_H