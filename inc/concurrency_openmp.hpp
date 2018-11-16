#ifndef LKEEGAN_CTCI_CONCURRENCY_OPENMP_H
#define LKEEGAN_CTCI_CONCURRENCY_OPENMP_H
#include <omp.h>
#include <cmath>
#include <iostream>
#include <vector>

// hello world: create n_threads
// count them in a variety of ways
// return vector of these counts
std::vector<int> count_threads(int n_threads);

// compute pi as area of circle
// pi/4 = \int_0^1 sqrt(1-x^2)dx
// ~= \sum_i=0^{N-1} sqrt(1+(i/N)^2) / N
double compute_pi_reduction(int N, int n_threads);
double compute_pi_critical(int N, int n_threads);
double compute_pi_atomic(int N, int n_threads);

template <typename T>
class matrix {
 private:
  std::vector<std::vector<T>> M;

 public:
  matrix(std::size_t N, const T& init_val = T()) {
    M.resize(N, std::vector<T>(N, init_val));
  }
  explicit matrix(const std::vector<std::vector<T>>& vec_of_vecs)
      : M(vec_of_vecs){};
  std::size_t size() const { return M.size(); }
  std::vector<T>& operator[](std::size_t i) { return M[i]; }
  const std::vector<T>& operator[](std::size_t i) const { return M[i]; }
  matrix operator*(const matrix& rhs) const {
    int N = static_cast<int>(M.size());
    matrix<T> R(rhs);
#pragma omp parallel for collapse(3)
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        for (int k = 0; k < N; ++k) {
          R[i][k] = M[i][j] * rhs[j][k];
        }
      }
    }
    return R;
  }
  bool operator==(const matrix& rhs) const { return M == rhs.M; }
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const matrix<T>& mat) {
  for (std::size_t i = 0; i < mat.size(); ++i) {
    os << "{ ";
    for (auto v : mat[i]) {
      os << v << " ";
    }
    os << "} ";
  }
  return os;
}

#endif  // LKEEGAN_CTCI_CONCURRENCY_OPENMP_H
