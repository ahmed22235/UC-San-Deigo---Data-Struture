#include <iostream>
#include <vector>
#include <algorithm>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using std::vector;
using std::ios_base;
using std::cin;
using std::cout;

class TreeOrders {
  int n;
  vector <int> key;
  vector <int> left;
  vector <int> right;

public:
  void read() {
    cin >> n;
    key.resize(n);
    left.resize(n);
    right.resize(n);
    for (int i = 0; i < n; i++) {
      cin >> key[i] >> left[i] >> right[i];
    }
  }

  vector <int> in_order() {
    vector<int> result;
    vector<int> stack;
    int current = 0;
    
    if (n == 0) return result;
    
    while (!stack.empty() || current != -1) {
      // Go to leftmost node
      while (current != -1) {
        stack.push_back(current);
        current = left[current];
      }
      
      // Current is now -1, so we pop from stack
      current = stack.back();
      stack.pop_back();
      result.push_back(key[current]);
      
      // Visit right subtree
      current = right[current];
    }
    
    return result;
  }

  vector <int> pre_order() {
    vector<int> result;
    vector<int> stack;
    
    if (n == 0) return result;
    
    stack.push_back(0);
    
    while (!stack.empty()) {
      int current = stack.back();
      stack.pop_back();
      
      result.push_back(key[current]);
      
      // Push right first, then left (so left is processed first)
      if (right[current] != -1) {
        stack.push_back(right[current]);
      }
      if (left[current] != -1) {
        stack.push_back(left[current]);
      }
    }
    
    return result;
  }

  vector <int> post_order() {
    vector<int> result;
    vector<int> stack;
    int current = 0;
    int lastVisited = -1;
    
    if (n == 0) return result;
    
    while (!stack.empty() || current != -1) {
      // Go to leftmost node
      if (current != -1) {
        stack.push_back(current);
        current = left[current];
      } else {
        int peekNode = stack.back();
        
        // If right child exists and hasn't been processed yet
        if (right[peekNode] != -1 && lastVisited != right[peekNode]) {
          current = right[peekNode];
        } else {
          result.push_back(key[peekNode]);
          lastVisited = stack.back();
          stack.pop_back();
        }
      }
    }
    
    return result;
  }
};

void print(vector <int> a) {
  for (size_t i = 0; i < a.size(); i++) {
    if (i > 0) {
      cout << ' ';
    }
    cout << a[i];
  }
  cout << '\n';
}

int main_with_large_stack_space() {
  ios_base::sync_with_stdio(0);
  TreeOrders t;
  t.read();
  print(t.in_order());
  print(t.pre_order());
  print(t.post_order());
  return 0;
}

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
      if (rl.rlim_cur < kStackSize)
      {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
          {
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }
#endif

  return main_with_large_stack_space();
}