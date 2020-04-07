#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <vector>

#define FOR(i, bg, ed) for (int i = bg; i < ed; i++)
#define REP(i, n) FOR(i, 0, n)

template <typename G>
struct LowLink {
    const G &g;
    vector<int> used, ord, low;
    vector<int> articulation;
    vector<pair<int, int>> bridge;

    LowLink(const G &g) : g(g) {}

    int dfs(int idx, int k, int par) {
        used[idx]            = true;
        ord[idx]             = k++;
        low[idx]             = ord[idx];
        bool is_articulation = false;
        int cnt              = 0;
        for (auto &to : g[idx]) {
            if (!used[to]) {
                ++cnt;
                k        = dfs(to, k, idx);
                low[idx] = min(low[idx], low[to]);
                is_articulation |= ~par && low[to] >= ord[idx];
                if (ord[idx] < low[to])
                    bridge.emplace_back(minmax(idx, (int)to));
            }
            else if (to != par) {
                low[idx] = min(low[idx], ord[to]);
            }
        }
        is_articulation |= par == -1 && cnt > 1;
        if (is_articulation) articulation.push_back(idx);
        return k;
    }

    virtual void build() {
        used.assign(g.size(), 0);
        ord.assign(g.size(), 0);
        low.assign(g.size(), 0);
        int k = 0;
        for (int i = 0; i < g.size(); i++) {
            if (!used[i]) k = dfs(i, k, -1);
        }
    }
};


using namespace std;
int N, M;
using V  = vector<int>;
using VV = vector<V>;
VV g;
int main() {
    cin >> N >> M;
    g.resize(N);
    REP(i, M) {
        int K;
        cin >> K;
        int v;
        cin >> v;
        v--;
        REP(j, K - 1) {
            int u;
            cin >> u;
            u--;
            g[v].push_back(u);
            g[u].push_back(v);
        }
    }
}