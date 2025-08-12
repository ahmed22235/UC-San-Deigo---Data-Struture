#include<iostream>
using namespace std;
struct node
{
    int value ; 
    node* next; // pointer point to node struct 
};

node* head = NULL;

void insertNode (int val);

void display();

void deletNode (int val);

void insertBegin(int val);



int main ()
{
   insertNode(10);
   insertNode(15);
   insertNode(7);
   display();
   //deletNode(15);
   cout<<endl;
   display();
  // deletNode(5);
   cout<<endl;
   display();
   insertBegin(5);
   cout<<endl;
   display();
}
void insertNode (int val)
{
// Remember, u want to put this value in nooooode struct, then u must build node first.
    node* new_node , *last;
    new_node = new node;
    new_node->value = val;
    if(head == NULL){
        head = new_node;
        new_node->next = NULL;
    }
    else{
        last = head;
        while(last->next != NULL){
            last = last->next;
        }
        last->next = new_node;
        new_node->next = NULL;
    }
}
void display()
{
    node* show;
    if(head == NULL)cout<<" l-list is empty";
    else{
        show = head;
        while(show != NULL)
        {
            cout<< show->value<< " ";
            show = show->next;
        }
    }
}

void deletNode (int val)
{
    node* currentNode, *beforNode;
    currentNode = head; 
    beforNode = head;
    if(currentNode->value == val)
    {
        head = currentNode->next;
        return;
    }
    while(currentNode->value != val)
    {
        beforNode = currentNode;
        currentNode = currentNode->next;
    }
    beforNode->next = currentNode->next;
} 

void insertBegin(int val)
{
    node* new_node = new node;
    new_node->value = val;
    new_node->next = head;
    head = new_node;
}

