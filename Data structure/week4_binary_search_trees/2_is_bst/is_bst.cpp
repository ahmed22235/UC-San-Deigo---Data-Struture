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
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

bool IsBinarySearchTree(const vector<Node>& tree) {
  if (tree.empty()) return true;
  
 
  vector<vector<long long>> stack;
  stack.push_back({0, LLONG_MIN, LLONG_MAX}); 
  
  while (!stack.empty()) {
    vector<long long> current = stack.back();
    stack.pop_back();
    
    int nodeIndex = (int)current[0];
    long long minBound = current[1];
    long long maxBound = current[2];
    
    if (tree[nodeIndex].key <= minBound || tree[nodeIndex].key >= maxBound) {
      return false;
    }
    
    if (tree[nodeIndex].right != -1) {
      stack.push_back({tree[nodeIndex].right, (long long)tree[nodeIndex].key, maxBound});
    }
    
    if (tree[nodeIndex].left != -1) {
      stack.push_back({tree[nodeIndex].left, minBound, (long long)tree[nodeIndex].key});
    }
  }
  
  return true;
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