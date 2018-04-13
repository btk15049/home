#include<bits/stdc++.h>
using namespace std;

typedef vector<int> V;
typedef vector<V> Graph;
constexpr int MAX_N = 112345;
constexpr int MAX_M = 112345;

struct Forest {
	Graph g;
    vector<int> roots;
	void dfs(int v, int p, Graph &in, vector<int>& used) {
        used[v] = 1;
		for (auto &u : in[v]) {
			if (u == p)continue;
			g[v].push_back(u);
			dfs(u, v, in, used);
		}
	}
	Forest(Graph& in) :g(in.size()) {
        vector<int> used(in.size(),0);
        for(int i = 0; i < (int)in.size(); i++){
		    if(used[i])continue;
            dfs(i, i, in, used);
            roots.push_back(i);
        }
	}
	V& operator[](const int i) {
		return g[i];
	}
	int size() {
		return (int)g.size();
	}
};

/*
    order[v] : order of v in toporogical sort
    low[v]   : low link of v
    group[e] : id of group where e belongs
    is_articulation_point: 
*/
namespace TwoVertex {
	int order[MAX_N];
    bool used[MAX_N];

	int low[MAX_N];
	bool is_articulation_point[MAX_N];
	int group[MAX_M];

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
	Forest build(int *in_a, int *in_b, int N, int M) {
		g = Graph(N);
		a = in_a;
		b = in_b;
		init(N, M);
		for (int i =0; i < M; i++) {
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
		return Forest(g);
	}
}