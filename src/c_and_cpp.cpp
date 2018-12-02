#include "c_and_cpp.hpp"

namespace ctci {
namespace c_and_cpp {

void last_k_lines(const std::string& filename, unsigned int k,
                  std::ostream& os) {
  std::ifstream myfile(filename);
  if (!myfile) {
    throw std::invalid_argument("ERROR: cannot read file");
  }
  std::vector<std::string> lines(k + 1);
  std::size_t i = 0;
  // read file line by line
  // put each line in vector of k+1 strings
  // (k+2)'th line wraps around to overwrite first element of vector
  // use k+1 since last getline call will overwrite (k+1)'th with empty string
  while (std::getline(myfile, lines[i])) {
    i = (i + 1) % (k + 1);
  }
  // print out last k lines
  for (std::size_t j = 1; j <= k; ++j) {
    os << lines[(i + j) % (k + 1)] << std::endl;
  }
}

void reverse_string(char* str) {
  // O(n)
  // find last character
  char* back = str;
  while (*back != '\0') {
    ++back;
  }
  // leave null terminator where it is
  --back;
  // then swap pairs of chars:
  // first & last, 2nd & 2nd-to-last, etc
  while (back > str) {
    // str <--> back using 3 XOR's
    *str ^= *back;
    *back ^= *str;
    *str ^= *back;
    ++str;
    --back;
  }
}

void* align_malloc(uintptr_t n_bytes, uintptr_t alignment_boundary) {
  // need to have n_bytes for data
  // + (alignment_boundary-1) extra bytes for alignment
  // + sizeof(uintptr_t) to store address of original malloc for later free
  uintptr_t bytes_needed = n_bytes + alignment_boundary - 1 + sizeof(uintptr_t);
  // allocate memory
  void* p;
  if ((p = (void*)malloc(bytes_needed)) == NULL) {
    return NULL;
  }
  uintptr_t malloc_address = (uintptr_t)(p);
  // calculate offset to align first byte to boundary
  uintptr_t remainder = malloc_address % alignment_boundary;
  uintptr_t offset = alignment_boundary - remainder;
  // set p to point to this first aligned byte
  p = (void*)((uintptr_t)(p) + offset);
  // set p[-1] to contain the malloc_address required to free
  ((uintptr_t*)p)[-1] = malloc_address;
  return p;
}

void aligned_free(void* p) {
  // cast pointer p to type uintptr
  // p[-1] is then the address to call free with
  free((void*)(((uintptr_t*)p)[-1]));
}

double** my_2d_alloc(int size_x, int size_y) {
  // for each x index we need space for
  // - a pointer to the start of the column: sizeof(T*)
  // - the column of data: size_y * sizeof(T)
  uintptr_t mem_data = static_cast<uintptr_t>(size_x) *
                       static_cast<uintptr_t>(size_y) * sizeof(double);
  uintptr_t mem_index = static_cast<uintptr_t>(size_x) * sizeof(double*);
  double** arr = (double**)malloc(mem_index + mem_data);
  if (arr == NULL) {
    return NULL;
  }
  // start data after index
  double* p = (double*)(arr + size_x);
  // set each arr[x] pointer to point to start of column x
  for (int ix = 0; ix < size_x; ++ix) {
    arr[ix] = p;
    p += size_y;
  }
  return arr;
}

}  // namespace c_and_cpp
}  // namespace ctci