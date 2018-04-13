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
constexpr int MAX_N = 112345;
constexpr int MAX_M = 112345;

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

namespace TwoVertex {
	int order[MAX_N];
	int group[MAX_M];
	int low[MAX_N];
	bool used[MAX_N];

	bool is_articulation_point[MAX_M];
	int *a, *b;
	Graph g;

	void init(int n, int m) {
		for (int i = 0; i < n; i++) {
			order[i] = -1;
			used[i] = false;
		}
		for (int i = 0; i < m; i++) {
			group[i] = -1;
		}
	}

	void low_link(int v, int pe, int id) {
		low[v] = order[v] = id++;
		int childs = 0;
		int clow_max = -1;
		for (int e : g[v]) {
			if (e == pe)continue;
			int u = a[e] ^ b[e] ^ v;
			if (order[u] == -1) {
				// u is a child of v
				low_link(u, e, id);
				low[v] = low[v] > low[u] ? low[u] : low[v];

				//for check articulation point
				childs++;
				clow_max = clow_max < low[u] ? low[u] : clow_max;
			}
			else {
				low[v] = low[v] > order[u] ? order[u] : low[v];
			}

			// check v is articulation point
			if (pe == -1) { // v is root
				is_articulation_point[v] = (childs >= 2);
			}
			else {
				is_articulation_point[v] = (order[v] <= clow_max);
			}
		}
	}
	//dfs_wrapper
	void low_link(int n) {
		int id = 0;
		for (int i = 0; i < n; i++) {
			if (order[i] == -1)low_link(i, -1, id);
		}
	}

	void grouping(int v, int k, int&id, vector<pair<int, int>>& edges, bool is_root = true) {
		used[v] = true;
		if (is_root)id--;
		else if (is_articulation_point[v])edges.push_back({ v, k });
		for (int e : g[v]) {
			int u = v ^ a[e] ^ b[e];
			if (used[u]==false) {
				if (is_root || low[u] >= order[v]) {
					group[e] = ++id - 1;
					edges.push_back({ v,group[e] });
				}
				else {
					group[e] = k;
				}
				grouping(u, group[e], id, edges, false);
			}
			else if (group[e] == -1) { // e is a backward edge
				group[e] = k;
			}
		}
	}

	pair<int,vector<pair<int,int>>> grouping(int n) {
		int id = 0;
		vector<pair<int, int>> edges;
		for (int i = 0; i < n; i++) {
			if (used[i] == false)
				grouping(i, ++id - 1, id, edges);
		}
		return { id + n ,edges };
	}

	// return : block cut tree
	Tree build(int *in_a, int *in_b, int N, int M) {
		g = Graph(N);
		a = in_a;
		b = in_b;
		init(N, M);
		for (int i : range(M)) {
			g[a[i]].push_back(i);
			g[b[i]].push_back(i);
		}
		low_link(N);
		int size;
		vector<pair<int, int>> edges;
		tie(size,edges) = grouping(N);
		
		g = Graph(size);
		for (pair<int, int> e : edges) {
			e.second += N;
			g[e.first].push_back(e.second);
			g[e.second].push_back(e.first);
		}
		return Tree(g);
	}
}
namespace TwoEdge {
	int depth[MAX_N];
	int group[MAX_N];
	int imos[MAX_N];
	bool isbridge[MAX_M];
	int *a, *b;
	Graph g;
	void find_bridge(int v, int pe) {
		for (int e : g[v]) {
			if (e == pe)continue;
			int u = a[e] ^ b[e] ^ v;
			if (depth[u] == -1) {
				depth[u] = depth[v] + 1;
				isbridge[e] = true;
				find_bridge(u, e);
				imos[v] += imos[u];
			}
			else if (depth[v] > depth[u]) {
				imos[u]--;
				imos[v]++;
			}
		}
		if (imos[v] > 0)isbridge[pe] = false;
	}

	void grouping(int v, int k, int&id) {
		group[v] = k;
		for (int e : g[v]) {
			int u = v ^ a[e] ^ b[e];
			if (group[u] == -1) {
				if (isbridge[e]) {
					grouping(u, ++id, id);
				}
				else {
					grouping(u, k, id);
				}
			}
		}
	}

	Tree build(int *in_a, int *in_b, int N, int M) {
		g = Graph(N);
		a = in_a;
		b = in_b;
		for (int i : range(M)) {
			g[a[i]].push_back(i);
			g[b[i]].push_back(i);
			isbridge[i] = false;
		}
		for (int i : range(N)) {
			group[i] = -1;
			depth[i] = -1;
			imos[i] = 0;
		}
		depth[0] = 0;
		find_bridge(0, -1);
		int id = 0;
		grouping(0, id, id);
		g = Graph(id + 1);
		for (int i : range(M)) {
			if (group[a[i]] != group[b[i]]) {
				g[group[a[i]]].push_back(group[b[i]]);
				g[group[b[i]]].push_back(group[a[i]]);
			}
		}
		return Tree(g);
	}
}



int a[112345];
int b[112345];
int main() {
	int n, m;
	cin >> n >> m;
	for (int i : range(m)) {
		cin >> a[i] >> b[i];
		a[i]--; b[i]--;
	}
	vector<int> es(m,0);
	vector<set<int>> vs(m);
	TwoVertex::build(a, b, n, m);
	for (int e : range(m)) {
		int g = TwoVertex::group[e];
		es[g]++;
		vs[g].insert(a[e]);
		vs[g].insert(b[e]);
	}
	vector<int> ret;
	for (int e : range(m)) {
		int g = TwoVertex::group[e];
		if (es[g]>0&&es[g] == vs[g].size())
			ret.push_back(e + 1);
	}
	cout << ret.size()<<endl;
	for (int i : range(ret.size()))cout << " " + (!i) << ret[i];
	cout << endl;

	return 0;
}
