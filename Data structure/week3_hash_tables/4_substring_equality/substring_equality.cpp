#include <iostream>
#include <vector>
#include<string>
#include <cstdlib>  
#include <ctime>   
using namespace std;

class Solver {
	string s;
	int n;
	vector<long long> h1, h2;
	long long x;
	vector<long long> pow_x1, pow_x2;
	static const long long m1 = 1000000007; 
    static const long long m2 = 1000000009;
public:	
	Solver(string s) : s(s),n(s.size()) {	
		// initialization, precalculation
		srand(time(0));
        x = rand() % 1000000000 + 1;
		h1.resize(n+1,0);
		h2.resize(n+1,0);
		pow_x1.resize(n+1,1);
		pow_x2.resize(n+1,1);
		for(int i=1; i<=n; i++)
		{ 
			pow_x1[i]=(pow_x1[i-1]*x)%m1;
			pow_x2[i]=(pow_x2[i-1]*x)%m2;
		}

		for(int i=1; i<=n; i++){
			h1[i] = (x*h1[i-1]+static_cast<int>(s[i-1]))%m1;
			h2[i] = (x*h2[i-1]+static_cast<int>(s[i-1]))%m2;
		}
	}

	pair<long long, long long>get_hash(int start , int len){
		long long hash1 =( h1[start+len] - (h1[start]*pow_x1[len])%m1 + m1)%m1;
		long long hash2 = (h2[start+len] - (h2[start]*pow_x2[len])%m2 + m2)%m2;
		return {hash1,hash2};
	}
	bool ask(int a, int b, int l) {
		 if(a + l > n || b + l > n) return false;
		 auto hash_a = get_hash(a,l);
		 auto hash_b = get_hash(b,l);
		 return (hash_a.first == hash_b.first) && (hash_a.second == hash_b.second);
	}
};

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);

	string s;
	int q;
	cin >> s >> q;
	Solver solver(s);
	for (int i = 0; i < q; i++) {
		int a, b, l;
		cin >> a >> b >> l;
		cout << (solver.ask(a, b, l) ? "Yes\n" : "No\n");
	}
}
