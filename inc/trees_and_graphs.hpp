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
struct two_way_bt_node {
  T data;
  std::unique_ptr<two_way_bt_node> left;
  std::unique_ptr<two_way_bt_node> right;
  two_way_bt_node* parent = nullptr;
  explicit two_way_bt_node(const T& data) : data(data) {}
};

template <class T>
struct nary_tree_node {
  T data;
  std::vector<std::unique_ptr<nary_tree_node>> children;
  explicit nary_tree_node(const T& data) : data(data) {}
};

// binary search tree, where each node has a pointer to its parent
template <class T>
struct two_way_bst {
  std::unique_ptr<two_way_bt_node<T>> head;
  explicit two_way_bst(const T& data)
      : head(
            std::unique_ptr<two_way_bt_node<T>>(new two_way_bt_node<T>(data))) {
  }
  void insert(const T& data) {
    two_way_bt_node<T>* new_node = head.get();
    while (new_node) {
      if (data > new_node->data) {
        // if value is larger, it goes to the right
        if (!new_node->right) {
          // insert here if there is space
          new_node->right =
              std::unique_ptr<two_way_bt_node<T>>(new two_way_bt_node<T>(data));
          new_node->right->parent = new_node;
          new_node = nullptr;
        } else {
          // otherwise go to right child and repeat
          new_node = new_node->right.get();
        }
      } else {
        // same on left side if value is smaller
        if (!new_node->left) {
          new_node->left =
              std::unique_ptr<two_way_bt_node<T>>(new two_way_bt_node<T>(data));
          new_node->left->parent = new_node;
          new_node = nullptr;
        } else {
          new_node = new_node->left.get();
        }
      }
    }
  }
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

// 4.6
// find sucessor of given node in BST (next value in order)
// where we can assume that each node has a link to its parent

template <class T>
two_way_bt_node<T>* successor(two_way_bt_node<T>* node) {
  if (node) {
    if (node->right) {
      // if we have a right child it will be larger
      node = node->right.get();
      // then take all available left nodes to find smallest
      // value in this subtree
      while (node->left) {
        node = node->left.get();
      }
    } else {
      // otherwise climb tree until we have a larger parent
      // i.e. one whose right child is not the one we just climbed up from
      while (node->parent && (node->parent->right.get() == node)) {
        node = node->parent;
      }
      node = node->parent;
    }
  }
  return node;
}

// 4.8
// find first common ancestor of two nodes in a binary tree
// without storing nodes in an additional data structure
// equivalently: find head of smallest sub-tree that contains the two nodes
template <class T>
binary_tree_node<T>* first_common_ancestor(
    binary_tree_node<T>* head, const std::vector<binary_tree_node<T>*>& nodes) {
  // DFS count matching nodes in left and right sub-trees starting
  // from head, then recurse on sub-tree containing all nodes
  // O(n_nodes_to_match n_nodes_in_tree^2) time, O(1) space
  // Alternatively, could use
  // O(n_nodes_in_tree) time and O(n_nodes_in_tree) space to make a copy of tree
  // including a link to parent in each node, then ascend tree from each of the
  // desired nodes until they converge on the common ancestor.
  std::size_t right_count = 0;
  std::size_t left_count = 0;
  if (head->right) {
    // count matching nodes in right sub-tree
    right_count = count_matching_nodes(head->right.get(), nodes);
  }
  if (right_count == nodes.size()) {
    // if right sub-tree contains all nodes, set as new head
    return first_common_ancestor(head->right.get(), nodes);
  } else {
    if (head->left) {
      // otherwise count matching nodes in left sub-tree
      left_count = count_matching_nodes(head->left.get(), nodes);
    }
    if (left_count == nodes.size()) {
      // if left sub-tree contains all nodes, set as new head
      return first_common_ancestor(head->left.get(), nodes);
    }
  }
  if (left_count + right_count == nodes.size()) {
    // otherwise we are either at the head of the smallest sub-tree
    // that contains all nodes, in which case return it
    return head;
  } else {
    // or the tree doesn't contain the desired nodes, so return null
    return nullptr;
  }
}
template <class T>
std::size_t count_matching_nodes(
    binary_tree_node<T>* head, const std::vector<binary_tree_node<T>*>& nodes) {
  std::size_t nodes_found = 0;
  if (head->right) {
    nodes_found += count_matching_nodes(head->right.get(), nodes);
  }
  for (binary_tree_node<T>* node : nodes) {
    if (head == node) {
      ++nodes_found;
    }
  }
  if (head->left) {
    nodes_found += count_matching_nodes(head->left.get(), nodes);
  }
  return nodes_found;
}
// some simple convenience routines for creating tests using the data
// structures

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
