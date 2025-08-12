#include <iostream>
#include <string>
#include <cmath>
using namespace std;
void rabin_karp(const string& T, const string& P, int d = 26, int q = 101) 
{
    int n = T.size();
    int m = P.size();

    int h = 1;
    for(int i=0; i<m-1; i++){ h = (h*d)%q; };

    int hash_T = 0;
    int hash_P = 0; 

    for(int i =0; i<m; i++){
        hash_P = (hash_P*d + static_cast<int>(P[i]))%q;
        hash_T = (hash_T*d + static_cast<int>(T[i]))%q;
    }

    for(int i=0; i<=n-m; i++){
        if (hash_P == hash_T){
            if(T.substr(i,m)==P)cout<<"p found at idx "<< i<<endl;
        }

        if(i< n-m)/// انت سابق بخطوة فوق 
        {
            // hash_T = (hash_T - static_cast<int>(T[i])*h) % q;
            // hash_T = d*hash_T;
            // hash_T = hash_T + static_cast<int>(T[i+m]) %q;
            hash_T = (d * (hash_T - static_cast<int>(T[i]) * h) + static_cast<int>(T[i + m])) % q;

            if(hash_T < 0) hash_T += q; // For the possibilty of negative values   
        }
    }

}
int main() {
    std::string text = "hello";
    std::string pattern = "ll";
    
    std::cout << "Text: " << text << std::endl;
    std::cout << "Pattern: " << pattern << std::endl;
    std::cout << "Searching for pattern in text:" << std::endl;
    
    rabin_karp(text, pattern);
    
    return 0;
}