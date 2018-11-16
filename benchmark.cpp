#include <iostream>
#include <map>
#include <random>
#include "concurrency_openmp.hpp"

template <typename T>
void setRandom(matrix<T>& mat, std::ranlux48& rng) {
  std::uniform_real_distribution<double> dist(-1, 1);
  for (std::size_t i = 0; i < mat.size(); ++i) {
    for (std::size_t j = 0; j < mat.size(); ++j) {
      mat[i][j] = dist(rng);
    }
  }
}

int main() {
  int n_runs = 4;
  std::vector<int> n_threads_list = {1, 2, 3, 4, 6};
  int matrix_size = 2000;
  std::ranlux48 rng(123);
  std::map<int, double> timings;
  matrix<int> A(matrix_size, 0.0);
  setRandom(A, rng);
  matrix<int> B(matrix_size, 0.0);
  setRandom(B, rng);
  matrix<int> C(matrix_size, 0.0);
  for (int i = 0; i < n_runs; ++i) {
    for (int n_threads : n_threads_list) {
      omp_set_num_threads(n_threads);
      double wtime = omp_get_wtime();
      C = A * B;
      double time = omp_get_wtime() - wtime;
      timings[n_threads] += time;
    }
  }
  for (int n_threads : n_threads_list) {
    std::cout << n_threads << "/" << omp_get_num_procs() << ": "
              << timings[n_threads] / static_cast<double>(n_runs) << std::endl;
  }
}