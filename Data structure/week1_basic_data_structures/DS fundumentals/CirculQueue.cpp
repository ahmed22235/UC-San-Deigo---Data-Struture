#include<iostream>
using namespace std;

#define size 5
int CirQueue [size];
int front = -1;
int rear = -1;

bool full();
bool empty();
void Enqu(int val);
void Dequ();
int peek();
void display();

int main()
{
    Enqu(1);
    Enqu(2);
    Enqu(3);
    Enqu(4);
    Enqu(5);
    display();
    cout<<endl;
    Enqu(6);
    cout<<endl;
    Dequ();
    display();
    cout<<endl;
    Enqu(6);
    display();

}
bool empty(){
    if(front==-1 && rear==-1 )return true;
    else return false;
}

bool full(){
    if((front ==0 && rear ==size-1) || (front==rear+1))return true;
    else return false;
}

void Enqu(int val)
{
    if(full())cout<<"full"; // notace the control flow
    else{
        if(empty()){
            front = rear = 0;
            CirQueue[rear] = val;
        }else if(rear == size-1){
            rear =0;
            CirQueue[rear] = val;
        }
        else{
            CirQueue[++rear] = val;
        } 
    }
}

void Dequ(){
    if(empty())cout<<"empty";
    else{
        if(front==size-1)front=0;
        else if(front == rear)front = rear =-1;// mean that there is one elem
        else front++;
    }
}

int peek(){
     if(empty()){
        cout<<"empty";
        return 0;
     }
     else return CirQueue[front];
}

void display()
{
    if(empty())cout<<"empty";
    else{
        if(front<=rear){
            for(int i= front; i<=rear; i++){
            cout<<CirQueue[i]<<" ";
           }
        }
        else{
            for(int i= front; i<size; i++){
            cout<<CirQueue[i]<<" ";
           }
           for(int i= 0; i<=rear; i++){
            cout<<CirQueue[i]<<" ";
           }
        }
        
    }
}


