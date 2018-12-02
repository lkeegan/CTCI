#ifndef LKEEGAN_CTCI_C_AND_CPP_H
#define LKEEGAN_CTCI_C_AND_CPP_H
#include <fstream>
#include <iostream>
#include <memory>
#include <queue>
#include <sstream>
#include <string>

namespace ctci {
namespace c_and_cpp {

// 12.1 print last k lines of filename
void last_k_lines(const std::string& filename, unsigned int k,
                  std::ostream& output);

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
inline void wait_until_ready() {
  volatile bool ready = false;
  // wait until ready is set to true
  while (!ready) {
    // without "volatile" the above condition may be "optimised"
    // by the compiler to always evaluate to true and we get stuck
    // in an infinite loop, even if ready is changed
    // to true at some point by some external process
  }
  // now ready to do something
}

// 12.8 copy a node structure where each node contains
// pointers to two other nodes

// simple node structure
template <class T>
struct node {
  // use unique_ptrs to child nodes:
  // no need for custom destructor, they
  // be automatically cleaned up when they
  // go out of scope
  std::unique_ptr<node> left;
  std::unique_ptr<node> right;
  T data;
};

template <class T>
std::unique_ptr<node<T>> copy_node(const std::unique_ptr<node<T>>& other_node) {
  std::unique_ptr<node<T>> new_node(new node<T>);
  new_node->data = other_node->data;
  if (other_node->left) {
    new_node->left = copy_node(other_node->left);
  }
  if (other_node->right) {
    new_node->right = copy_node(other_node->right);
  }
  return new_node;
}

// 12.9 implement a smart (shared) pointer
template <class T>
class SmartPointer {
 private:
  int* reference_count_ptr;
  T* data_ptr;
  friend void swap(SmartPointer& left, SmartPointer& right) {
    std::swap(left.reference_count_ptr, right.reference_count_ptr);
    std::swap(left.data_ptr, right.data_ptr);
  }

 public:
  // constructor from pointer to allocated data
  // NB takes ownership of data
  // user must not call delete on this pointer
  explicit SmartPointer(T* ptr = nullptr)
      : reference_count_ptr(ptr ? new int(1) : nullptr),
        data_ptr(ptr ? ptr : nullptr) {}
  // copy constructor: copy pointer to data & increment ref count
  SmartPointer(const SmartPointer& other)
      : reference_count_ptr(other.reference_count_ptr),
        data_ptr(other.data_ptr) {
    ++(*reference_count_ptr);
  }
  // move constructor (do not increment reference count)
  SmartPointer(SmartPointer&& other)
      : reference_count_ptr(other.reference_count_ptr),
        data_ptr(other.data_ptr) {
    // set pointers in other to null
    // so destructor doesn't change ref count
    other.reference_count_ptr = nullptr;
    other.data_ptr = nullptr;
  }
  // assignment constructor: copy&swap
  SmartPointer& operator=(const SmartPointer& other) {
    SmartPointer tmp(other);
    swap(*this, tmp);
    return *this;
  }
  // move assignment constructor (do not increment reference count)
  SmartPointer& operator=(SmartPointer&& other) {
    // 'steal' pointers from other
    reference_count_ptr = other.reference_count_ptr;
    data_ptr = other.data_ptr;
    // then set pointers in other to null
    // so destructor doesn't change ref count
    other.reference_count_ptr = nullptr;
    other.data_ptr = nullptr;
    return *this;
  }
  // de-reference data pointer
  T& operator*() const { return *data_ptr; }
  // get count of references to data
  int reference_count() const { return *reference_count_ptr; }
  // if our reference_count_prt is not a nullptr,
  // and it was 1, i.e. this was the last reference to the data
  // then delete both data and reference count in destructor
  ~SmartPointer() {
    if (reference_count_ptr) {
      --(*reference_count_ptr);
      if (*reference_count_ptr == 0) {
        delete data_ptr;
        delete reference_count_ptr;
      }
    }
  }
};

// 12.10
void* align_malloc(uintptr_t n_bytes, uintptr_t alignment_boundary);
void aligned_free(void* p);

// 12.11 2d vector in C
double** my_2d_alloc(int size_x, int size_y);

}  // namespace c_and_cpp
}  // namespace ctci
#endif  // LKEEGAN_CTCI_C_AND_CPP_H
