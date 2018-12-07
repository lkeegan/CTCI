#include "trees_and_graphs.hpp"
#include "catch.hpp"

// Unit tests
using namespace ctci::trees_and_graphs;

TEST_CASE("list_of_depths", "[trees_and_graphs]") {
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
