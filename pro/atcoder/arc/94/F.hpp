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

constexpr int mod = 998244353;
int main() {
	string s;
	cin >> s;
	int n = s.size();
	vector<int> in(n);
	for (int i : range(n))in[i] = s[i] - 'a';
	set<vector<int>> all;
	queue<vector<int>> que;
	que.push(in);
	all.insert(in);
	while (que.empty() == false) {
		if (all.size() > 30)break;
		auto now = que.front();
		que.pop();
		for (int i : range(n - 1)) {
			if (all.size() > 30)break;
			if (now[i] == now[i + 1])continue;
			auto nxt = now;
			nxt[i] = nxt[i + 1] = 3 - now[i] - now[i + 1];
			if (all.count(nxt) == 0) {
				all.insert(nxt);
				que.push(nxt);
			}
		}
	}
	if (que.size() == 0) {
		cout << all.size() << endl;
	}
	else {
		int M = 0;
		for (int i : range(n)) {
			M = (M + in[i]) % 3;
		}
		LL ret = 1;
		for (int i : range(n-1)) {
			if (in[i] == in[i + 1])ret = 0;
		}
		using V = vector<LL>;
		using VV = vector<V>;
		using VVV = vector<VV>;

		VVV dp(2, VV(3, V(3,0)));
		for (int i : range(3))dp[0][i][i] = 1;
		for (int _ : range(n - 1)) {
			VVV nxt(2, VV(3, V(3, 0)));
			for (int i : range(2)) {
				for (int j : range(3)) {
					for (int k : range(3)) {
						for (int l : range(3)) {
							if (k == l) {
								nxt[i|1][(j + l) % 3][l] += dp[i][j][k];
							}
							else {
								nxt[i][(j + l) % 3][l] += dp[i][j][k];
							}
						}
					}
				}
			}
			for (auto &a : nxt)for (auto &b : a)for (auto &c : b)c %= mod;
			swap(dp, nxt);
		}
		cout << (ret + dp[1][M][0]+ dp[1][M][1]+dp[1][M][2]) % mod << endl;
	}

	return 0;
}
