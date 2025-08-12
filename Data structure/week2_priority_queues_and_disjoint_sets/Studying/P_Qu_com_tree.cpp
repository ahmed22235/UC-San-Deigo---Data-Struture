#include<iostream>
#include<algorithm>
#include <climits>
#include<vector>
using namespace std;
// Priority Queue System using Complete Binary Tree (1-based indix)
#define Max_size 10
int Pri_Qu[Max_size];
int heap_size =0;

int parent (int idx){
    return idx/2;
}
int left_ch (int idx){
    return 2*idx;
}
int right_ch (int idx){
    return 2*idx + 1;
}

void SiftUp (int idx){
    while(idx>1 && Pri_Qu[parent(idx)]<Pri_Qu[idx]){
        swap(Pri_Qu[parent(idx)] , Pri_Qu[idx]);
        idx = parent(idx);
    }
}

void SiftDown(int idx){
    int maxidx = idx;
    int left = left_ch(idx);
    int right = right_ch(idx);
    if(left <= heap_size && Pri_Qu[left]>Pri_Qu[maxidx]) maxidx=left;

    if(right <= heap_size && Pri_Qu[right]>Pri_Qu[maxidx]) maxidx=right;
    //Base case for the recurence 
    if(idx != maxidx){
        swap(Pri_Qu[idx], Pri_Qu[maxidx]);
        SiftDown(maxidx);
    }
}

void insert (int val){
    if(heap_size == Max_size)cout<<"error";
    else{
        heap_size++;
        Pri_Qu[heap_size] = val;
        SiftUp(heap_size);
    }
}

int  ExMax (){
    int result = Pri_Qu[1];
    Pri_Qu[1] = Pri_Qu[heap_size];
    heap_size--;
    SiftDown(1);
    return result;
}

void remove(int idx){
    Pri_Qu[idx] = INT_MAX;
    SiftUp(idx);
    ExMax();
}

void changeP (int idx, int val){
    int oldp = Pri_Qu[idx];
    Pri_Qu[idx] = val;
    if(val > oldp)SiftUp(idx);
    else SiftDown(idx);
}

vector<int> naive_Hsort(vector<int> &A)
{
    heap_size = 0;
    for(int i =0; i<A.size(); i++){
        insert(A[i]);
    }
    for(int i = A.size()-1; i>0; i--){
        A[i] = ExMax();
    }
    return A;
}

// Optimal Heap sort

void Build_Heap(vector<int>&A){
    A.insert(A.begin(),0);// Dumy to save 1-based idx

    heap_size = A.size()-1;
    for(int i=heap_size/2; i>=1; i--){
        SiftDown(i);
    }
}

vector<int> Heap_S (vector<int>A){
    Build_Heap(A);
    heap_size = A.size();
    while(heap_size>1){
        swap(A[1],A[heap_size]);
        heap_size--;
        SiftDown(1);
    }
    return A;
}




