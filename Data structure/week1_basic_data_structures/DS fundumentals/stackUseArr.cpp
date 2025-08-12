#include<iostream>
using namespace std;

#define size 5
int stack[size], top=-1;


void push(int val);
int pop ();
void peek();
void display();

int main ()
{
    push(15);
    push(20);
    push(25);
    display();
    cout<<endl;
    pop();
    display();
    cout<<endl;
    peek();
    //display();
}


void push(int val)
{
    if(top==size-1)cout<< "stack overflow";
    else{
        top++;
        stack[top]=val;
    }
}
int pop()
{
    if(top==size-1)cout<< "stack underflow";
    else{
        return stack[top--];
    }
}
void peek()
{
     if(top==size-1)cout<< "stack underflow";
    else{
        cout<< stack[top];
    }
}
void display()
{
    if(top==size-1)cout<< "stack underflow";
    else{
        for(int i = top; i>=0; i--){
            cout<<stack[i]<<endl;
        }
    }
}