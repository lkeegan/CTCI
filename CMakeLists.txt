cmake_minimum_required(VERSION 3.1)
project (CTCI)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fprofile-arcs -ftest-coverage -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -march=native")

# make Catch2 unit testing library
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE catch)

# set header files
include_directories(inc)

# set common source files
set (SRCS ${SRCS} src/arrays_and_strings.cpp src/linked_lists.cpp src/stacks_and_queues src/bit_manipulation.cpp src/c_and_cpp.cpp src/moderate.cpp)

# make unit test executable
set (TEST_SRCS ${SRCS} test/arrays_and_strings.cpp test/linked_lists.cpp test/stacks_and_queues.cpp test/bit_manipulation.cpp test/c_and_cpp.cpp test/moderate.cpp)
add_executable(tests test/main.cpp ${TEST_SRCS})
target_link_libraries(tests Catch)

# make running the test executable part of the build, so failed test = failed build
add_custom_command(TARGET tests POST_BUILD COMMAND tests -s -d yes)
