// https://atcoder.jp/contests/agc034/tasks/agc034_e
/*<head>*/
// #include "Tree.hpp"
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
 * @file Tree.hpp
 * @brief 根付き森と根付き木
 * @author btk15049
 * @date 2019/05/07
 * @datails
 *  verify:
 */


namespace _Tree_ {
    /**
     * @brief 根付き森クラス
     * @tparam E=Edge 新たな辺構造体作るときは書き換える
     * @details 0-indexedで使うことしか考えてないので注意．
     * @see Graph
     */
    template <typename E = Edge>
    class Forest : public Graph<E> {
      private:
        using Graph<E>::add_edge;

        //! 根の集合
        vector<int> roots;

        /**
         * @brief
         * DFSで木を作る
         */
        void build_tree(Graph<E>& g, const int v, vector<bool>& used) {
            used[v] = true;
            for (int edge_id : g[v]) {
                auto e      = g.i2e(edge_id);
                const int u = e.versus(v);
                if (used[u]) continue;
                e.a = v;
                e.b = u;
                this->add_arc(e);
                build_tree(g, u, used);
            }
        }

      public:
        /**
         * @brief
         * 無向グラフから根付き森を作る
         * @see Graph::Graph()
         */
        Forest(Graph<E>& g, const int loop_begin_vtx = 0)
            : Graph<E>(g.size(), g.size() - 1) {
            this->resize(g.size());
            vector<bool> used(g.size());
            for (int v : range(loop_begin_vtx, g.size() + loop_begin_vtx)) {
                v = v % g.size();
                if (used[v] == false) {
                    build_tree(g, v, used);
                    roots.push_back(v);
                }
            }
        }

        /**
         * @brief Get the roots object
         * @return vector<int>
         */
        vector<int> get_roots() { return roots; }
    };

    template <typename E = Edge>
    class Tree : public Forest<E> {
      private:
        using Forest<E>::get_roots;
        int root;

      public:
        Tree(Graph<E>& g, const int root = 0)
            : Forest<E>(g, root), root(root) {}
        inline int get_root() { return root; }
    };
} // namespace _Tree_
using namespace _Tree_;

/* #endregion */
/*</body>*/
int N;
int X[2123];
struct node {
    int merges;
    int needs;
    int vs;
    node(int m = 0, int n = 0, int v = 0) {
        merges = m;
        needs  = n;
        vs     = v;
    };
};
constexpr int INF = 1e9;
node dfs(int v, Tree<>& t) {
    int d = t.degree(v);
    if (d == 0) {
        return node(0, X[v], X[v]);
    }
    vector<node> child;
    for (int u : t.Ns(v)) child.push_back(dfs(u, t));
    node ret;
    int needs_max    = 0;
    int needs_sum    = 0;
    int merges_sum   = 0;
    int enable_break = 0;
    int vs           = 0;
    for (int i : range(d)) {
        if (child[needs_max].needs < child[i].needs) {
            needs_max = i;
        }
        needs_sum += child[i].needs;
        merges_sum += child[i].merges;
        vs += child[i].vs;
    }
    vs += X[v];
    for (int i : range(d)) {
        if (i != needs_max) {
            enable_break += child[i].merges;
        }
    }
    needs_max = child[needs_max].needs;
    if (needs_max * 2 > needs_sum) {
        int k = (needs_max * 2 - needs_sum + 1) / 2;
        chmin(k, enable_break);
        needs_sum += k * 2;
        merges_sum -= k;
    }
    int new_needs  = 0;
    int new_merges = merges_sum;

    if (needs_max * 2 > needs_sum) {
        new_merges += needs_sum - needs_max;
        new_needs = needs_sum - (needs_sum - needs_max) * 2;
    }
    else {
        new_merges += needs_sum / 2;
        new_needs = needs_sum % 2;
    }
    return node(new_merges, new_needs + vs, vs);
}
int calc(int root, Graph<>& g) {
    Tree<> t(g, root);
    auto x = dfs(root, t);


    int sum = 0;
    for (int i : range(N)) {
        sum += X[i];
    }
    // cerr << x.merges << " " << x.needs - sum << endl;

    if (x.needs - sum == 0) {
        return x.merges;
    }
    else {
        return INF;
    }
}
int main() {
    cin >> N;
    string s;
    cin >> s;
    int sum = 0;
    for (int i : range(N)) {
        X[i] = s[i] - '0';
        sum += X[i];
    }
    if (sum == 1) {
        cout << 0 << endl;
        return 0;
    }
    Graph<> g(N, N - 1);
    for (int i : range(N - 1)) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        g.add_edge(a, b);
    }
    int ret = INF;
    for (int i : range(N)) chmin(ret, calc(i, g));
    if (ret == INF) ret = -1;
    cout << ret << endl;
    return 0;
}