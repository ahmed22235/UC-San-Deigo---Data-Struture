#include<iostream>
#include<vector>
using namespace std;

struct SplayTree {
    int key;
    SplayTree *left, *right, *parent ;
    SplayTree (int k) : key(k), left(nullptr),right(nullptr),parent(nullptr){}
};

class Splay 
{
    private:
      SplayTree *root;
      void rightRo (SplayTree* x)
      {
        SplayTree *y = x->left;
        x->left = y->right;
        if(y->right != nullptr) y->right->parent = x; 
        y->parent = x->parent;
        if(x->parent == nullptr) root = y;
        else if(x == x->parent->right) x->parent->right = y;
        else x->parent->left = y;

        y->right = x;
        x->parent = y;
      }
      
      void leftRo(SplayTree* x)
      {
        SplayTree *y = x->right;
        x->right = y->left;
        if(y->left != nullptr) y->left->parent = x; 
        y->parent = x->parent;
        if(x->parent == nullptr) root = y;
        else if(x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;

        y->left = x;
        x->parent = y;
      }

      void Splay(SplayTree* x)
      {
        while(x->parent != nullptr)
        {
            if(x->parent->parent == nullptr)
            {
                // zig step
             if(x == x->parent->left) rightRo(x->parent);
             else leftRo(x->parent);
            }
            else if((x == x->parent->left) && (x->parent == x->parent->parent->left))
            {
                // zig zig (left,left)
                rightRo(x->parent->parent);
                rightRo(x->parent);
            }
             }
            else if ((x == x->parent->right) && (x->parent == x->parent->parent->right)) {
                // Zig-Zig (Right-Right)
                leftRotate(x->parent->parent);
                leftRotate(x->parent);
            }
            else {
                // Zig-Zag cases
                if (x == x->parent->right && x->parent == x->parent->parent->left) {
                    // Left-Right
                    leftRotate(x->parent);
                    rightRotate(x->parent);
                }
                else {
                    // Right-Left
                    rightRotate(x->parent);
                    leftRotate(x->parent);
                }
        }
      }
    public:
      Splay(): root(nullptr){}
      SplayTree* find(int k, SplayTree *R)
      {
        if(R == nullptr)return nullptr; 
        if(R->key == k)return R;
        if(k < R->key) return find(k,R->left);
        if(k > R->key) return find(k,R->right);
      }
      SplayTree* L_Des(SplayTree* N){
        if(N->left==nullptr)return N;
        else return L_Des(N->left);
      }

      SplayTree* R_ances(SplayTree* N){
        if(N->parent == nullptr)return nullptr;
        if(N->parent->key > N->key)return N->parent;
        else return R_ances(N->parent);
      }

      SplayTree* Next(SplayTree* N)
      {
        if(N->right != nullptr)return L_Des(N->right);
        else return R_ances(N->left);
      }

      
};

