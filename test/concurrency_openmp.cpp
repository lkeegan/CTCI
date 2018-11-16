#include "concurrency_openmp.hpp"
#include "catch.hpp"

TEST_CASE("count_threads", "[concurrency_openmp]") {
  int n_threads = 6;
  std::vector<int> thread_counts = count_threads(n_threads);
  for (auto count : thread_counts) {
    REQUIRE(count == n_threads);
  }
}

TEST_CASE("compute_pi", "[concurrency_openmp]") {
  double pi_exact = 3.14159265359;
  for (int n_threads : {1, 2, 3, 4, 6}) {
    double pi_approx = compute_pi_reduction(10000000, n_threads);
    REQUIRE(pi_approx == Approx(pi_exact).margin(1e-8));
    pi_approx = compute_pi_critical(10000000, n_threads);
    REQUIRE(pi_approx == Approx(pi_exact).margin(1e-8));
    pi_approx = compute_pi_atomic(10000000, n_threads);
    REQUIRE(pi_approx == Approx(pi_exact).margin(1e-8));
  }
}

TEST_CASE("matrix operator*", "[concurrency_openmp]") {
  matrix<int> A(3, 0);
  matrix<int> B(3, 0);
  matrix<int> C = A * B;
  REQUIRE(C == A);
  REQUIRE(C == B);
}