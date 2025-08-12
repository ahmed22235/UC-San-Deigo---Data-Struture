#include <algorithm>
#include <iostream>
#include <vector>
#include <climits> 

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node {
  int key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key, int left, int right) : key(key), left(left), right(right) {}
};

bool isBST(const vector<Node>& tree, int node_index, long long min_key, long long max_key) {
  if (node_index == -1)
    return true;

  const Node& node = tree[node_index];
  
  if (node.key < min_key || node.key >= max_key)
    return false;

  return isBST(tree, node.left, min_key, node.key) &&
         isBST(tree, node.right, node.key, max_key);
}

bool IsBinarySearchTree(const vector<Node>& tree) {
  if (tree.empty()) return true;
  return isBST(tree, 0, LLONG_MIN, LLONG_MAX);
}

int main() {
  int nodes;
  cin >> nodes;
  vector<Node> tree;
  for (int i = 0; i < nodes; ++i) {
    int key, left, right;
    cin >> key >> left >> right;
    tree.push_back(Node(key, left, right));
  }
  if (IsBinarySearchTree(tree)) {
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}
