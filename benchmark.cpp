#include <benchmark/benchmark.h>
#include <concurrency_openmp.hpp>
#include <random>
#include <string>

template <typename T>
void setRandom(matrix<T>& mat, std::ranlux48& rng) {
  std::uniform_real_distribution<double> dist(-1, 1);
  for (std::size_t i = 0; i < mat.size(); ++i) {
    for (std::size_t j = 0; j < mat.size(); ++j) {
      mat[i][j] = dist(rng);
    }
  }
}

void BM_StringCopy(benchmark::State& state) {
  std::string x = "hello";
  for (auto _ : state) {
    std::string y;
    for (int i = 0; i < state.range(0); ++i) {
      y += x;
    }
  }
  state.SetComplexityN(state.range(0));
}

static void BM_MatrixMult(benchmark::State& state) {
  int matrix_size = state.range(0);
  std::ranlux48 rng(123);
  matrix<int> A(matrix_size, 0.0);
  setRandom(A, rng);
  matrix<int> B(matrix_size, 0.0);
  setRandom(B, rng);
  matrix<int> C(matrix_size, 0.0);
  for (auto _ : state) {
    C = A * B;
  }
  state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_StringCopy)->Range(1 << 8, 1 << 18)->Complexity()->UseRealTime();

BENCHMARK(BM_MatrixMult)
    ->Range(1 << 2, 1 << 10)
    ->UseRealTime()
    ->ThreadRange(1, 4);

BENCHMARK_MAIN();