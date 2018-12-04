#include <benchmark/benchmark.h>
#include <linked_lists.hpp>
#include <random>

using namespace ctci::linked_lists;

void BM_remove_dups(benchmark::State& state) {
  int n = state.range(0);
  bool USE_DATA_BUFFER = static_cast<bool>(state.range(1));
  std::ranlux48 rng(123);
  std::uniform_int_distribution<> dist(0, (n + 1) / 3);
  std::list<int> lst;
  for (int i = 0; i < n; ++i) {
    lst.push_front(dist(rng));
  }
  for (auto _ : state) {
    // make copy of list since remove_dups works in-place
    std::list<int> lst_copy(lst);
    remove_dups(lst_copy, USE_DATA_BUFFER);
  }
  state.SetComplexityN(n);
}

BENCHMARK(BM_remove_dups)->Ranges({{2, 1 << 9}, {0, 0}})->Complexity();
BENCHMARK(BM_remove_dups)->Ranges({{2, 1 << 9}, {1, 1}})->Complexity();