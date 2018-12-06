# CTCI [![Build Status](https://travis-ci.org/lkeegan/CTCI.svg?branch=master)](https://travis-ci.org/lkeegan/CTCI) [![codecov](https://codecov.io/gh/lkeegan/CTCI/branch/master/graph/badge.svg)](https://codecov.io/gh/lkeegan/CTCI) [![Quality Gate](https://sonarcloud.io/api/project_badges/measure?project=lkeegan_CTCI&metric=alert_status)](https://sonarcloud.io/dashboard/index/lkeegan_CTCI)
(Partial) set of C++11 solutions to questions from the book [Cracking the Code Interview](http://www.crackingthecodinginterview.com/).

- solutions to a given chapter X are in 'inc/X.hpp' and 'src/X.cpp'.
- unit tests (using the [Catch2](https://github.com/catchorg/Catch2) framework, included) are in 'test/X.cpp'
- benchmarks (using the [Google Benchmark](https://github.com/google/benchmark) library, not included) are in 'benchmark/X.cpp'.

## Status
| Chapter                   | Solutions          | Unit tests         | Benchmarks         |
| :------------------------ | :----------------: | :----------------: | :----------------: |
| 1. Arrays and Strings     | :heavy_check_mark: | :heavy_check_mark: | :heavy_check_mark: |
| 2. Linked Lists           | :heavy_check_mark: | :heavy_check_mark: | |
| 3. Stacks and Queues      | :heavy_check_mark: | :heavy_check_mark: | |
| 4. Trees and Graphs       | | | |
| 5. Bit manipulation       | | | |
| 6. Math & Logic Puzzles   | | | |
| 7. Object-Oriented Design | | | |
| 8. Recursion & Dynamic Programming | | | |
| 9. System Design and Scalability | | | |
| 10. Sorting and Searching | | | |
| 11. Testing               | | | |
| 12. C and C++             | | | |
| 13. Java                  | | | |
| 14. Databases             | | | |
| 15. Threads and Locks     | | | |
| 16. Moderate              | | | |
| 17. Hard                  | | | |


## Use
To compile and run the tests in debug mode to check everything is working:
```
mkdir Debug
cd Debug
cmake .. -DCMAKE_BUILD_TYPE=Debug
make tests
```
To compile and run the benchmarks (assuming you have already installed the Google Benchmark library)
```
mkdir Release
cd Release
cmake .. -DCMAKE_BUILD_TYPE=Release
make benchmark
