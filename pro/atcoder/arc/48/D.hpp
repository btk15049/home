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
typedef vector<V> Graph;

struct Tree {
	Graph g;
	void dfs(int v, int p, Graph &in) {
		for (auto &u : in[v]) {
			if (u == p)continue;
			g[v].push_back(u);
			dfs(u, v, in);
		}
	}
	Tree(Graph& in) :g(in.size()) {
		dfs(0, 0, in);
	}
	V& operator[](const int i) {
		return g[i];
	}
	int size() {
		return (int)g.size();
	}
};

constexpr int INF = 1e7;
int nearest[112345];

namespace LCA {
	/*
	use doubling
	- build : O(nlogn)
	- query : O(logn)
	*/
	constexpr int BUF = 112345;
	constexpr int LOG = 20; // LOG >= log(BUF)
	int pp[LOG][BUF];
	int *p = pp[0];
	int depth[BUF];
	int dp[3][LOG][112345];

	void dfs(int v, Tree &g) {
		for (int u : g[v]) {
			depth[u] = depth[v] + 1;
			p[u] = v;
			dfs(u, g);
		}
	}
	constexpr int D = 1;
	constexpr int U = 2;
	void build(Tree &g, int root = 0) {
		int n = g.size();
		for (int i = 0; i < n; i++) {
			pp[0][i] = -1;
		}
		depth[root] = 0;
		dfs(root, g);
		for (int i : range(n)) {
			if (p[i] != -1) {
				dp[0][0][i] = 2;
				dp[D][0][i] = min(
					nearest[p[i]] * 3 + 1,
					nearest[i] * 3 + 2
				);
				dp[U][0][i] = min(
					nearest[i] * 3 + 1,
					nearest[p[i]] * 3 + 2
				);
			}
		}
		for (int k = 0, f = 1; f; k++) {
			f = 0;
			for (int i = 0; i < n; i++) {
				if (pp[k][i]<0)pp[k + 1][i] = -1;
				else {
					pp[k + 1][i] = pp[k][pp[k][i]];
					f = 1;
					int nxt = pp[k][i];
					dp[0][k + 1][i] = dp[0][k][i] + dp[0][k][nxt];
					dp[D][k + 1][i] = min(
						dp[0][k][nxt] + dp[D][k][i],
						dp[D][k][nxt] + dp[0][k][i] / 2
						);
					dp[U][k + 1][i] = min(
						dp[0][k][nxt]/2 + dp[U][k][i],
						dp[U][k][nxt] + dp[0][k][i]
					);
				}
			}
		}
	}

	inline int lca(int u, int v) {
		if (depth[u] > depth[v])swap(u, v);
		for (int k = 0, d; (d = depth[v] - depth[u]); k++) {
			if ((d >> k) & 1) {
				v = pp[k][v];
			}
		}
		if (u == v)return v;
		for (int k = LOG - 1; k >= 0; k--) {
			if (pp[k][u] != pp[k][v]) {
				u = pp[k][u];
				v = pp[k][v];
			}
		}
		return pp[0][u];
	}
	struct latte {
		int vtx;
		int up;
		int down;
		int normal;
	};
	latte update(latte v, int k) {
		return latte{
			pp[k][v.vtx],
			min(
				dp[0][k][v.vtx] / 2 + v.up,
				dp[U][k][v.vtx] + v.normal
			),
			min(
				dp[0][k][v.vtx] + v.down,
				dp[D][k][v.vtx] + v.normal / 2
			),
			dp[0][k][v.vtx] + v.normal
		};
	}
	int mg(latte u, latte v) {
		return min(
			{
				u.normal + v.normal,
				u.up + v.normal/2,
				u.normal+v.down
			}
		);
	}
	inline int malta(int _u, int _v) {
		latte u{ _u, INF, INF, 0 };
		latte v{ _v, INF, INF, 0 };
		bool f = false;
		if (depth[u.vtx] > depth[v.vtx]) {
			swap(u, v);
			f = true;
		}
		for (int k = 0, d; (d = depth[v.vtx] - depth[u.vtx]); k++) {
			if ((d >> k) & 1) {
				//v = pp[k][v];	
				v = update(v,k);
			}
		}
		if (u.vtx == v.vtx) {
			if (f)swap(u, v);
			return mg(u, v);
			//return v;
			//TODO
		}
		for (int k = LOG - 1; k >= 0; k--) {
			if (pp[k][u.vtx] != pp[k][v.vtx]) {
				u = update(u, k);
				v = update(v, k);
			}
		}
		u = update(u, 0);
		v = update(v, 0);
		if (f)swap(u, v);
		return mg(u, v);
	}
}

void dfs1(int v, Tree& t) {
	for (int u : t[v]) {
		dfs1(u, t);
		chmin(nearest[v], nearest[u] + 1);
	}
}

void dfs2(int v, Tree& t) {
	for (int u : t[v]) {
		chmin(nearest[u], nearest[v] + 1);
		dfs2(u, t);
	}
}

int main() {
	int N, Q;
	cin >> N >> Q;
	Graph g(N);
	for (int i : range(N - 1)) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		g[a].emplace_back(b);
		g[b].emplace_back(a);
	}
	Tree t(g);
	string s;
	cin >> s;
	for (int i : range(N)) {
		if (s[i] == '0')nearest[i] = INF;
		else nearest[i] = 0;
	}
	dfs1(0, t);
	dfs2(0, t);
	LCA::build(t);
	while (Q--) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		cout << LCA::malta(a, b)<<endl;
	}
	return 0;
}
