#include "trees_and_graphs.hpp"
#include "catch.hpp"

// Unit tests
using namespace ctci::trees_and_graphs;

// do BF traversal of tree, append node data in order traversed to vector
// for ascending binary search tree, resulting vector is also ascending
void bfs_flatten_tree(binary_tree_node<int>* n, std::vector<int>& flat) {
  if (n->left) {
    bfs_flatten_tree(n->left.get(), flat);
  }
  flat.push_back(n->data);
  if (n->right) {
    bfs_flatten_tree(n->right.get(), flat);
  }
}
std::vector<int> vec_from_tree(binary_tree_node<int>* n) {
  std::vector<int> vec;
  bfs_flatten_tree(n, vec);
  return vec;
}

TEST_CASE("4.2 minimal_tree", "[trees_and_graphs]") {
  typedef binary_tree_node<int> tree;
  std::vector<int> ascending_ints{0};
  std::unique_ptr<tree> min_tree = minimal_tree(ascending_ints);
  REQUIRE(min_tree->data == 0);
  REQUIRE(min_tree->left == nullptr);
  REQUIRE(min_tree->right == nullptr);
  REQUIRE(vec_from_tree(min_tree.get()) == ascending_ints);
  REQUIRE(depth_dfs(min_tree.get()) == 0);

  ascending_ints = std::vector<int>{0, 2};
  min_tree = minimal_tree(ascending_ints);
  REQUIRE(min_tree->data == 0);
  REQUIRE(min_tree->left == nullptr);
  REQUIRE(min_tree->right->data == 2);
  REQUIRE(min_tree->right->left == nullptr);
  REQUIRE(min_tree->right->right == nullptr);
  REQUIRE(vec_from_tree(min_tree.get()) == ascending_ints);
  REQUIRE(depth_dfs(min_tree.get()) == 1);

  ascending_ints = std::vector<int>{0, 2, 7};
  min_tree = minimal_tree(ascending_ints);
  REQUIRE(min_tree->data == 2);
  REQUIRE(min_tree->left->data == 0);
  REQUIRE(min_tree->right->data == 7);
  REQUIRE(min_tree->left->left == nullptr);
  REQUIRE(min_tree->left->right == nullptr);
  REQUIRE(min_tree->right->left == nullptr);
  REQUIRE(min_tree->right->right == nullptr);
  REQUIRE(vec_from_tree(min_tree.get()) == ascending_ints);
  REQUIRE(depth_dfs(min_tree.get()) == 1);

  ascending_ints = std::vector<int>{1, 2, 3, 4, 5, 6, 7};
  min_tree = minimal_tree(ascending_ints);
  REQUIRE(vec_from_tree(min_tree.get()) == ascending_ints);
  REQUIRE(depth_dfs(min_tree.get()) == 2);

  ascending_ints = std::vector<int>{1, 2, 3, 4, 5, 16, 27, 99};
  min_tree = minimal_tree(ascending_ints);
  REQUIRE(vec_from_tree(min_tree.get()) == ascending_ints);
  REQUIRE(depth_dfs(min_tree.get()) == 3);

  ascending_ints = std::vector<int>{
      -928287, -324, -12, -7, -2, 0,  1,   2,     3,        4,         5,
      16,      27,   44,  67, 87, 99, 126, 45234, 52345234, 1242523532};
  min_tree = minimal_tree(ascending_ints);
  REQUIRE(vec_from_tree(min_tree.get()) == ascending_ints);
  REQUIRE(depth_dfs(min_tree.get()) == 4);
}

TEST_CASE("4.3 list_of_depths", "[trees_and_graphs]") {
  typedef binary_tree_node<int> tree;
  tree t(0);
  tree* node = &t;
  node->left = std::unique_ptr<tree>(new tree(1));
  node->right = std::unique_ptr<tree>(new tree(4));
  node->left->right = std::unique_ptr<tree>(new tree(9));
  node->right->left = std::unique_ptr<tree>(new tree(30));
  node->right->right = std::unique_ptr<tree>(new tree(14));

  std::vector<list_node_ptrs<int>> depth_list = list_of_depths(&t);
  REQUIRE(depth_list.size() == 3);
  REQUIRE(depth_list[0] == list_node_ptrs<int>{&t});
  REQUIRE(depth_list[1] == list_node_ptrs<int>{t.left.get(), t.right.get()});
  REQUIRE(depth_list[2] == list_node_ptrs<int>{t.left->right.get(),
                                               t.right->left.get(),
                                               t.right->right.get()});
}

TEST_CASE("4.4 check_balanced", "[trees_and_graphs]") {
  typedef binary_tree_node<int> tree;
  tree t(0);
  tree* node = &t;
  REQUIRE(check_balanced(node) == true);
  node->left = std::unique_ptr<tree>(new tree(1));
  REQUIRE(check_balanced(node) == true);
  node->left->left = std::unique_ptr<tree>(new tree(2));
  REQUIRE(check_balanced(node) == true);
  node->left->left->left = std::unique_ptr<tree>(new tree(3));
  REQUIRE(check_balanced(node) == true);
  node->right = std::unique_ptr<tree>(new tree(1));
  REQUIRE(check_balanced(node) == false);
  node->left->right = std::unique_ptr<tree>(new tree(2));
  REQUIRE(check_balanced(node) == false);
  node->right->right = std::unique_ptr<tree>(new tree(2));
  REQUIRE(check_balanced(node) == true);
  node->left->right->right = std::unique_ptr<tree>(new tree(3));
  REQUIRE(check_balanced(node) == true);
  node->left->right->left = std::unique_ptr<tree>(new tree(3));
  REQUIRE(check_balanced(node) == true);
  node->left->right->left->right = std::unique_ptr<tree>(new tree(4));
  REQUIRE(check_balanced(node) == false);
  node->left->left->left->right = std::unique_ptr<tree>(new tree(4));
  REQUIRE(check_balanced(node) == false);
  node->right->right->left = std::unique_ptr<tree>(new tree(3));
  REQUIRE(check_balanced(node) == true);
  node->left->right->right.reset();
  REQUIRE(check_balanced(node) == true);
  node->left->right->left.reset();
  REQUIRE(check_balanced(node) == false);
  node->left->right.reset();
  REQUIRE(check_balanced(node) == true);
  node->right->right.reset();
  REQUIRE(check_balanced(node) == false);
}

TEST_CASE("4.5 validate_bst", "[trees_and_graphs]") {
  std::vector<int> ints{1, 2, 3, 4, 5, 16, 27, 99};
  auto tree = minimal_tree(ints);
  CAPTURE(vec_from_tree(tree.get()));
  REQUIRE(validate_bst(tree.get()) == true);
  tree->data = 6;
  CAPTURE(vec_from_tree(tree.get()));
  REQUIRE(validate_bst(tree.get()) == false);
  tree->data = 5;
  CAPTURE(vec_from_tree(tree.get()));
  REQUIRE(validate_bst(tree.get()) == true);
  tree->data = 3;
  CAPTURE(vec_from_tree(tree.get()));
  REQUIRE(validate_bst(tree.get()) == true);
  tree->data = 2;
  CAPTURE(vec_from_tree(tree.get()));
  REQUIRE(validate_bst(tree.get()) == false);
  tree->left->right->data = 2;
  CAPTURE(vec_from_tree(tree.get()));
  REQUIRE(validate_bst(tree.get()) == true);

  ints = std::vector<int>{-121, -55, -8, 0,  0,  1,  2,  3,  4,  5,  16,
                          17,   20,  21, 25, 27, 55, 55, 55, 55, 55, 99};
  tree = minimal_tree(ints);
  CAPTURE(vec_from_tree(tree.get()));
  REQUIRE(validate_bst(tree.get()) == true);
  tree->left->right->data = 4;
  CAPTURE(vec_from_tree(tree.get()));
  REQUIRE(validate_bst(tree.get()) == true);
  tree->left->right->data = 2;
  CAPTURE(vec_from_tree(tree.get()));
  REQUIRE(validate_bst(tree.get()) == true);
  tree->left->right->data = 1;
  CAPTURE(vec_from_tree(tree.get()));
  REQUIRE(validate_bst(tree.get()) == false);
  tree->left->right->data = 5;
  CAPTURE(vec_from_tree(tree.get()));
  REQUIRE(validate_bst(tree.get()) == false);
}

TEST_CASE("4.6 successor", "[trees_and_graphs]") {
  two_way_bst<int> tree(30);
  tree.insert(10);
  tree.insert(50);
  tree.insert(3);
  tree.insert(6);
  tree.insert(2);
  tree.insert(2);
  tree.insert(18);
  tree.insert(51);
  tree.insert(49);
  tree.insert(99);
  tree.insert(0);
  tree.insert(1);
  tree.insert(5);
  tree.insert(7);
  tree.insert(8);
  tree.insert(8);
  tree.insert(9);
  two_way_bt_node<int>* head = nullptr;
  REQUIRE(successor(head) == nullptr);
  head = tree.head.get();
  // 10 -> 18
  REQUIRE(successor(head->left.get()) == head->left->right.get());
  // 30 -> 49
  REQUIRE(successor(head) == head->right->left.get());
  // 18 -> 30
  REQUIRE(successor(head->left->right.get()) == head);
  // 2 -> 3
  REQUIRE(successor(head->left->left->left.get()) == head->left->left.get());
  // 2 -> 2
  REQUIRE(successor(head->left->left->left->left.get()) ==
          head->left->left->left.get());
  // 1 -> 2
  REQUIRE(successor(head->left->left->left->left->left->right.get()) ==
          head->left->left->left->left.get());
  // 9 -> 10
  REQUIRE(successor(head->left->left->right->right->right->right.get()) ==
          head->left.get());
  // 99 -> null
  REQUIRE(successor(head->right->right->right.get()) == nullptr);
}

// data structure tests
TEST_CASE("binary_tree_node", "[trees_and_graphs]") {
  typedef binary_tree_node<int> tree;
  tree t(0);
  tree* node = &t;

  REQUIRE(count_dfs(&t) == 1);
  REQUIRE(depth_dfs(&t) == 0);
  REQUIRE(is_perfect(&t) == true);

  node->left = std::unique_ptr<tree>(new tree(1));

  REQUIRE(count_dfs(&t) == 2);
  REQUIRE(depth_dfs(&t) == 1);
  REQUIRE(is_perfect(&t) == false);

  node->right = std::unique_ptr<tree>(new tree(2));

  REQUIRE(count_dfs(&t) == 3);
  REQUIRE(depth_dfs(&t) == 1);
  REQUIRE(is_perfect(&t) == true);

  node->left->left = std::unique_ptr<tree>(new tree(3));

  REQUIRE(count_dfs(&t) == 4);
  REQUIRE(depth_dfs(&t) == 2);
  REQUIRE(is_perfect(&t) == false);

  node->left->right = std::unique_ptr<tree>(new tree(4));

  REQUIRE(count_dfs(&t) == 5);
  REQUIRE(depth_dfs(&t) == 2);

  node->right->left = std::unique_ptr<tree>(new tree(5));

  REQUIRE(count_dfs(&t) == 6);
  REQUIRE(depth_dfs(&t) == 2);

  node->left->left->left = std::unique_ptr<tree>(new tree(6));

  REQUIRE(count_dfs(&t) == 7);
  REQUIRE(depth_dfs(&t) == 3);

  node->left->left->left->right = std::unique_ptr<tree>(new tree(7));

  REQUIRE(count_dfs(&t) == 8);
  REQUIRE(depth_dfs(&t) == 4);

  node->left->left->left->right->left = std::unique_ptr<tree>(new tree(8));

  REQUIRE(count_dfs(&t) == 9);
  REQUIRE(depth_dfs(&t) == 5);
}
