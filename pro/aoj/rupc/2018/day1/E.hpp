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

int x[1123456];
int y[1123456];
LL d[1123456];
int E=0;
typedef vector<int> V;
typedef vector<V> VV;
constexpr LL INF = 1e18;
int main() {
	int N, M;
	cin >> N >> M;
	int s, t;
	cin >> s >> t;
	s--;
	t--;
	VV g(N);
	for (int i : range(M)) {
		int a, b, c, cost;
		cin >> a >> b >> c >> cost;
		a--;
		b--;
		c--;
		x[E] = a; y[E] = b; d[E] = cost;
		g[a].push_back(E); g[b].push_back(E); E++;
		x[E] = b; y[E] = c; d[E] = cost;
		g[b].push_back(E); g[c].push_back(E); E++;
		x[E] = c; y[E] = a; d[E] = cost;
		g[c].push_back(E); g[a].push_back(E); E++;
	}
	vector<LL> p(N, INF);
	p[s] = 0;
	priority_queue<pair<LL, int>> que;
	que.push({ 0ll,s });
	while (que.size()) {
		int v; LL q;
		tie(q, v) = que.top(); q = -q; que.pop();
		if (p[v] < q)continue;
		for (int e : g[v]) {
			int u = v ^ x[e] ^ y[e];
			LL nq = q + d[e];
			if (chmin(p[u], nq)) {
				que.push({ -nq,u });
			}
		}
	}
	cout << p[t] << endl;
	return 0;
}
