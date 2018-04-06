#include <bits/stdc++.h>
using namespace std;

//The number of outdegree of vertex in graph "in" is 1
constexpr int USED = -2;
constexpr int BRANCH = -1;
constexpr int UNCYCLE = 11234567;
struct SunnyGraph {
	using V = vector<int>;
	using Graph = vector<V>;
	int size;
	Graph g; // g[i]    : vertexes of i th component's loop
	Graph in;// in[v]   : reverse edges(not in loop) toward v 
	V K;     // K[v]    : id of connected component contains v
	V root;  // root[v] : root vertex of v (same connected components)
	int dfs1(int v, V& out, int id, V &loop) {
		auto &sign = K;
		sign[v] = -2;
		int u = out[v];
		if (sign[u] >= 0) {
			sign[v] = UNCYCLE;
			return BRANCH;
		}
		if (sign[u] == USED || (u = dfs1(u, out, id, loop)) >= 0) {
			sign[v] = id;
			root[v] = v;
			loop.push_back(v);
			if (v == u)return BRANCH;
			else return u;
		}
		K[v] = UNCYCLE;
		return BRANCH;
	}
	void dfs2(int v) {
		for (auto &u : in[v]) {
			K[u] = K[v];
			root[u] = root[v];
			dfs2(u);
		}
	}
	SunnyGraph(V out) {
		size = out.size();
		in.resize(size);
		K.resize(size, -1);
		root.resize(size);
		int id = 0;
		for (int v = 0; v < size; v++){
			V L;
			if (K[v] == -1)dfs1(v, out, id, L);
			if (L.size()) {
				g.push_back(L);
				id++;
			}
		}
		for (int v = 0; v < size; v++)
			if (K[v] == UNCYCLE)in[out[v]].push_back(v);
		for (auto &s : g)for (auto &v : s)dfs2(v);
	}
};
