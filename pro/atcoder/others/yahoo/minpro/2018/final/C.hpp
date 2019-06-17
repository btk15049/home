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

constexpr int SIZE = 112345;
int a[SIZE];
int b[SIZE];

typedef vector<int> V;
typedef vector<V> VV;
namespace CD {
	constexpr int BLACK = 1;
	constexpr int WHITE = 0;
	constexpr int RED = 2;
	int used[SIZE];
	struct centroid {
		int size;
		int par;
		V   cld;
		V   vex;
	}node[SIZE];
	stack<int> st;
	int dfs(int v, int all, VV &g, int &tar, int& ans) {
		int cld_size = 1;
		int cld_max = 0;
		used[v] = WHITE;
		for (auto &e : g[v]) {
			int u = v^a[e] ^ b[e];
			if (used[u] != RED)continue;
			int cld = dfs(u, all, g, tar, ans);
			chmax(cld_max, cld);
			cld_size += cld;
		}
		chmax(cld_max, all - cld_size);
		if (cld_max<ans) {
			tar = v;
			ans = cld_max;
		}
		return cld_size;
	}
	int construct(int v, int p, VV&g) {
		V vex;
		st.push(v);
		vex.push_back(v);
		used[v] = RED;
		while (st.size()) {
			int s = st.top(); st.pop();
			for (auto &e : g[s]) {
				int t = s ^ a[e] ^ b[e];
				if (used[t]!=WHITE)continue;
				st.push(t);
				used[t] = RED;
				vex.push_back(t);
			}
		}

		int lim = vex.size() + 1;
		dfs(v, vex.size(), g, v, lim);
		used[v] = BLACK;

		node[v].size = vex.size();
		node[v].par = p;
		node[v].vex = vex;

		for (auto &e : g[v]) {
			int u = v^a[e] ^ b[e];
			if (used[u])continue;
			node[v].cld.push_back(construct(u, v, g));
		}
		return v;
	}
	int construct(VV &g, int root = 0) {
		int N = g.size();
		fill(used, used + N, WHITE);
		return construct(0, -1, g);
	}
}
VV dist_to_par;
VV dist_cnt;
vector<VV> dist_sub_cnt;
VV group;

/*
	call from pre_build
	set {dist_to_par[v][d],group[v][d]}
	 //note that d = depth of centroid decomposition
*/
void dfs(int v,int depth,int id, VV &g, V& sub) {
	using namespace CD;
	group[v].push_back(id);
	used[v] = BLACK;
	dist_to_par[v].push_back(depth);
	if (sub.size() <= depth)sub.push_back(1);
	else sub[depth]++;
	for (int e : g[v]) {
		int u = v^a[e] ^ b[e];
		if (used[u] != WHITE)continue;
		dfs(u, depth + 1, id, g, sub);
	}
}

/*
	before, CD::used[u in node[v].vex] must be BLACK
*/
void pre_build(int v, VV &g,bool init = true){
	using namespace CD;
	if (init) {
		dist_cnt = VV(node[v].size, V(1, 1));
		dist_sub_cnt = vector<VV>(node[v].size);
		dist_to_par=VV(node[v].size);
		group=VV(node[v].size);
	}
	for (int u : node[v].vex) {
		used[u] = WHITE;
	}
	group[v].push_back(-1);
	used[v] = BLACK;
	dist_to_par[v].push_back(0);
	{
		int k = 0;
		used[v] = BLACK;
		for (int e : g[v]) {
			int u = v^a[e] ^ b[e];
			if (used[u] != WHITE)continue;
			V sub(1, 0);
			dfs(u,1,k,g,sub);
			k++;
			for (int i : range(1,sub.size())) {
				if (dist_cnt[v].size() <= i) {
					dist_cnt[v].push_back(sub[i]);
				}
				else {
					dist_cnt[v][i] += sub[i];
				}
			}
			dist_sub_cnt[v].push_back(sub);
		}
	}
	for (int u : node[v].cld)pre_build(u, g, false);
}
int query(const int v, const int d) {
	using namespace CD;
	int depth = dist_to_par[v].size() - 1;
	int c = v;
	int ret = 0;
	while (depth>=0) {
		const int dist = d - dist_to_par[v][depth];
		if (dist>=0) {
			if (dist < dist_cnt[c].size())
				ret += dist_cnt[c][dist];
			if (v!=c) {
				if (dist < dist_sub_cnt[c][group[v][depth]].size())
					ret -= dist_sub_cnt[c][group[v][depth]][dist];
			}
		}
		depth--;
		c = node[c].par;
	}
	return ret;
}
int main() {
	int N, Q;
	cin >> N >> Q;
	VV g(N);
	for (int i : range(N - 1)) {
		cin >> a[i] >> b[i];
		a[i]--; b[i]--;
		g[a[i]].push_back(i);
		g[b[i]].push_back(i);
	}
	int centroid = CD::construct(g);
	pre_build(centroid, g);
	for (int i : range(Q)) {
		int v, d;
		cin >> v >> d;
		v--;
		cout << query(v,d) << endl;
	}
	return 0;
}
