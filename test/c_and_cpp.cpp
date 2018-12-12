#include "c_and_cpp.hpp"
#include "catch.hpp"

// Unit tests
using namespace ctci::c_and_cpp;

TEST_CASE("12.1 last_k_lines", "[c_and_cpp]") {
  REQUIRE_THROWS(last_k_lines("non-existing-filename.txt", 1, std::cout));

  // make text file
  int n_lines = 3;
  std::string filename("tmp.txt");
  std::vector<std::string> lines{"123",      "34g5",   "ervgy3y4v wcvt 3qv",
                                 "(32q4-",   "dfas",   "002148",
                                 "efvoifh,", "ew8032", "6g r6egnewcv..."};
  std::ofstream myfile(filename);
  for (const auto &l : lines) {
    myfile << l << std::endl;
  }
  std::stringstream ss;
  std::string line;
  // read last k lines to ss
  last_k_lines(filename, n_lines, ss);
  // compare to last k lines in vector
  auto rev_iter = lines.crbegin();
  rev_iter += n_lines - 1;
  while (std::getline(ss, line)) {
    CAPTURE(line);
    CAPTURE(*rev_iter);
    REQUIRE(line == *rev_iter--);
  }
}

TEST_CASE("12.2 reverse_string", "[c_and_cpp]") {
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

TEST_CASE("12.4 virtual_functions", "[c_and_cpp]") {
  using namespace virtual_functions;
  // issue that arises from inheritance
  // e.g. have class "dog" that inherits from "animal"
  // non-virtual:
  // compile-time binding of function food()
  std::ostringstream os;
  dog *d = new dog(os);
  animal *a = new dog(os);
  REQUIRE(d->food() == "dog.food()");
  REQUIRE(a->food() == "animal.food()");  // NOT dog.food()
  delete d;
  // d is of type dog, so calls dog destructor, then animal destructor
  REQUIRE(os.str() == "~dog()\n~animal()\n");
  os = std::ostringstream("");
  delete a;  // only calls ~animal(), NOT ~dog()
  REQUIRE(os.str() == "~animal()\n");

  // virtual:
  // run-time binding of function food()
  // even if compile type is v_animal, at run-time v_dog.food() is called
  v_dog *v_d = new v_dog(os);
  v_animal *v_a = new v_dog(os);
  REQUIRE(v_d->food() == "v_dog.food()");
  REQUIRE(v_a->food() == "v_dog.food()");
  os = std::ostringstream("");
  delete v_d;
  REQUIRE(os.str() == "~v_dog()\n~v_animal()\n");
  // and similarly for destructor
  os = std::ostringstream("");
  delete v_a;  // calls ~v_dog(), then ~v_animal()
  REQUIRE(os.str() == "~v_dog()\n~v_animal()\n");
}

TEST_CASE("12.5 shallow_vs_deep_copy", "[c_and_cpp]") {
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

TEST_CASE("12.8 copy_node", "[c_and_cpp]") {
  std::unique_ptr<node<double>> head(new node<double>);
  head->data = 0.354;
  head->left.reset(new node<double>);
  head->left->data = 0.123;
  head->left->left.reset(new node<double>);
  head->left->left->data = 9.123;
  head->right.reset(new node<double>);
  head->right->data = 0.923;

  std::unique_ptr<node<double>> copy = copy_node<double>(head);

  REQUIRE(copy->data == head->data);
  REQUIRE(copy->left->data == head->left->data);
  REQUIRE(copy->right->data == head->right->data);
  REQUIRE(copy->left->left->data == head->left->left->data);
  REQUIRE(copy->left->right == nullptr);
}

TEST_CASE("12.9 SmartPointer", "[c_and_cpp]") {
  SmartPointer<double> p1(new double(4.0));
  REQUIRE(*p1 == 4.0);
  REQUIRE(p1.reference_count() == 1);
  {
    SmartPointer<double> p2(p1);
    *p2 = 5.0;
    REQUIRE(*p1 == 5.0);
    REQUIRE(*p2 == 5.0);
    REQUIRE(p1.reference_count() == 2);
    REQUIRE(p2.reference_count() == 2);
    {
      SmartPointer<double> p3 = p2;
      // use move constructor
      SmartPointer<double> p4(std::move(p2));
      // reference count unchanged,
      // we have a new pointer p4,
      // but since p2 was moved it is now out of scope
      *p4 += 1.0;
      // same story with move assignment constructor:
      // p4 now out of scope, ref count unchanged
      SmartPointer<double> p5;
      p5 = std::move(p4);
      REQUIRE(*p1 == 6.0);
      REQUIRE(*p3 == 6.0);
      REQUIRE(*p5 == 6.0);
      REQUIRE(p1.reference_count() == 3);
      REQUIRE(p3.reference_count() == 3);
      REQUIRE(p5.reference_count() == 3);
    }
    // p3, p5 out of scope
    REQUIRE(p1.reference_count() == 1);
  }
  REQUIRE(p1.reference_count() == 1);
}

TEST_CASE("12.10 align_malloc", "[c_and_cpp]") {
  // try to malloc too much memory: should return NULL
  REQUIRE(align_malloc(1ULL << 63, 4096) == NULL);

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

TEST_CASE("12.11 my_2d_alloc", "[c_and_cpp]") {
  // try to malloc too much memory: should return NULL
  REQUIRE(my_2d_alloc(1 << 31, 1 << 31) == NULL);

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
  free(arr);
}