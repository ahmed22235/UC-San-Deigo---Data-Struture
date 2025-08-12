#include <iostream>
#include <string>
#include <vector>

using std::string;
typedef unsigned long long ull;

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const std::vector<int>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

std::vector<int> get_occurrences(const Data& input) {
    const string& s = input.pattern, t = input.text;
    std::vector<int> ans;

    int n = t.size();
    int m = s.size();

    int d = 26 , q=101, h=1;
    for(int i =0; i<m-1; i++){
        h = (h*d)%q;
    }

    int hash_t = 0;
    int hash_s = 0;

    for(int i=0; i<m; i++){
        hash_s = (hash_s*d + static_cast<int>(s[i])) %q;
        hash_t = (hash_t*d + static_cast<int>(t[i])) %q;
    }

    for(int i=0; i<=n-m; i++){
        if(hash_s == hash_t){
        if (t.substr(i, m) == s) ans.push_back(i);
        }
        if(i<n-m){
            hash_t = (hash_t - static_cast<int>(t[i])*h)%q;
            hash_t = d*hash_t;
            hash_t = (hash_t + static_cast<int>(t[i+m]))%q;

            if(hash_t<0)hash_t+=q;
        }
    }
    return ans;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
    return 0;
}
