#include <iostream>
#include <vector>
using namespace std;

// Box/Node structure - holds key-value pair
struct Box {
    int key;
    int value;
    Box* next;

    Box(int k, int v) : key(k),value(v),next(nullptr){};
};

class HashTable{
    private: 
     vector<Box*>table;
     int table_size ;
     int hash(int key) {return key % table_size;}
    
    public:
     HashTable(int size =7){
        table_size = size;
        table.resize(table_size,nullptr);
     }

     bool hasKey(int key){
        int idx = hash(key);
        Box* curr = table[idx];
        while(curr != nullptr){
            if(curr->key==key)return true;
            curr = curr->next;
        }
        return false;
     }
     
     void set (int key, int value){
        int idx = hash(key);
        Box* curr = table[idx];
        while(curr != nullptr){
            if(curr->key == key) {
                curr->value = value;
                return ;
            }
            curr = curr->next;
        }
        Box* newbox = new Box(key,value);
        newbox->next = table[idx];
        table[idx] = newbox;
     }
     int get(int key) {
        int index = hash(key);
        Box* current = table[index];
        
        while (current != nullptr) {
            if (current->key == key) {
                return current->value;
            }
            current = current->next;
        }
        
        // Key not found
        throw runtime_error("Key not found!");
    }

    void display(){
        for(int i=0; i<table_size; i++){
            Box* curr = table[i];
            if(curr == nullptr)cout<<"empty";
            else{
                while(curr != nullptr){
                    cout<<'['<<curr->key <<','<<curr->value<<']';
                    if(curr->next!=nullptr)cout<<"-->";
                    curr = curr->next;
                }
            }
            cout<<endl;
        }
        cout<<endl;
    }
};

// Test the implementation
int main() {
    HashTable ht(7);  // Create hash table with size 7
    
    cout << "=== Testing Hash Table ===" << endl;
    
    // Test set function
    ht.set(10, 100);
    ht.set(22, 220);
    ht.set(31, 310);
    ht.set(17, 170);  // This might collide with 10 (17%7 = 3, 10%7 = 3)
    ht.set(15, 150);
    
    ht.display();
    
    // Test hasKey function
    cout << "hasKey(10): " << (ht.hasKey(10) ? "true" : "false") << endl;
    cout << "hasKey(99): " << (ht.hasKey(99) ? "true" : "false") << endl;
    
    // Test get function
    try {
        cout << "get(22): " << ht.get(22) << endl;
        cout << "get(17): " << ht.get(17) << endl;
        cout << "get(99): " << ht.get(99) << endl;  // This will throw error
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
    
    // Test updating existing key
    cout << "\nUpdating key 10 with new value 999:" << endl;
    ht.set(10, 999);
    ht.display();
    
    return 0;
}