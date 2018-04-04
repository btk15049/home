#include<bits/stdc++.h>

using namespace std;
typedef long long LL;

#ifdef BTK
#define DEBUG if(1)
#else
#define CIN_ONLY if(1)
struct cww {cww() {CIN_ONLY{ios::sync_with_stdio(false); cin.tie(0);}}
}star;
#define DEBUG if(0)
#endif

#define ALL(v) (v).begin(),(v).end()
#define REC(ret, ...) std::function<ret (__VA_ARGS__)>
template <typename T>inline bool chmin(T &l, T r){bool a = l>r; if (a)l = r; return a;}
template <typename T>inline bool chmax(T &l, T r){bool a = l<r; if (a)l = r; return a;}
template <typename T>istream& operator>>(istream &is, vector<T> &v){for (auto &it : v)is >> it;return is;}

class range {private: struct I { int x; int operator*() { return x; }bool operator!=(I& lhs) { return x<lhs.x; }void operator++() { ++x; } }; I i, n;public:range(int n) :i({ 0 }), n({ n }) {}range(int i, int n) :i({ i }), n({ n }) {}I& begin() { return i; }I& end() { return n; }};
// 1 2 3 4
// 4 1 2 3 
// 1 4 2 3
// 
typedef vector<int> V;
int main() {
	
	for (int i : range(1,10)) {
		V o(i);
		iota(ALL(o), 0);
		int ret = 0;
		do {
			V used(i,0);
			for (int j : range(i)) {
				if (used[(o[j] + 1) % i] == 0) {
					used[o[j]] = 1;
				}
			}
			ret += used[0];
		} while (next_permutation(ALL(o)));
		cout << ret << ",";
	}
	return 0;
}
