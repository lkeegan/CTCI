# CTCI [![Build Status](https://travis-ci.org/lkeegan/CTCI.svg?branch=master)](https://travis-ci.org/lkeegan/CTCI) [![codecov](https://codecov.io/gh/lkeegan/CTCI/branch/master/graph/badge.svg)](https://codecov.io/gh/lkeegan/CTCI) [![Quality Gate](https://sonarcloud.io/api/project_badges/measure?project=lkeegan_CTCI&metric=alert_status)](https://sonarcloud.io/dashboard/index/lkeegan_CTCI)
(Partial) Set of C++11 solutions to questions from the book [Cracking the Code Interview](http://www.crackingthecodinginterview.com/).

The solutions to a given chapter X are declared in 'inc/X.hpp' and implemented in 'src/X.cpp'.

The corresponding unit tests (using the [Catch2](https://github.com/catchorg/Catch2) framework, included) are in 'test/X.cpp'.

Benchmarks (using the [Google Benchmark](https://github.com/google/benchmark) library, not included) are in 'benchmark/X.cpp'.

| Chapter | Solutions | Unit tests | Benchmarks |
| :-----: | :-------: | :--------: | :--------: |
| 1. Arrays and Strings | :heavy_check_mark: | :heavy_check_mark: |  |
| 2. Linked Lists | | | |

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
