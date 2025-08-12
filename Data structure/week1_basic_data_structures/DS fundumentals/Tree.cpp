#include<iostream>
using namespace std;
struct Treenode 
{
    int data;
    Treenode *left, *right;
};

Treenode* creattree(int value)
{
    Treenode* new_node = new Treenode;
    new_node->data = value;
    new_node->left = new_node->right = NULL;
    return new_node;
}

void preord ( Treenode* root ){// Preorder (data->left->right)
    if(root == nullptr)return; // Base case for the recursion

    cout << root->data<<" ";
    preord(root->left);
    preord(root->right);
}

void inord (Treenode* root) // Inorder (left -> data -> right)
{
    if(root == nullptr)return;
    inord(root->left);
    cout<<root->data<<" ";
    inord(root->right);
} 

void postord (Treenode* root) // (left right data)
{
    if(root == nullptr)return;
    postord(root->left);
    postord(root->right);
    cout<<root->data<<" ";
}

int main ()
{
    // root
    Treenode* root = creattree(1);
    // left parent node
    root->left = creattree(2);
    root->left->left = creattree(4);
    root->left->right = creattree(5);
    root->left->right->left = creattree(9);
    // right parent node 
    root->right = creattree(3);
    root->right->left = creattree(6); 
    root->right->right = creattree(7);
    root->right->right->left = creattree(15);

    cout <<"Inorder (left, root, right) Debth first search"<<endl;
    inord(root);
}