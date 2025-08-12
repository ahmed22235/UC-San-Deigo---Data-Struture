#include<iostream>
using namespace std;

struct node
{
    int value; 
    node* next;
};
node* front = NULL; 
node* rear = NULL;
void enqu (int val);
void dequ ();
void peek();
void display();

int main()
{

}

void enqu(int val)
{
    node* new_node = new node;
    new_node->value = val;
    new_node->next = NULL;
    if(front==NULL){
        front = rear = new_node;
    }
    else{
        rear->next = new_node;
        rear = new_node;
    }
}

void dequ(){
    if(rear == NULL)cout<<"empty";
    else if(front == rear)
    {
        node* ptr = front;
        front = rear = NULL;
        delete(ptr);
    }else{
        node* ptr = front;
        front = front->next;
        delete(ptr);
    }
}
void display()
{
    node* show;
    if(front == NULL)cout<<" l-list is empty";
    else{
        show = front;
        while(show != NULL)
        {
            cout<< show->value<< " ";
            show = show->next;
        }
    }
}

