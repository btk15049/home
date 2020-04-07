// http://codeforces.com/contest/1163/problem/F
/*<head>*/
// #include "GraphUtil.hpp"
/*</head>*/

/*<body>*/
/* #region header */
/**
 * @file Template.hpp
 * @brief 競技プログラミング用テンプレート
 * @author btk15049
 * @date 2019/05/02
 */
#include <bits/stdc++.h>
using namespace std;

/* #region macro */
#ifdef BTK
#    define DEBUG if (1)
#    define CIN_ONLY if (0)
#else
#    define DEBUG if (0)
#    define CIN_ONLY if (1)
#endif
/** @def
 * ALLマクロ
 */
#define ALL(v) (v).begin(), (v).end()

/** @def
 * 再帰ラムダをするためのマクロ
 */
#define REC(ret, ...) std::function<ret(__VA_ARGS__)>
/* #endregion */

namespace _Template_ {
    /**
     * @brief cin高速化処理を行うための構造体
     * @details CIN_ONLYマクロで動作が変わる
     */
    struct cww {
        cww() {
            CIN_ONLY {
                ios::sync_with_stdio(false);
                cin.tie(0);
            }
        }
    } star;
    /**
     * @brief change min
     * @tparam T 型
     * @param l 参照
     * @param r 非参照
     * @return 更新があればtrue
     */
    template <typename T>
    inline bool chmin(T& l, T r) {
        bool a = l > r;
        if (a) l = r;
        return a;
    }
    /**
     * @brief chminのmax版
     * @see chmin
     */
    template <typename T>
    inline bool chmax(T& l, T r) {
        bool a = l < r;
        if (a) l = r;
        return a;
    }
    /**
     * @brief
     * vectorに直接cin流すためのやつ
     * @tparam T
     * @param is
     * @param v
     * @return istream&
     */
    template <typename T>
    istream& operator>>(istream& is, vector<T>& v) {
        for (auto& it : v) is >> it;
        return is;
    }
    /**
     * @brief
     * rangeを逆向きに操作したいとき用
     * @details
     * ループの範囲は[bg,ed)なので注意
     * @see range
     */
    class reverse_range {
      private:
        struct I {
            int x;
            int operator*() { return x - 1; }
            bool operator!=(I& lhs) { return x > lhs.x; }
            void operator++() { --x; }
        };
        I i, n;

      public:
        reverse_range(int n) : i({0}), n({n}) {}
        reverse_range(int i, int n) : i({i}), n({n}) {}
        I& begin() { return n; }
        I& end() { return i; }
    };
    /**
     * @brief
     * python みたいな range-based for を実現
     * @details
     * ループの範囲は[bg,ed)なので注意
     * !つけると逆向きにループが回る (reverse_range)
     * 空間計算量はO(1)
     * 使わない変数ができて警告が出がちなので，unused_varとかを使って警告消しするとよい
     */
    class range {
      private:
        struct I {
            int x;
            int operator*() { return x; }
            bool operator!=(I& lhs) { return x < lhs.x; }
            void operator++() { ++x; }
        };
        I i, n;

      public:
        range(int n) : i({0}), n({n}) {}
        range(int i, int n) : i({i}), n({n}) {}
        I& begin() { return i; }
        I& end() { return n; }
        reverse_range operator!() { return reverse_range(*i, *n); }
    };
    /**
     * @brief
     * rangeで生まれる使わない変数を消す用（警告消し）
     */
    template <typename T>
    inline T& unused_var(T& v) {
        return v;
    }
    using LL = long long;
} // namespace _Template_
using namespace _Template_;


/**
 * @file Graph.hpp
 * @brief グラフクラス
 * @author btk15049
 * @date 2019/03/11
 * @datails
 *  verify: WUPC C
 */
namespace _Graph_ {
    /**
    * @brief 辺を扱う構造体の例
    * @details
    辺に重みなどを加えたい場合は変数とかを増やして作る．
    Graphに使うために必要な要件:
    - id,a,bは必須，他のパラメータ増やすときはコンストラクタを忘れずに
    - versusは必須，基本的にコピペでOK
    */
    struct Edge {
        int id, a, b;
        /**
         * @brief Construct a new Edge object
         * @param id 辺番号
         * @param a 辺に接続する頂点番号
         * @param b 辺に接続する頂点番号
         */
        Edge(int id = 0, int a = 0, int b = 0) : id(id), a(a), b(b) {}
        /**
         * @brief 辺における，vの対になってる頂点番号を取得する
         * @param v 頂点番号
         * @return int vじゃない方の頂点番号
         */
        inline int versus(const int v) const { return a ^ b ^ v; }
    };

    /**
    * @brief 重み付き辺を扱う構造体の例
    * @details
    辺に重みなどを加えたい場合は変数とかを増やして作る．
    Graphに使うために必要な要件:
    - id,a,bは必須，他のパラメータ増やすときはコンストラクタを忘れずに
    - versusは必須，基本的にコピペでOK
    */
    template <typename COST_TYPE>
    struct WeightedEdge {
        int id, a, b;
        COST_TYPE cost;

        WeightedEdge(int id = 0, int a = 0, int b = 0, int cost = 0)
            : id(id), a(a), b(b), cost(cost) {}
        /**
         * @brief 辺における，vの対になってる頂点番号を取得する
         * @param v 頂点番号
         * @return int vじゃない方の頂点番号
         */
        inline int versus(const int v) const { return a ^ b ^ v; }
    };
    /**
     * @brief グラフクラス
     * @tparam E=Edge 新たなグラフクラス作るときは書き換える
     * @details 0-indexedで使うことしか考えてないので注意．
     */
    template <typename E = Edge>
    class Graph {
      private:
        //! 辺集合
        vector<E> edges;
        //! 隣接リスト
        vector<vector<int>> g;

      public:
        /**
         * @brief Construct a new Graph object
         * @param reserved_vertex_size 頂点数の最大値，vectorのサイズ確保用
         * @param reserved_edge_size 辺数の最大値，vectorのサイズ確保用
         */
        Graph(int reserved_vertex_size = 1, int reserved_edge_size = -1) {
            g.reserve(reserved_vertex_size);
            edges.reserve(max(reserved_vertex_size, reserved_edge_size));
        }

        /**
         * @brief グラフの頂点数を返す
         * @return int 頂点数
         */
        inline int size() { return g.size(); }

        /**
         * @brief vの次数を返す
         * @param v 頂点番号
         * @return int 次数
         */
        inline int degree(const int v) { return g[v].size(); }

        /**
         * @brief グラフ全体の辺の数を返す
         * @return int グラフ全体の辺の数
         */
        inline int degree() { return edges.size(); }

        /**
         * @brief
         * グラフの頂点数を変更する
         * @return int
         */
        inline void resize(const int n) { g.resize(n); }

        /**
         * @brief "無向"辺(a,b)を追加する．
         * @param a 頂点番号
         * @param b 頂点番号
         * @param params 重みとか，容量とか
         * @details paramsはemplace_backと同じノリで続けて足してけばOK
         */
        template <typename... Ts>
        inline void add_edge(int a, int b, Ts&&... params) {
            const int id = edges.size();
            if ((int)g.size() <= max(a, b)) {
                g.resize(max(a, b) + 1);
            }
            g[a].emplace_back(id);
            g[b].emplace_back(id);
            edges.emplace_back(id, a, b, forward<Ts>(params)...);
        }

        /**
         * @brief "無向"辺Eを追加する．
         * @details paramsはemplace_backと同じノリで続けて足してけばOK
         */


        /**
         * @brief 辺を追加 idは自動付与
         * @param e
         */
        inline void add_edge(E e) {
            e.id = edges.size();
            if ((int)g.size() <= max(e.a, e.b)) {
                g.resize(max(e.a, e.b) + 1);
            }
            g[e.a].emplace_back(e.id);
            g[e.b].emplace_back(e.id);
            edges.emplace_back(e);
        }

        /**
         * @brief "有向"辺(a,b)を追加する．
         * @param a 頂点番号
         * @param b 頂点番号
         * @param params 重みとか，容量とか
         * @details paramsはemplace_backと同じノリで続けて足してけばOK
         */
        template <typename... Ts>
        inline void add_arc(int a, int b, Ts&&... params) {
            const int id = edges.size();
            if ((int)g.size() <= max(a, b)) {
                g.resize(max(a, b) + 1);
            }
            g[a].emplace_back(id);
            edges.emplace_back(id, a, b, forward<Ts>(params)...);
        }

        /**
         * @brief 辺を追加 idは自動付与
         * @param e
         */
        inline void add_arc(E e) {
            e.id = edges.size();
            if ((int)g.size() <= max(e.a, e.b)) {
                g.resize(max(e.a, e.b) + 1);
            }
            g[e.a].emplace_back(e.id);
            edges.emplace_back(e);
        }

        /**
         * @brief vの隣接頂点を返す
         * @param v int
         * @return vector<int>
         */
        inline vector<int> Ns(const int v) {
            vector<int> ns(g[v].size());
            for (int i = 0; i < degree(v); i++) {
                ns[i] = edges[g[v][i]].versus(v);
            }
            return ns;
        }

        /**
         * @brief vに隣接する辺番号の集合を返す
         * @param v int
         * @return vector<int>
         */
        inline const vector<int>& operator[](const int v) { return g[v]; }

        /**
         * @brief 辺番号から辺の参照を取得する
         * @param edge_id
         * @return E&
         */
        inline E& i2e(const int edge_id) { return edges[edge_id]; }
    };
} // namespace _Graph_
using namespace _Graph_;

/**
 * @file GraphUtil.hpp
 * @author btk
 * @brief Graphクラスを使ったライブラリ(dijkstraなど)を管理
 * @date 2019-05-26
 * @copyright Copyright (c) 2019
 */


namespace _GraphUtil_ {

    /**
     * @brief
     * 通常のダイクストラ
     * @tparam E 重み付き辺構造体　.costをメンバにもつ必要あり
     * @tparam COST_TYPE コストの型
     * @param g グラフ
     * @param s 始点
     * @return vector<int>
     */
    template <typename E, typename COST_TYPE>
    vector<COST_TYPE> dijkstra(Graph<E>& g, COST_TYPE inf, const int s = 0) {
        //! TODO interval heapを使う
        priority_queue<pair<COST_TYPE, int>> que;
        vector<COST_TYPE> d(g.size(), inf);

        // init
        d[s] = 0;
        que.push(make_pair((COST_TYPE)0, s));

        while (!que.empty()) {
            const int v       = que.top().second;
            const COST_TYPE c = -que.top().first;
            que.pop();
            if (d[v] < c) continue;
            for (const int eid : g[v]) {
                E& e        = g.i2e(eid);
                const int u = e.versus(v);
                if (chmin(d[u], c + e.cost)) {
                    que.push(make_pair(-(c + e.cost), u));
                }
            }
        }
        return d;
    }
} // namespace _GraphUtil_
using namespace _GraphUtil_;

/* #endregion */
/*</body>*/

constexpr LL inf = 1e17;
constexpr int sz = 212345 * 2;
int bv[sz];
int ev[sz];
int bg[sz];
int ed[sz];
LL ct[sz];
int edge_set[sz];
int vertex_set[sz];

vector<int> B[sz];
vector<int> E[sz];
int N, M, Q;

Graph<WeightedEdge<LL>> g(sz, sz);

vector<int> shortest_path(vector<LL> d) {
    vector<int> path;
    int v = N - 1;
    while (v != 0) {
        for (int eid : g[v]) {
            auto edge   = g.i2e(eid);
            const int u = edge.versus(v);
            if (d[u] + edge.cost == d[v]) {
                path.push_back(eid);
                edge_set[eid] = 1;
                vertex_set[v] = 1;
                vertex_set[u] = 1;
                v             = u;
                break;
            }
        }
    }
    reverse(ALL(path));
    return path;
}

auto assign_ps(vector<LL> d, int* ps) {
    vector<int> order(N);
    iota(ALL(order), 0);
    sort(ALL(order), [&](int l, int r) { return d[l] < d[r]; });
    for (const int v : order) {
        if (vertex_set[v]) {
            ps[v] = v;
        }
        else {
            for (int eid : g[v]) {
                auto e      = g.i2e(eid);
                const int u = e.versus(v);
                if (d[u] + e.cost == d[v]) {
                    ps[v] = ps[u];
                    break;
                }
            }
        }
        // cerr << v << ":" << d[v] << " " << ps[v] << endl;
    }
}

int qe[sz];
LL qc[sz];
LL ret[sz];
int main() {
    cin >> N >> M >> Q;
    for (int i : range(M)) {
        unused_var(i);
        int a, b;
        LL w;
        cin >> a >> b >> w;
        a--;
        b--;
        g.add_edge(a, b, w);
    }
    auto d    = dijkstra(g, inf, 0);
    auto r    = dijkstra(g, inf, N - 1);
    auto path = shortest_path(d);
    assign_ps(d, bv);
    assign_ps(r, ev);
    for (int i : range(M)) {
        if (edge_set[i]) continue;
        auto e = g.i2e(i);
        int v  = e.a;
        int u  = e.b;
        if (d[bv[v]] >= d[ev[u]]) swap(v, u);
        bg[i] = bv[v];
        ed[i] = ev[u];
        /*
        cerr << i << " ";
        cerr << bg[i] << " ";
        cerr << ed[i] << " ";
        cerr << endl;
        */
        if (d[bg[i]] < d[ed[i]]) {
            ct[i] = d[v] + r[u] + e.cost;
            B[bg[i]].push_back(i);
            E[ed[i]].push_back(i);
        }
    }
    vector<int> qo;
    for (int i : range(Q)) {
        cin >> qe[i] >> qc[i];
        qe[i]--;
        if (edge_set[qe[i]]) {
            qo.push_back(i);
        }
        else {
            auto e          = g.i2e(qe[i]);
            auto candidates = {d.back(), d[e.a] + qc[i] + r[e.b],
                               d[e.b] + qc[i] + r[e.a]};
            ret[i]          = *min_element(ALL(candidates));
        }
    }
    sort(ALL(qo), [&](int l, int r) {
        auto el = g.i2e(qe[l]);
        auto er = g.i2e(qe[r]);
        LL dl   = min(d[el.a], d[el.b]);
        LL dr   = min(d[er.a], d[er.b]);
        return dl < dr;
    });
    int itr = 0;
    set<pair<LL, int>> S;
    auto update = [&](int v) {
        for (int ej : B[v]) {
            S.insert({ct[ej], ej});
            /*
            cerr << "ins:";
            cerr << " ,eid:" << ej;
            cerr << " ,bg:" << bg[ej];
            cerr << " ,ed:" << ed[ej];
            cerr << " ,ct:" << ct[ej];
            cerr << endl;
            */
        }
        for (int ej : E[v]) {
            S.erase({ct[ej], ej});
            /*
            cerr << "del:";
            cerr << " ,eid:" << ej;
            cerr << " ,bg:" << bg[ej];
            cerr << " ,ed:" << ed[ej];
            cerr << " ,ct:" << ct[ej];
            cerr << endl;
            */
        }
    };
    update(0);
    for (int qi : qo) {
        int ei = qe[qi];
        while (path[itr] != ei) {
            auto e = g.i2e(path[itr]);
            int v  = d[e.a] < d[e.b] ? e.a : e.b;
            int u  = e.versus(v);
            update(u);
            itr++;
        }
        {
            auto e  = g.i2e(ei);
            int v   = d[e.a] < d[e.b] ? e.a : e.b;
            int u   = e.versus(v);
            ret[qi] = min((S.size() == 0u ? inf : S.begin()->first),
                          d[v] + qc[qi] + r[u]);
        }
    }

    for (int i : range(Q)) {
        cout << ret[i] << "\n";
    }
    return 0;
}