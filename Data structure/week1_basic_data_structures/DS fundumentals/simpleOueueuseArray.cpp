#include<iostream>
using namespace std;

#define size 5
int queue[size];
int front = -1;
int rear = -1;

void Enqu(int val);
void Dequ();
int peek();
void display();

int main()
{
    Enqu(5);
    Enqu(10);
    Enqu(15);

    display();
    cout<<endl;
    Dequ();
    display();
    cout<<endl;
    cout<<peek();
}

void Enqu(int val)
{
    if(rear != size-1)
    {
        if(front==-1 && rear==-1){
        front++;
        queue[++rear] = val;
       }
        else {
        queue[++rear] = val;
      }
    }else{
        cout<<"Queue is full";
    }
}

void Dequ(){
    if(front !=-1 && rear !=-1 && front<=rear)front++;
    else cout<<"empty";
}

int peek(){
    if(front !=-1 && rear !=-1 && front<=rear)return front++;
    else cout<<"empty";
    return 0;
}

void display(){
    if(front !=-1 && rear !=-1 && front<=rear){
        for(int i = front; i<=rear; i++){
            cout<<queue[i]<<" ";
        }
    }else cout<<"empty";    
}


