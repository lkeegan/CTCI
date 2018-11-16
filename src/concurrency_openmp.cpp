#include "concurrency_openmp.hpp"

std::vector<int> count_threads(int n_threads) {
  std::vector<int> counts;
  // set thread-count for parallel regions
  // NB typically would be done externally
  // e.g. by setting OMP_NUM_THREADS env var
  omp_set_num_threads(n_threads);
  int count = 0;
  // start parallel section ("fork")
#pragma omp parallel
  // everything in here executed by all threads
  {
#pragma omp master
    // this section only executed by master thread
    {
      counts.push_back(omp_get_num_threads());
      std::cout << "omp_get_thread_num() call from thread "
                << omp_get_thread_num() << std::endl;
    }
#pragma omp critical
    // mutex lock on this section
    // only one thread can do this at a time
    {
      ++count;
      std::cout << "+1 from thread " << omp_get_thread_num() << std::endl;
    }
  }  // end of parallel section ("join")
  counts.push_back(count);

  // alternative version using atomic
  count = 0;
#pragma omp parallel
  {
    // only valid for single line, simple operation on primitive data type
#pragma omp atomic
    ++count;
    std::cout << "+1 from thread " << omp_get_thread_num() << std::endl;
  }
  counts.push_back(count);

  // alternative version using reduction
  count = 0;
#pragma omp parallel reduction(+ : count)
  {
    ++count;
    std::cout << "+1 from thread " << omp_get_thread_num() << std::endl;
  }
  counts.push_back(count);
  return counts;
}

double compute_pi_reduction(int N, int n_threads) {
  omp_set_num_threads(n_threads);
  double f = 0;  // ~= pi / 4x
  double dx = 1.0 / static_cast<double>(N);
  int actual_n_threads;
  double wt = omp_get_wtime();
#pragma omp parallel reduction(+ : f)
  {
    // fork threads
    // do reduction on variable f using operator+
#pragma omp master
    {
      // only do this block on master thread
      actual_n_threads = omp_get_num_threads();
    }  // no implicit barrier here
#pragma omp for
    for (int i = 0; i < N; ++i) {
      // static scheduling (default): split for loop into
      // chunks, where default chunk size = N/n_threads
      // most efficient if each iteration takes same time to complete
      double x_i = static_cast<double>(i) * dx;
      // can write to f without worrying about race conditions
      // thanks to reduction(+:f) clause
      // equivalent (but probably slower than) storing sum
      // in temp var, then summing them in a critical section at end
      // or alternatively
      f += sqrt(1.0 - x_i * x_i);
    }  // implicit #pragma omp barrier at end of for
  }
  std::cout << "compute_pi_reduction: " << omp_get_wtime() - wt << " ("
            << actual_n_threads << "/" << omp_get_num_procs() << ")"
            << std::endl;
  return 4.0 * dx * f;
}

double compute_pi_critical(int N, int n_threads) {
  omp_set_num_threads(n_threads);
  int actual_n_threads;
  double dx = 1.0 / static_cast<double>(N);
  double pi_4dx = 0;  // ~= pi / (4 dx)
  double wt = omp_get_wtime();
#pragma omp parallel
  {
#pragma omp master
    {
      // only do this block on master thread
      actual_n_threads = omp_get_num_threads();
    }  // no implicit barrier here
    // private variable for each thread
    double sum = 0;
    // store partial sum from each thread in sum
    // nowait: when a thread is done it can continue to
    // next section without waiting for others to finish
    // i.e. remove implicit barrier at end of for loop
#pragma omp for nowait
    for (int i = 0; i < N; ++i) {
      double x_i = static_cast<double>(i) * dx;
      sum += sqrt(1.0 - x_i * x_i);
    }
#pragma omp critical
    {
      // add each sum to pi:
      // use critical to do this separately for each thread
      // to avoid race conditions
      pi_4dx += sum;
    }  // implicit barrier here
  }
  std::cout << "compute_pi_critical: " << omp_get_wtime() - wt << " ("
            << actual_n_threads << "/" << omp_get_num_procs() << ")"
            << std::endl;
  return 4.0 * dx * pi_4dx;
}

double compute_pi_atomic(int N, int n_threads) {
  omp_set_num_threads(n_threads);
  int actual_n_threads;
  double dx = 1.0 / static_cast<double>(N);
  double pi_4dx = 0;  // ~= pi / (4 dx)
  double wt = omp_get_wtime();
#pragma omp parallel
  {
#pragma omp master
    {
      // only do this block on master thread
      actual_n_threads = omp_get_num_threads();
    }  // no implicit barrier here
#pragma omp for
    for (int i = 0; i < N; ++i) {
      double x_i = static_cast<double>(i) * dx;
      // use atomic pragma to avoid race condition
      // when adding to pi_4dx
#pragma omp atomic
      pi_4dx += sqrt(1.0 - x_i * x_i);
    }
  }
  std::cout << "compute_pi_atomic: " << omp_get_wtime() - wt << " ("
            << actual_n_threads << "/" << omp_get_num_procs() << ")"
            << std::endl;
  return 4.0 * dx * pi_4dx;
}