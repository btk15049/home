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

typedef vector<int> V;
typedef vector<V> VV;
int N;
VV g;
int sz[5123];
VV branch;
void dfs(int v = 0, int p = -1) {
	sz[v] = 1;
	branch[v].push_back(N - 1);
	for (int u : g[v]) {
		if (p == u)continue;
		dfs(u, v);
		sz[v] += sz[u];
		branch[v].push_back(sz[u]);
		branch[v].front() -= sz[u];
	}
}
constexpr int mod = 1e9 + 7;
// mÇñ@Ç∆Ç∑ÇÈaÇÃãtå≥
// O(log a)
inline LL invMod(LL a, LL m = mod) {
	LL b = m, u = 1, v = 0;
	while (b) {
		LL t = a / b;
		swap(a -= t * b, b);
		swap(u -= t * v, v);
	}
	return (u % m + m) % m;
}

// äKèÊ
// O(n)
constexpr int SZ = 112345;
LL fact[SZ];
LL rfact[SZ];
struct fact_ {
	fact_() {
		fact[0] = 1;
		for (int i = 1; i<SZ; i++)
			fact[i] = fact[i - 1] * i%mod;
		rfact[SZ - 1] = invMod(fact[SZ - 1]);
		for (int i = SZ - 1; i>0; i--) {
			rfact[i - 1] = rfact[i] * i%mod;
		}
	}
}fact_init;
// O(1)
LL Comb(LL n, LL k) {
	LL u = fact[n];
	LL d = (rfact[k] * rfact[n - k]) % mod;
	return u * d%mod;
}

//O(1)
LL Perm(LL n, LL k) {
	LL u = fact[n];
	LL d = rfact[n - k] % mod;
	return u * d%mod;
}

LL dp[5123];
LL f(int v) {
	for (int i : range(N)) {
		dp[i] = 0;
	}
	dp[0] = 1;
	int ub = 1;
	for (auto cnt : branch[v]) {
		ub += cnt;
		for (int i = ub - 1; i >= 0; i--) {
			for (int j = 1; j <= min(i, cnt); j++) {
				LL c = Comb(cnt, j) * Perm(cnt, j) % mod;
				dp[i] += dp[i - j] * c %mod;
			}
			dp[i] %= mod;
		}
	}
	LL ret = 0;
	for (int i : range(N)) {
		if (i & 1) {
			ret += mod - dp[i] * fact[N - i] % mod;
		}
		else {
			ret += dp[i] * fact[N - i] % mod;
		}
	}
	return ret % mod;
}

void solve() {
	g = VV(N);
	branch = VV(N);
	for (int i : range(N - 1)) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	dfs();
	if (N % 2==0) {
		for (int v : range(N)) {
			if (sz[v] == N / 2) {
				cout << fact[N / 2] * fact[N / 2] % mod << endl;
				return;
			}
		}
	}
	for (int v : range(N)) {
		bool isCentroid = true;
		for (auto cnt : branch[v])isCentroid &= (cnt <= N / 2);
		if (isCentroid) {
			cout << f(v) << endl;
			return;
		}
	}

}
int main() {
	while (cin >> N) {
		solve();
	}
	return 0;
}
