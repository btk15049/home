#ifndef VS
#include <bits/stdc++.h>
using namespace std;
#endif
typedef long long LL;

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

    void dfs(int v, Tree &g) {
        for (int u : g[v]) {
            depth[u] = depth[v] + 1;
            p[u] = v;
            dfs(u, g);
        }
    }

    //lcaÇÃèÄîı
    void build(Tree &g, int root = 0) {
        int n = g.size();
        for (int i = 0; i < n; i++) {
            pp[0][i] = -1;
        }
        depth[root] = 0;
        dfs(root, g);
        for (int k = 0, f = 1; f; k++) {
            f = 0;
            for(int i = 0; i < n; i++) {
                if (pp[k][i]<0)pp[k + 1][i] = -1;
                else {
                    pp[k + 1][i] = pp[k][pp[k][i]];
                    f = 1;
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
    inline int dist(int a, int b) {
        int c = lca(a, b);
        return depth[a] + depth[b] - 2 * depth[c];
    }
    inline int lca(int a, int b, int c) {
        int d = lca(a, b);
        int e = lca(b, c);
        int f = lca(c, a);
        int dd = dist(d, a) + dist(d, b) + dist(d, c);
        int ee = dist(e, a) + dist(e, b) + dist(e, c);
        int ff = dist(f, a) + dist(f, b) + dist(f, c);
        vector<pair<int, int>> v = { {dd,d},{ee,e},{ff,f} };
        return min_element(v.begin(),v.end())->second;
    }
}
