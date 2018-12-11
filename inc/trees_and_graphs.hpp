#ifndef LKEEGAN_CTCI_TREES_AND_GRAPHS_H
#define LKEEGAN_CTCI_TREES_AND_GRAPHS_H
#include <forward_list>
#include <iostream>
#include <limits>
#include <memory>
#include <queue>
#include <vector>

namespace ctci {
namespace trees_and_graphs {

// some simple data structures
template <class T>
struct binary_tree_node {
  T data;
  std::unique_ptr<binary_tree_node> left;
  std::unique_ptr<binary_tree_node> right;
  explicit binary_tree_node(const T& data) : data(data) {}
};

template <class T>
struct nary_tree_node {
  T data;
  std::vector<std::unique_ptr<nary_tree_node>> children;
  explicit nary_tree_node(const T& data) : data(data) {}
};

// 4.2
// given array of unique values sorted in ascending order
// create binary search tree with minimal height
template <class T>
std::unique_ptr<binary_tree_node<T>> minimal_tree(
    const std::vector<T>& a, std::size_t first = 0,
    std::size_t last = std::numeric_limits<std::size_t>::max()) {
  last = std::min(last, a.size() - 1);
  std::size_t middle = (first + last) / 2;
  std::unique_ptr<binary_tree_node<T>> n(new binary_tree_node<T>(a[middle]));
  if (middle > first) {
    n.get()->left = minimal_tree(a, first, middle - 1);
  }
  if (last > middle) {
    n.get()->right = minimal_tree(a, middle + 1, last);
  }
  return n;
}

// 4.3
// Given binary tree, create linked list of all nodes
// at each depth, i.e. one linked list per level
template <class T>
using list_node_ptrs = std::forward_list<binary_tree_node<T>*>;
template <class T>
std::vector<list_node_ptrs<T>> list_of_depths(binary_tree_node<T>* node) {
  std::vector<list_node_ptrs<T>> depth_list;
  if (node) {
    depth_list.emplace_back(list_node_ptrs<T>{node});
  }
  while (!depth_list.empty()) {
    // go through list of nodes at this level
    // add all children to next level list
    list_node_ptrs<T> next_level;
    for (auto n : depth_list.back()) {
      if (n->left.get()) {
        next_level.push_front(n->left.get());
      }
      if (n->right.get()) {
        next_level.push_front(n->right.get());
      }
    }
    if (next_level.empty()) {
      // no nodes in next level, have gone through entire tree
      break;
    } else {
      next_level.reverse();  // to maintain left->right ordering of nodes
      depth_list.push_back(std::move(next_level));
    }
  }
  return depth_list;
}

// 4.4
// check if binary tree is balanced
// i.e. heights of two sub-trees do not differ by more than one
// BFS: find first level containing a leaf
// then go down max_allowed_difference levels
// and check if any nodes have children: if so not balanced
template <class T>
bool check_balanced(binary_tree_node<T>* node, int max_allowed_difference = 1) {
  std::queue<binary_tree_node<T>*> curr_level;
  std::queue<binary_tree_node<T>*> next_level;
  next_level.push(node);
  // set this flag once we see a leaf node
  bool SEEN_LEAF = false;
  while (!next_level.empty()) {
    // go to next level
    std::swap(next_level, curr_level);
    while (!curr_level.empty()) {
      // process each node in level
      node = curr_level.front();
      curr_level.pop();
      if (node->left) {
        // add left child to next level
        next_level.push(node->left.get());
      } else if (!node->right) {
        // check if node is a leaf node
        SEEN_LEAF = true;
      }
      if (node->right) {
        // add right child to next level
        next_level.push(node->right.get());
      }
    }
    if (SEEN_LEAF) {
      --max_allowed_difference;
      if (max_allowed_difference == 0) {
        // next level is the last one allowed for a balanced tree
        while (!next_level.empty()) {
          // process each node in next level
          node = next_level.front();
          next_level.pop();
          if (node->left || node->right) {
            // if node has a child, tree is not balanced
            return false;
          }
        }
      }
    }
  }
  return true;
}

// 4.5
// Check if binary tree is a binary search tree
// i.e. all lhs children <= node <= all rhs children
// using in order traversal of nodes
template <class T>
bool validate_bst(binary_tree_node<T>* node) {
  T prev_min{std::numeric_limits<T>::min()};
  return traverse_bst(node, prev_min);
}
template <class T>
bool traverse_bst(binary_tree_node<T>* node, T& prev_min) {
  bool IN_ORDER = true;
  if (node->left) {
    IN_ORDER &= traverse_bst(node->left.get(), prev_min);
  }
  if (node->data < prev_min) {
    return false;
  }
  prev_min = node->data;
  if (node->right) {
    IN_ORDER &= traverse_bst(node->right.get(), prev_min);
  }
  return IN_ORDER;
}

// some simple routines to test the data structures
// count elements in tree (DFS)
// using in order traversal (left child, node, right child)
template <class T>
int count_dfs(binary_tree_node<T>* tree_node) {
  int count = 0;
  if (tree_node) {
    if (tree_node->left) {
      count += count_dfs(tree_node->left.get());
    }
    ++count;
    if (tree_node->right) {
      count += count_dfs(tree_node->right.get());
    }
  }
  return count;
}

// find depth of tree (DFS)
// depth is the length of the longest path to a leaf (i.e. childless node)
template <class T>
int depth_dfs(binary_tree_node<T>* tree_node) {
  int left = 0;
  int right = 0;
  if (tree_node) {
    if (tree_node->left) {
      left += 1 + depth_dfs(tree_node->left.get());
    }
    if (tree_node->right) {
      right += 1 + depth_dfs(tree_node->right.get());
    }
  }
  return std::max(left, right);
}

// BFS check if tree is perfect, i.e.
// if the tree has k levels it contains 2^k - 1 nodes
template <class T>
bool is_perfect(binary_tree_node<T>* tree_node) {
  if (!tree_node) {
    return false;
  }
  std::queue<binary_tree_node<T>*> curr_nodes;
  std::queue<binary_tree_node<T>*> next_nodes;
  next_nodes.push(tree_node);
  int perfect_fill_children = 2;
  while (!next_nodes.empty()) {
    std::swap(curr_nodes, next_nodes);
    int count_children = 0;
    while (!curr_nodes.empty()) {
      auto node = curr_nodes.front();
      curr_nodes.pop();
      if (node->left) {
        next_nodes.push(node->left.get());
        ++count_children;
      }
      if (node->right) {
        next_nodes.push(node->right.get());
        ++count_children;
      }
    }
    if (count_children == perfect_fill_children) {
      // all nodes in this level have two children,
      // tree might be perfect, continue to next level
      perfect_fill_children *= 2;
    } else if (count_children == 0) {
      // no nodes in this level have children: perfect tree
      return true;
    } else {
      // not perfect tree
      return false;
    }
  }
  return true;
}

}  // namespace trees_and_graphs
}  // namespace ctci
#endif  // LKEEGAN_CTCI_TREES_AND_GRAPHS_H