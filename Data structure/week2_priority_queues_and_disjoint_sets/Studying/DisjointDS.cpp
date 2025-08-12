#include<iostream>
#include<array>
#include<vector>
#include<algorithm>
using namespace std;

// Disjoint By Rank
struct DisjointDS
{
    vector<int>parent;
    vector<int>ranks;
    int n ;

    DisjointDS(int size){
        n = size;
        parent.resize(n);
        ranks.resize(n);
        for(int i=0; i<n; i++){
            parent[i]=i;
            ranks[i]=0;
        }
    }

    int find(int i){
        if(parent[i] != i){parent[i] = find(i)};
        return parent[i];
    }

    
    void Union (int i, int j){
       int i_id = find(i); 
       int j_id = find(j);

       if(i_id == j_id)return;

       int rank_i = ranks[i_id];
       int rank_j = ranks[j_id];

       if(rank_i<rank_j)parent[i_id] = j_id;
       else if(rank_i>rank_j)parent[j_id] = i_id;
       else { 
        parent[j_id] = i_id;
        ranks[i_id]++;
    }
       
       

    //    int new_root = min(i_id,j_id);

    //    for(int l = 0; i<n; i++){
    //     parent[l] = new_root;
    //    }
    }
};
