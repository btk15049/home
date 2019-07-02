// https://atcoder.jp/contests/abc132/tasks/abc132_e
#ifdef BTK
/*<head>*/
#    include "Template.hpp"
#    include "graph/Graph.hpp"
#    include "graph/GraphUtil.hpp"
/*</head>*/
#else
/*<body>*/
/* #region header */
/* #region 1*/
/**
 * @file Template.hpp
 * @brief 競技プログラミング用テンプレート
 * @author btk15049
 * @date 2019/05/02
 */
#    include <bits/stdc++.h>
using namespace std;

/* #region macro */
/**
 * @def DEBUG
 * @brief デバッグ用のif文　提出時はif(0)で実行されない
 */

/**
 * @def CIN_ONLY
 * @brief デバッグ用のif文　提出時はif(0)で実行されない
 */

#    ifdef BTK
#        define DEBUG if (1)
#        define CIN_ONLY if (0)
#    else
#        define DEBUG if (0)
#        define CIN_ONLY if (1)
#    endif
/**
 * @def ALL(v)
 * @brief
 * ALLマクロ
 */
#    define ALL(v) (v).begin(), (v).end()

/**
 * @def REC(ret, ...)
 * @brief
 * 再帰ラムダをするためのマクロ
 */
#    define REC(ret, ...) std::function<ret(__VA_ARGS__)>
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
     * @var star
     * @brief cin高速化を実体化
     */
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
        /**
         * @brief Construct a new reverse range object
         *
         * @param n
         */
        reverse_range(int n) : i({0}), n({n}) {}
        /**
         * @brief Construct a new reverse range object
         *
         * @param i
         * @param n
         */
        reverse_range(int i, int n) : i({i}), n({n}) {}
        /**
         * @brief
         * begin iterator
         * @return I&
         */
        I& begin() { return n; }
        /**
         * @brief
         * end iterator
         * @return I&
         */
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
        /**
         * @brief Construct a new range object
         *
         * @param n
         */
        range(int n) : i({0}), n({n}) {}
        /**
         * @brief Construct a new range object
         *
         * @param i
         * @param n
         */
        range(int i, int n) : i({i}), n({n}) {}
        /**
         * @brief
         * begin iterator
         * @return I&
         */
        I& begin() { return i; }
        /**
         * @brief
         * end iterator
         * @return I&
         */
        I& end() { return n; }
        /**
         * @brief
         * 逆向きに参照するrange(reverse_rangeを取得できるs)
         * @return reverse_range
         */
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
    //! LL
    using LL = long long;
} // namespace _Template_
using namespace _Template_;
/* #endregion */
/* #region 2*/

/**
 * @file Graph.hpp
 * @brief グラフクラス
 * @author btk15049
 * @date 2019/03/11
 * @details
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
        //! 辺id
        int id;
        //! 端点
        int a;
        //! 端点
        int b;
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
        //! 辺id
        int id;
        //! 端点
        int a;
        //! 端点
        int b;
        //! 辺重み
        COST_TYPE cost;

        /**
         * @brief Construct a new Weighted Edge object
         *
         * @param id
         * @param a
         * @param b
         * @param cost
         */
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
/* #endregion */
/* #region 3*/
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
     * @param inf 流量のinf
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
/* #endregion */
/*</body>*/
#endif

int main() {
    int N, M;
    cin >> N >> M;
    Graph<WeightedEdge<int>> g(3 * N, 3 * M);
    for (int i : range(M)) {
        int a, b;
        cin >> a >> b;
        g.add_arc(a - 1, 1 * N + b - 1, 1);
        g.add_arc(N + a - 1, 2 * N + b - 1, 1);
        g.add_arc(N + N + a - 1, b - 1, 1);
    }
    g.resize(3 * N);
    int S, T;
    cin >> S >> T;
    S--;
    T--;
    auto d = dijkstra(g, (LL)1e15, S);
    if (d[T] > 3 * N) d[T] = -3;
    cout << d[T] / 3 << endl;
    return 0;
}