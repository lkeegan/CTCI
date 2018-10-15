#include "c_and_cpp.hpp"
#include "catch.hpp"

// Unit tests
TEST_CASE("last_k_lines", "[c_and_cpp]") {
  REQUIRE_NOTHROW(last_k_lines("tmp.txt", 10));
}

TEST_CASE("reverse_string", "[c_and_cpp]") {
  char str[5] = "Test";
  reverse_string(str);
  REQUIRE(str[0] == 't');
  REQUIRE(str[1] == 's');
  REQUIRE(str[2] == 'e');
  REQUIRE(str[3] == 'T');
  REQUIRE(str[4] == '\0');

  char str2[4] = "Odd";
  reverse_string(str2);
  REQUIRE(std::string(str2) == "ddO");

  std::string cpp_str1("Asdfghjkl");
  reverse_string(cpp_str1);
  REQUIRE(cpp_str1 == "lkjhgfdsA");
}

TEST_CASE("virtual_functions", "[c_and_cpp]") {
  using namespace virtual_functions;
  // issue that arises from inheritance
  // have class "dog" that inherits from "animal"
  // non-virtual:
  // compile-time binding of function food()
  dog *d = new dog();
  animal *a = new dog();
  REQUIRE(d->food() == "dog.food()");
  REQUIRE(a->food() == "animal.food()");  // NOT dog.food()
  delete d;
  // also of destructor which can leak memory
  // if any is allocated in dog() that needs to be cleaned up
  delete a;  // only calls ~animal(), NOT ~dog()

  // virtual:
  // run-time binding of function food()
  v_dog *v_d = new v_dog();
  v_animal *v_a = new v_dog();
  REQUIRE(v_d->food() == "v_dog.food()");
  REQUIRE(v_a->food() == "v_dog.food()");
  delete v_d;
  // and destructor
  delete v_a;  // calls ~v_dog(), then ~v_animal()
}

TEST_CASE("shallow_vs_deep_copy", "[c_and_cpp]") {
  // dblvec_* classes are a (bad) implementation of
  // a vector of doubles,
  // with shallow copy:
  dblvec_shallow s1({1.0, 2.0, 3.0});
  dblvec_shallow s2(s1);
  REQUIRE(s1[2] == 3.0);
  REQUIRE(s2[2] == 3.0);
  // modify s1
  s1[2] = 4.0;
  REQUIRE(s1[2] == 4.0);
  // s2 value is also changed,
  // as it contains a copy of the *pointer*
  // in s1, not a copy of the *data* in s1.
  REQUIRE(s2[2] == 4.0);

  // with deep copy:
  dblvec_deep d1({1.0, 2.0, 3.0});
  dblvec_deep d2(d1);
  REQUIRE(d1[2] == 3.0);
  REQUIRE(d2[2] == 3.0);
  // modify d1
  d1[2] = 4.0;
  REQUIRE(d1[2] == 4.0);
  // d2 unchanged
  REQUIRE(d2[2] == 3.0);
}

TEST_CASE("align_malloc", "[c_and_cpp]") {
  constexpr int ALIGNMENT_BOUNDARY = 512;
  double *data =
      (double *)align_malloc(100 * sizeof(double), ALIGNMENT_BOUNDARY);
  data[23] = 0.345;
  data[99] = 0.545;
  REQUIRE(data[23] == 0.345);
  REQUIRE(data[99] == 0.545);
  CAPTURE((uintptr_t)(data));
  CAPTURE((uintptr_t)(data) / ALIGNMENT_BOUNDARY);
  REQUIRE((uintptr_t)(data) % ALIGNMENT_BOUNDARY == 0);
  aligned_free(data);
}

TEST_CASE("my_2d_alloc", "[c_and_cpp]") {
  int X = 3;
  int Y = 5;
  double **arr = my_2d_alloc(X, Y);
  for (int x = 0; x < X; ++x) {
    for (int y = 0; y < Y; ++y) {
      arr[x][y] = y + x * Y;
    }
  }
  REQUIRE(arr[0][0] == 0.0);
  REQUIRE(arr[0][2] == 2.0);
  REQUIRE(arr[1][0] == Y);
  REQUIRE(arr[1][1] == Y + 1);
  REQUIRE(arr[X - 1][0] == (X - 1) * Y);
  REQUIRE(arr[X - 1][Y - 1] == X * Y - 1);
  my_2d_free(arr);
}