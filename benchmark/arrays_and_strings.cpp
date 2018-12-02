#include <benchmark/benchmark.h>
#include <arrays_and_strings.hpp>
#include <random>

using namespace ctci::arrays_and_strings;

void BM_is_unique_a(benchmark::State& state) {
  std::string unique_string;
  for (int ci = 0; ci < 128; ++ci) {
    unique_string.push_back(static_cast<char>(ci));
  }
  int n = state.range(0);
  std::string s = unique_string.substr(0, n);
  for (auto _ : state) {
    is_unique_a(s);
  }
  state.SetComplexityN(n);
}

void BM_is_unique_b(benchmark::State& state) {
  std::string unique_string;
  for (int ci = 0; ci < 128; ++ci) {
    unique_string.push_back(static_cast<char>(ci));
  }
  int n = state.range(0);
  std::string s = unique_string.substr(0, n);
  for (auto _ : state) {
    is_unique_b(s);
  }
  state.SetComplexityN(n);
}

void BM_check_permutation(benchmark::State& state) {
  int n = state.range(0);
  std::string s1;
  for (int ci = 0; ci < n; ++ci) {
    s1.push_back(static_cast<char>(ci % 128));
  }
  std::string s2(s1);
  for (auto _ : state) {
    check_permutation(s1, s2);
  }
  state.SetComplexityN(n);
}

void BM_URLify(benchmark::State& state) {
  int n = state.range(0);
  std::string s16("asd dg ww! 1s f.");
  std::string s{};
  for (int i = 0; i < n; ++i) {
    s += s16;
  }
  s += std::string(15 * n, ' ');
  for (auto _ : state) {
    URLify(s, n * s16.size());
  }
  state.SetComplexityN(n);
}

void BM_is_permutation_of_palindrome(benchmark::State& state) {
  int n = state.range(0);
  std::string s16("asd dg ww! 1s f.");
  std::string s{};
  for (int i = 0; i < n; ++i) {
    s += s16;
  }
  for (auto _ : state) {
    is_permutation_of_palindrome(s);
  }
  state.SetComplexityN(n);
}

void BM_one_away(benchmark::State& state) {
  int n = state.range(0);
  std::string s16("asd dg ww! 1s f.");
  std::string s1{};
  for (int i = 0; i < n; ++i) {
    s1 += s16;
  }
  s16 = s1;
  s16[16 * n / 2] = 'X';
  for (auto _ : state) {
    one_away(s1, s16);
  }
  state.SetComplexityN(n);
}

void BM_string_compression(benchmark::State& state) {
  int n = state.range(0);
  std::string s16("qqqqccc sppppooo");
  std::string s1{};
  for (int i = 0; i < n; ++i) {
    s1 += s16;
  }
  for (auto _ : state) {
    std::string s2 = string_compression(s1);
  }
  state.SetComplexityN(n);
}

void BM_rotate_matrix(benchmark::State& state) {
  int n = state.range(0);
  std::vector<int> vec;
  vec.reserve(n);
  for (int i = 0; i < n; ++i) {
    vec.push_back(i);
  }
  matrix mat(n);
  for (auto& v : mat) {
    v = vec;
  }
  for (auto _ : state) {
    rotate_matrix(mat);
  }
  state.SetComplexityN(n);
}

void BM_zero_matrix(benchmark::State& state) {
  int n = state.range(0);
  std::vector<int> vec;
  vec.reserve(n);
  matrix mat(n);
  int j = 0;
  for (auto& v : mat) {
    for (int i = 0; i < n; ++i) {
      vec.push_back(i - j);
    }
    v = vec;
    ++j;
  }
  for (auto _ : state) {
    zero_matrix(mat);
  }
  state.SetComplexityN(n);
}

void BM_is_rotation(benchmark::State& state) {
  int n = state.range(0);
  std::string s16("qqqqccc sppppooo");
  std::string s1{};
  for (int i = 0; i < n; ++i) {
    s1 += s16;
  }
  for (auto _ : state) {
    is_rotation(s1, s1);
  }
  state.SetComplexityN(n);
}

BENCHMARK(BM_is_unique_a)->Range(2, 1 << 7)->Complexity();
BENCHMARK(BM_is_unique_b)->Range(2, 1 << 7)->Complexity();
BENCHMARK(BM_check_permutation)->Range(2, 1 << 14)->Complexity();
BENCHMARK(BM_URLify)->Range(1, 1 << 14)->Complexity();
BENCHMARK(BM_is_permutation_of_palindrome)->Range(1, 1 << 14)->Complexity();
BENCHMARK(BM_one_away)->Range(1, 1 << 14)->Complexity();
BENCHMARK(BM_string_compression)->Range(1, 1 << 14)->Complexity();
BENCHMARK(BM_rotate_matrix)->Range(1, 1 << 8)->Complexity();
BENCHMARK(BM_zero_matrix)->Range(1, 1 << 8)->Complexity();
BENCHMARK(BM_is_rotation)->Range(1, 1 << 14)->Complexity();
