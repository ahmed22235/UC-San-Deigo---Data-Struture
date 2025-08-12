#include <iostream>
#include <vector>
#include <unordered_set>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Answer {
	size_t i, j, len;
};

// الفكرة كلها في استخدام prifix_sum
long long get_hash(int s, int len, const vector<long long> &H, long long m, long long pow_x) {
	long long hash = (H[s+len] - (H[s]*pow_x)%m + m) % m;
	return hash;
}


// هنا انا باخد استرينج واحد واحسبله هاشس بقدر الطول اللي ببعته واحفظه في سيت عشان المقارنة
// وبعد كدة ببدا احسب نفس الطول للاسترينج التاني واقارن في كل مرة لو لقيت ماتش ف السيت 
bool hasCommonsub(const string &s, const string &t, int leng, const vector<long long> &h_s, const vector<long long> &h_t, const vector<long long> &pow_x, long long m, Answer &ans) {
	if(leng == 0) return true;
	int n = s.size(), k = t.size();
	unordered_set<long long> hash_set;
	
	for(int i = 0; i <= n - leng; i++) {
		long long hash_s = get_hash(i, leng, h_s, m, pow_x[leng]);
		hash_set.insert(hash_s);
	}
	
	for(int j = 0; j <= k - leng; j++) {
		long long hash_t = get_hash(j, leng, h_t, m, pow_x[leng]);
		if(hash_set.find(hash_t) != hash_set.end()) {
			for(int i = 0; i <= n - leng; i++) {
				long long hash_s = get_hash(i, leng, h_s, m, pow_x[leng]);
				if(hash_s == hash_t) {
					if(s.substr(i, leng) == t.substr(j, leng)) {
						ans.i = i;
						ans.j = j;
						ans.len = leng;
						return true;
					}
				}
			}	
		}
	}
	return false;
}

Answer solve(const string &s, const string &t) {
	Answer ans = {0, 0, 0};
	srand(time(0));
	long long m = 1000000007;
	long long x = rand() % 1000000000 + 1;
	
	int n = s.size(), k = t.size();

	vector<long long> h_s(n+1, 0); 
	vector<long long> h_t(k+1, 0);

	int max_len = max(n, k);
	vector<long long> pow_x(max_len+1, 1);
	
	// Precompute powers of x
	for(int i = 1; i <= max_len; i++) {
		pow_x[i] = (pow_x[i-1] * x) % m;
	}

	// Compute prefix hashes for string s,t
	for(int i = 1; i <= n; i++) {
		h_s[i] = (x * h_s[i-1] + static_cast<int>(s[i-1])) % m;
	}
	
	for(int i = 1; i <= k; i++) {
		h_t[i] = (x * h_t[i-1] + static_cast<int>(t[i-1])) % m;
	}

	// Binary search on the length
	int left = 0, right = min(n, k);
	while(left < right) {
		int mid = (left + right + 1) / 2;
		if(hasCommonsub(s, t, mid, h_s, h_t, pow_x, m, ans)) {
			left = mid;
		} else {
			right = mid - 1;
		}
	}

	
	hasCommonsub(s, t, left, h_s, h_t, pow_x, m, ans);
	return ans;
}

int main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	string s, t;
	while (cin >> s >> t) {
		auto ans = solve(s, t);
		cout << ans.i << " " << ans.j << " " << ans.len << "\n";
	}
}