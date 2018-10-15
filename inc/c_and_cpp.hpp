#ifndef LKEEGAN_CTCI_C_AND_CPP_H
#define LKEEGAN_CTCI_C_AND_CPP_H
#include <fstream>
#include <iostream>
#include <memory>
#include <queue>
#include <string>

// 12.1 print last k lines of filename
void last_k_lines(const std::string& filename, unsigned int k = 1);

// 12.2 reverse a null-terminated ('\0') string
void reverse_string(char* str);
// 12.2 C++ version (aka std::reverse(str.begin(), str.end());)
template <class T>
void reverse_string(T& str) {
  typename T::iterator front = str.begin();
  typename T::iterator back = str.end();
  while ((front != back) && (front != --back)) {
    std::swap(*front++, *back);
  }
}

// 12.3 Hash table vs STL map

// std::unordered_map implements a hash table
// hash function on input gives which "bucket" would/does contain item
// then check if item is one of these O(1) items already in bucket
// so we need "==" operator and hash function
// O(1) amortised insertion/look-up [but O(n) worst case]
// O(n) space

// for relatively small (i.e. log(n) not vastly larger than 1)
// number of inputs, can use a search tree instead, e.g.
// std::map is order preserving version (using red/black tree)
// no hash function, just compares keys in search tree
// so need a "<" function for keys
// O(log(n)) insertion/look-up
// O(n) space

// And for a small number of *known* possible inputs,
// we can construct a perfect hash function such that no collisions possible,
// i.e. each key hashes to a unique integer in some range
// then just use an array of e.g. bools with hash of key as array index

// 12.4, 12.7: Virtual functions
namespace virtual_functions {
class animal {
 public:
  std::string food() { return "animal.food()"; }
  ~animal() { std::cout << "~animal()" << std::endl; }
};

class dog : public animal {
 public:
  std::string food() { return "dog.food()"; }
  ~dog() { std::cout << "~dog()" << std::endl; }
};

class v_animal {
 public:
  virtual std::string food() { return "v_animal.food()"; }
  virtual ~v_animal() { std::cout << "~v_animal()" << std::endl; }
};

class v_dog : public v_animal {
 public:
  std::string food() { return "v_dog.food()"; }
  ~v_dog() { std::cout << "~v_dog()" << std::endl; }
};
}  // namespace virtual_functions

// 12.5 shallow vs deep copy
class dblvec_shallow {
  // use default copy constructor: shallow copy, i.e.
  // just copies the pointer d, NOT the data it points to
 private:
  std::shared_ptr<std::vector<double>> d;

 public:
  explicit dblvec_shallow(
      const std::vector<double>& vec = std::vector<double>())
      : d(std::make_shared<std::vector<double>>(vec)){};
  double& operator[](int i) { return (*d)[i]; }
};

class dblvec_deep {
 private:
  std::unique_ptr<std::vector<double>> d;

 public:
  explicit dblvec_deep(const std::vector<double>& vec = std::vector<double>())
      : d(new std::vector<double>(vec)){};
  // copy constructor: deep copy
  // delete old vector, copy contents of other vector to new vector
  dblvec_deep(const dblvec_deep& other)
      : d(new std::vector<double>(*other.d)){};
  // similary for assignment operator (using copy&swap):
  dblvec_deep& operator=(dblvec_deep other) {
    std::swap(d, other.d);
    return *this;
  }
  double& operator[](int i) { return (*d)[i]; }
};

// 12.6
// in C, volatile tells the compiler not to optimise
// away / cache any reads of this variable, but
// instead to read it from main memory each time

// useful when variable may be changed outside
// of the code, e.g. waiting for some hardware to be ready:
// volatile bool not_ready = true;
// while(not_ready) {};

// without volatile the above may be "optimised"
// by the compiler to while(true){} and we are stuck
// in an infinite loop, even if not_ready is changed
// to false at some point by some external process

// 12.10
void* align_malloc(uintptr_t n_bytes, uintptr_t alignment_boundary);
void aligned_free(void* p);

// 12.11 2d vector in C
double** my_2d_alloc(int size_x, int size_y);
void my_2d_free(double** arr);
#endif  // LKEEGAN_CTCI_C_AND_CPP_H
