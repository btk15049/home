#ifndef VS
#include<bits/stdc++.h>
#endif

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

const int mod = 1e9 + 7;
typedef vector<LL> V;
typedef vector<V> VV;
int main() {
	string s;
	while (cin >> s) {
		VV dp(4, V(3, 0));
		dp[0][0] = 1;
		for (auto c : s) {
			VV nxt(4, V(3, 0));
			if (c == '0' || c == '?') {
				for (int i : range(4)) {
					nxt[i][1] += dp[i][0];
					nxt[i][2] += dp[i][1];
					nxt[i][1] += dp[i][2];
				}
			}
			if (c == '1' || c == '?') {
				for (int i : range(4)) {
					nxt[min(i + 1, 3)][0] += dp[i][0];
					nxt[i][0] += dp[i][1];
					nxt[i][1] += dp[i][2];
				}
			}
			for (auto &a : nxt)for (auto &b : a)b %= mod;
			swap(dp, nxt);
		}
		cout << (dp[3][0] + dp[3][1] + dp[3][2] + dp[2][0] + dp[2][1] + dp[1][0]) % mod << endl;
	}
	return 0;
}
