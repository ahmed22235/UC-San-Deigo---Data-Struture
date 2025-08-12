#include<iostream>
#include<vector>
using namespace std;

// Forward declaration
class AVLTree;

struct AVLNode {
    int key;
    int hi;
    AVLNode* left;      
    AVLNode* right;     
    AVLNode* parent;    

    AVLNode(int k) : key(k), hi(1), left(nullptr), right(nullptr), parent(nullptr) {}
};

class AVLTree  
{
private:
    AVLNode* root;
    
public:
    AVLTree() : root(nullptr) {}
    AVLNode* find(int k, AVLNode* R){
        //we travese to find the pointer which point to key
        if(R == nullptr)return nullptr;
        else if(R->key == k)return R;
        else if(R->key > k) return find(k, R.left);
        else if(R->key < k) return find(k, R.right);
      }

    int get_hi(AVLNode* node) {
        if(node == nullptr) return 0;
        return node->hi;
    }
    
    int get_balance(AVLNode* node) {
        if(node == nullptr) return 0;  
        return get_hi(node->left) - get_hi(node->right);
    }

    void update_hi(AVLNode* node) {
        if(node != nullptr) {
            node->hi = 1 + max(get_hi(node->left), get_hi(node->right)); 
        }
    }

    AVLNode* rotateR(AVLNode* y) {
        AVLNode* x = y->left;  
        AVLNode* temp = x->right;  
        
        x->right = y;
        y->left = temp;

        update_hi(y);
        update_hi(x);

        return x;  // the new root of subtree
    }

    AVLNode* rotateL(AVLNode* x) {  
        AVLNode* y = x->right;   
        AVLNode* temp = y->left;
        
        y->left = x;  
        x->right = temp; 

        update_hi(x); 
        update_hi(y);

        return y;  
    }

    AVLNode* insertHelper(AVLNode* node, int key) {  
        // 1- There is no tree 
        if(node == nullptr) return new AVLNode(key);

        // 2-There is tree 
        if(key < node->key) {
            node->left = insertHelper(node->left, key);
        }
        else if(key > node->key) {  
            node->right = insertHelper(node->right, key);  
        }
        else {
            return node;  // duplicate not allowed
        }
        
        update_hi(node);
        int balance = get_balance(node);

        // 1-LL case 
        if(balance > 1 && key < node->left->key) {
            return rotateR(node);
        }
        
        // 2-RR case
        if(balance < -1 && key > node->right->key) {  
            return rotateL(node);
        }
        
        // 3-LR case
        if(balance > 1 && key > node->left->key) {
            node->left = rotateL(node->left);
            return rotateR(node);
        }
        
        // 4-RL case
        if(balance < -1 && key < node->right->key) { 
            node->right = rotateR(node->right);  
            return rotateL(node);  
        }
        
        return node;
    }
    
    void insert(int key) {
        root = insertHelper(root, key);
    }


    void delet(AVLNode* N)
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
          AVLNode x = next(N); // We are sure the it will not out scope of this subtree
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

    AVLNode* Merge_W_root(AVLNode*R1, AVLNode* R2, AVLNode* T){
        T->left = R1;
        T->right = R2;
        R1->parent = T;
        R2->parent = T;
        return T;
    }
    AVLNode* Merge(AVLNode* R1, AVLNode* R2)
    {
        AVLNode* T = find(INT_MAX, R1);
        delet(T);
        return Merge_W_root(R1,R2,T)
    }

    AVLNode* AVL_Merge(AVLNode* R1, AVLNode* R2,  AVLNode* T)
    {
        if(abs((R1->hi - R2->hi))<=1){
            return Merge_W_root(R1,R2,T);
        }
        else if(R1->hi > R2->hi){
            AVLNode* R = AVL_Merge(R1->right,R2,T);
            R1->right = R; 
            R->parent = R1;
            update_hi(R1);
            int balance = get_balance(R1);
            //RR Prpblem --> lead to left rotation
            if (balance < -1 && get_balance(R1->right) <= 0)
            return rotateL(R1);
            //RL problem --> lead to right rotation then left
        if (balance < -1 && get_balance(R1->right) > 0) {
            R1->right = rotateR(R1->right);
            return rotateL(R1);
        }

          return R1;        }
        else {
            R2->left = AVL_Merge(R1, R2->left, T);
            R2->left->parent = R2;
            update_hi(R2);
            int balance = get_balance(R2);
            //LL problem lead to Right rotation 
            if (balance > 1 && get_balance(R2->left) >= 0)
            return rotateR(R2);
            //LR problem lead to lift rotation then right 
            if (balance > 1 && get_balance(R2->left) < 0) {
            R2->left = rotateL(R2->left);
            return rotateR(R2);
           }

        return R2;
         }
    }

    pair<AVLNode*, AVLNode*> Split(AVLNode* R ,int x)
    {
        if(R==nullptr)return {nullptr, nullptr};
        if( x <=R->key){
            auto res = Split(R->left,x);
            AVLNode* R3 = Merge_W_root(res.second,R->right, R);
            return {res.first,R3};
        }
        if( x >R->key){
            auto res = Split(R->right,x);
            AVLNode* R3 = Merge_W_root(R->left,res.first, R);
            return {R3,res.second};
        }
        
    }



       



















    void inorderHelper(AVLNode* node) {
        if (node != nullptr) {
            inorderHelper(node->left);
            cout << node->key << "(h:" << node->hi << ") ";
            inorderHelper(node->right);
        }
    }

    void printInorder() {
        cout << "Tree (inorder): ";
        inorderHelper(root);
        cout << endl;
    }

    AVLNode* getRoot() {
        return root;
    }
    
    void setRoot(AVLNode* newRoot) {
        root = newRoot;
    }
};

// Test function
int main() {
    AVLTree tree;
    
    cout << "Testing AVL Tree Implementation:" << endl;
    
    // Test basic insertions
    cout << "\nInserting: 10, 20, 30 (should trigger left rotation)" << endl;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);  // This should cause RR case -> left rotation
    tree.printInorder();
    
    cout << "\nInserting: 40, 50, 25" << endl;
    tree.insert(40);
    tree.insert(50);
    tree.insert(25);
    tree.printInorder();
    
    // Test LL case
    cout << "\nInserting: 5, 3, 1 (should trigger right rotation)" << endl;
    tree.insert(5);
    tree.insert(3);
    tree.insert(1);   // This should cause LL case -> right rotation
    tree.printInorder();
    
    return 0;
}