//
#define CIN_ONLY
#define DECIMAL_DIGITS 10
#define STATIC_MOD 1e9 + 7

#ifdef BTK
/*<head>*/
#    include "Template.hpp"
/*</head>*/
#else
/*<body>*/
/*</body>*/
#endif

#define pb push_back


namespace _DSU {
    constexpr int BUF = 212345 * 2;
    int ptr           = 0;
    int mem[BUF];
    LL memo[212345];
    int *get(int size) {
        ptr += size;
        return mem + ptr - size;
    }
    void reset() { ptr = 0; }
} // namespace _DSU

LL in[112345];

class UF {
  private:
    int *par, *rank;
    LL *sz;

  public:
    int find(int x) {
        if (par[x] == x) {
            return x;
        }
        else {
            sz[par[x]] += sz[x];
            sz[x]         = 0;
            return par[x] = find(par[x]);
        }
    }
    UF(int n)
        : par(_DSU::get(n + 10)), rank(_DSU::get(n + 10)), sz(_DSU::memo) {
        for (int i = 0; i < n; i++) {
            par[i] = i, rank[i] = 0, sz[i] = in[i];
        }
    }
    bool unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        if (rank[x] < rank[y]) swap(x, y);
        par[y] = x;
        if (rank[x] == rank[y]) rank[x]++;
        return true;
    }
    bool same(int x, int y) { return find(x) == find(y); }
};


constexpr int SIZE = 112345;
int x[SIZE];
int y[SIZE];
int z[SIZE];
typedef vector<int> V;
typedef vector<V> VV;
namespace CD {
    enum VER_TYPE {
        RED   = 1, // もう重心として選ばれた頂点
        WHITE = 0,
        BLACK = -1,
    };
    struct centroid {
        int size;
        int par;
        V cld;
        V vex;
    } node[SIZE];
    stack<int> st;
    // 最初，集合内の頂点は全てBLACK
    // 最終的に，tarがcentroidになる
    int search_centroid(int v, int all, VV &g, int *a, int *b, int &tar,
                        int &ans, int *used) {
        int cld_size = 1;
        int cld_max  = 0;
        used[v]      = WHITE;
        for (auto &e : g[v]) {
            int u = v ^ a[e] ^ b[e];
            if (used[u] != BLACK) continue;
            int cld = search_centroid(u, all, g, a, b, tar, ans, used);
            chmax(cld_max, cld);
            cld_size += cld;
        }
        chmax(cld_max, all - cld_size);
        if (cld_max < ans) {
            tar = v;
            ans = cld_max;
        }
        return cld_size;
    }
    vector<int> root[112345];
    vector<int> dep[112345];
    void dfs(int v, int p, VV &g, int *a, int *b, int *used, int r) {
        root[v].push_back(r);

        for (auto &e : g[v]) {
            int u = v ^ a[e] ^ b[e];
            if (used[u] == RED) continue;
            if (u == p) continue;
            dep[u].push_back(dep[v].back() + 1);
            dfs(u, v, g, a, b, used, r);
        }
    }
    int construct(int v, VV &g, int *a, int *b, int *used, int p = -1) {
        st.push(v);
        V vex;
        vex.pb(v);
        // WHITEの連結成分をvexに全て入れ，全てBLACKに変える
        used[v] = BLACK;
        while (st.size()) {
            int s = st.top();
            st.pop();
            for (auto &e : g[s]) {
                int t = s ^ a[e] ^ b[e];
                if (used[t] != WHITE) continue;
                st.push(t);
                used[t] = BLACK;
                vex.pb(t);
            }
        }

        int lim = vex.size() + 1;
        // BLACK -> WHITE
        // vが重心に変わる
        search_centroid(v, vex.size(), g, a, b, v, lim, used);

        used[v] = RED;

        node[v].size = vex.size();
        node[v].par  = p;
        node[v].vex  = vex;

        dep[v].push_back(0);
        // dfs(v);

        for (auto &e : g[v]) {
            int u = v ^ a[e] ^ b[e];
            if (used[u]) continue;
            node[v].cld.pb(construct(u, g, a, b, used, v));
        }
        return v;
    }
    int decomposition(VV &g, int bg = 0) {
        return construct(bg, g, x, y, z, -1);
    }

} // namespace CD

int main() {
    /* write here */
    return 0;
}