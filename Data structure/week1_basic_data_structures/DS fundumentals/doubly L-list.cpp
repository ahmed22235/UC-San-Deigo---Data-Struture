#include<iostream>
using namespace std;

struct node {
    int value;
    node* next = NULL;
    node* prev = NULL;
};

node* head = NULL;
node* tail = NULL;

void insertNodeEnd (int val);
void insertNodeBegin (int val);
void deletNode(int val);
void displayForward ();
void displayBackward();

int main() {
    insertNodeEnd(5);
    insertNodeEnd(10);
    insertNodeEnd(15);
    insertNodeBegin(3);
    
    cout << "Forward: ";
    displayForward();
    cout << "\nBackward: ";
    displayBackward();
    
    deletNode(10);
    cout << "\nAfter deleting 10: ";
    displayForward();
    
    return 0;
}

void insertNodeEnd (int val)
{
    node* new_node = new node;
    new_node->value = val;
    if(head == NULL)
    {
        head = new_node;
        tail = new_node;
    }
    else{
        tail->next = new_node;
        new_node->prev = tail;
        tail = new_node;
    }
}

void insertNodeBegin (int val)
{
    node* new_node = new node;
    new_node->value = val; 
    if(head == NULL)
    {
        head = new_node;
        tail = new_node; 
    }
    else{
        new_node->next = head;
        head->prev = new_node;
        head = new_node;
    }
}

void deletNode(int val)
{
    if (head == NULL) return; //1-Empty
    node* temp = head;
    
    // ✅ FIXED: Find the node with the value
    while(temp != NULL && temp->value != val)
    {
        temp = temp->next;
    }
    
    if(temp == NULL) return; // Value not found
    
    if(temp == head && temp == tail)// 2-only one node 
    {
        head = NULL;
        tail = NULL;
    }
    else if(temp == head ) // 3-first node
    {
        head = head->next;  
        head->prev = NULL;
    }
    else if(temp == tail) //4-last tail
    {
        tail = temp->prev;
        tail->next = NULL;
    }
    else {
        node* temp2 = temp;
        temp2 = temp->prev;
        temp2->next = temp->next;
        
        temp2 = temp->next;
        temp2->prev = temp->prev;
    }
    delete temp;
}

void displayForward (){
    node* temp = head;
    while(temp != NULL)
    {
        cout<<temp->value<<" ";
        temp = temp->next;
    }
}

void displayBackward(){
   node* temp = tail;
   while(temp != NULL)
   {
    cout<<temp->value<<" ";
    temp = temp->prev;
   } 
}