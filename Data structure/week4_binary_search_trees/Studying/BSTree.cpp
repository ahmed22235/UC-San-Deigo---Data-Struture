#include<iostream>
#include<vector>
using namespace std;
struct Treenode 
{
    int key;
    Treenode *left, *right, *parent;
    Treenode(int k) : key=(k) , left(nullptr), right(nullptr), parent(nullptr){}
};
class BST {
    private: 
      Treenode* root;
    public:
      BST() : root(nullptr) {}

      Treenode* find(int k, Treenode* R){
        //we travese to find the pointer which point to key
        if(R == nullptr)return nullptr;
        else if(R->key == k)return R;
        else if(R->key > k) return find(k, R.left);
        else if(R->key < k) return find(k, R.right);
      }
      Treenode* findmodify(int key, Treenode* R)
      {
        if(R==nullptr)return nullptr;
        if(R->key == key)return R;
        else if(R->key > key){
            if(R->left != nullptr)return findmodify(key, R->left)
            return R;
        }
        else if(R->key < key){
            if(R->right != nullptr)return findmodify(key, R->right);
            return R;
        }
      }

      Treenode* L_Des(Treenode* N){
        if(N->left==nullptr)return N->key;
        else return L_Des(N->left);
      }

      Treenode* R_ances(Treenode* N){
        if(N->parent == nullptr)return nullptr;
        if(N->parent->key > N.key)return N->parent;
        else return R_ances(N->parent);
      }

      Treenode* Next(Treenode* N)
      {
        if(N->right != nullptr)return L_Des(N->right);
        else return R_ances(N->left);
      }

      vector<Treenode*>Range(int s, int e, Treenode*R)
      {
        vector<Treenode*> result;
        if(R == nullptr)return result;

        Treenode* N = findmodify(s, R);
        while(N != nullptr && N.key<=e){
            if(N.key>=s)result.push_back(N);
            N = next(N);
        }
        return result;
      } 


      void insert(int k)
      {
        if(root == nullptr){
            root = new Treenode(k);
            return;
        }

        Treenode* N = findmodify(k,root);
        Treenode* newnode = new Treenode(k);
        newnode.parent = N;
        if(k<N.key) N->left  = newnode
        else N.right = newnode;

      }

      void delet(Treenode* N)
      {
        //Case one: Node N has no Right child 
        if(N->right ==nullptr)
        {
          // 1-If it the root 
          if(N->parent == nullptr){
            root = N->left;
            root->parent = nullptr;
          }
          // 2-If it a left child(itself)
          if(N->parent->left == N){
            N->parent->left = N.left;
            N->left->parent = N->parent
          }
          //3-if it right child(itself)
          else{
            N->parent->right = N->left;
            N->left->parent = N->parent
          }
        }

        //Case two: Node N has a right child
        else
        {
          Treenode x = next(N); // We are sure the it will not out scope of this subtree
          N->key = x.key;

          // Now we need to remove the node we taked its key
            // 1- the right child has lefts
            if(x.parent.left == x){
              x.parent.left = x.right
            }
            // 2- the right child has no left
            else{
              x.parent->right = x.right;
            }
            if(x.right) x.right->parent = x.parent;
            delete x;
            return 
        }
        delete N;
      }
      




}





