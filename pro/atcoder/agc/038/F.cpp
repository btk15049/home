// https://atcoder.jp/contests/agc038/tasks/agc038_f
#define CIN_ONLY
#define DECIMAL_DIGITS 10
#define STATIC_MOD 1e9 + 7

#ifdef BTK
/*<head>*/
#    include "Template.hpp"
#    include "graph/Dinic.hpp"
#    include "structure/UnionFind.hpp"
/*</head>*/
#else
/*<body>*/
/* #region auto includes */
/* #region stl */
/*<stl>*/
#    include <bits/stdc++.h>
#    include <sys/types.h>
#    include <unistd.h>
using namespace std;
/*</stl>*/
/* #endregion */
/* #region template/IncludeSTL.hpp*/
/**
 * @file IncludeSTL.hpp
 * @author btk
 * @brief 標準ライブラリをincludeするだけ
 * @version 0.1
 * @date 2019-07-21
 *
 * @copyright Copyright (c) 2019
 *
 */

/*<head>*/
#    pragma once
/*</head>*/


/*<stl>*/
#    include <bits/stdc++.h>
#    include <sys/types.h>
#    include <unistd.h>
using namespace std;
/*</stl>*/
/* #endregion */
/* #region template/Macro.hpp*/
/**
 * @file Macro.hpp
 * @author btk
 * @brief マクロとか，LLとか
 * @version 0.1
 * @date 2019-07-13
 *
 * @copyright Copyright (c) 2019
 *
 */


//! LL
using LL = long long;

/**
 * @def DEBUG
 * @brief デバッグ用のif文 提出時はif(0)で実行されない
 */

/*</head>*/
#    ifdef BTK
#        define DEBUG if (1)
#    else
#        ifdef CIN_ONLY
#            define FAST_IO
#        endif
#        define DEBUG if (0)
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

/**
 * @def VAR_NAME(var)
 * @brief 変数名を取得する
 */
#    define VAR_NAME(var) #    var

/**
 * @brief
 * rangeで生まれる使わない変数を消す用（警告消し）
 */
template <typename T>
inline T& unused_var(T& v) {
    return v;
}
/* #endregion */
/* #region template/IO.hpp*/
/**
 * @file IO.hpp
 * @author btk
 * @brief cin高速化とか，出力の小数桁固定とか
 * @version 0.1
 * @date 2019-07-13
 *
 * @copyright Copyright (c) 2019
 */


/**
 * @brief 入出力の設定を行うための構造体
 */
struct cww {
    /**
     * @brief Construct a new cww::cww object
     * @details
     * CIN_ONLYを定義すると，submit時にcinとscanfの同期を切る設定が走る
     * DECIMAL_DIGITSを定義すると，doubleの出力時指定した桁数分小数部を吐くようになる
     */
    cww() {
#    ifdef FAST_IO
        ios::sync_with_stdio(false);
        cin.tie(0);
#    endif
#    ifdef DECIMAL_DIGITS
        cout << fixed;
        cout << setprecision(DECIMAL_DIGITS);
#    endif
    }
};

//! 入出力設定構造体を実体化
cww star;

/**
 * @brief
 * vectorに直接cin流すためのやつ
 * @tparam T
 * @param is
 * @param v
 * @return istream&
 */
template <typename T>
std::istream& operator>>(std::istream& is, std::vector<T>& v) {
    for (auto& it : v) is >> it;
    return is;
}
/* #endregion */
/* #region template/Loop.hpp*/
/**
 * @file Loop.hpp
 * @author btk
 * @brief rangeとかループ系のクラス
 * @version 0.1
 * @date 2019-07-13
 *
 * @copyright Copyright (c) 2019
 *
 */


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
/* #endregion */
/* #region template/MinMaxOperation.hpp*/
/**
 * @file MinMaxOperation.hpp
 * @author btk
 * @brief 最大値とか最小値を求める
 * @version 0.1
 * @date 2019-07-04
 *
 * @copyright Copyright (c) 2019
 *
 */

/**
 * @brief 2項の最小値求める
 *
 * @tparam T
 */
template <typename T>
struct min_op {
    /**
     * @brief 本体
     *
     * @param l
     * @param r
     * @return T
     */
    static T exec(const T l, const T r) { return l < r ? l : r; }
};

/**
 * @brief 2項の最大値求める
 *
 * @tparam T
 */
template <typename T>
struct max_op {
    /**
     * @brief 本体
     *
     * @param l
     * @param r
     * @return T
     */
    static T exec(const T l, const T r) { return l > r ? l : r; }
};

/**
 * @brief テンプレート再帰の末尾
 *
 * @tparam F 二項演算
 * @tparam T
 * @param v
 * @return T
 */
template <typename F, typename T>
inline T multi_op(T&& v) {
    return v;
}

/**
 * @brief 複数項における演算の結果を返す
 *
 * @tparam F
 * @tparam T
 * @tparam Ts
 * @param head
 * @param tail
 * @return T
 */
template <typename F, typename T, typename... Ts>
inline T multi_op(const T head, Ts&&... tail) {
    return F::exec(head, multi_op<F>(tail...));
}

/**
 * @brief 複数項の最小値
 * @see multi_op
 * @tparam T
 * @tparam Ts
 * @param head
 * @param tail
 * @return T
 */
template <typename T, typename... Ts>
inline T multi_min(T&& head, Ts&&... tail) {
    return multi_op<min_op<T>>(head, tail...);
}

/**
 * @brief 複数項の最大値
 * @see multi_op
 * @tparam T
 * @tparam Ts
 * @param head
 * @param tail
 * @return T
 */
template <typename T, typename... Ts>
inline T multi_max(T&& head, Ts&&... tail) {
    return multi_op<max_op<T>>(head, tail...);
}

/**
 * @brief
 * 先頭の値をFで参照する関数に基づいて変更できたらする
 * @tparam F
 * @tparam T
 * @tparam Ts
 * @param target
 * @param candidates
 * @return true
 * @return false
 */
template <typename F, typename T, typename... Ts>
inline bool ch_op(T& target, Ts&&... candidates) {
    const T old = target;
    target      = multi_op<F>(target, candidates...);
    return old != target;
}

/**
 * @brief change min
 * @tparam T 型
 * @param target 変更する値
 * @param candidates
 * @return 更新があればtrue
 */
template <typename T, typename... Ts>
inline bool chmin(T& target, Ts&&... candidates) {
    return ch_op<min_op<T>>(target, candidates...);
}

/**
 * @brief chminのmax版
 * @see chmin
 *  @tparam T 型
 * @param target 変更する値
 * @param candidates
 * @return 更新があればtrue
 */
template <typename T, typename... Ts>
inline bool chmax(T& target, Ts&&... candidates) {
    return ch_op<max_op<T>>(target, candidates...);
}
/* #endregion */
/* #region template/Random.hpp*/
/**
 * @file Random.hpp
 * @author btk
 * @brief 乱数生成系
 * @version 0.1
 * @date 2019-07-13
 * @copyright Copyright (c) 2019
 */


//! 乱数のシード値をプロセスIDとして取得
const pid_t pid = getpid();

/**
 * @brief XorShift32の実装
 */
class XorShift32 {
  private:
    //! XorShiftの現在の値
    unsigned value;

    /**
     * @brief XorShift32のアルゴリズムに基づいて value を更新
     */
    inline void update() {
        value = value ^ (value << 13);
        value = value ^ (value >> 17);
        value = value ^ (value << 5);
    }

    /**
     * @brief 値を更新し，更新前の値を返却
     * @return unsigned 呼び出し時の value を用いる
     */
    inline unsigned get() {
        unsigned v = value;
        update();
        return v;
    }

  public:
    /**
     * @brief [0, 2^bit) の範囲の乱数値を取り出す
     * @tparam デフォルトは31
     * @return int
     */
    template <int bit = 31>
    inline int next_int() {
        return (int)(get() >> (32 - bit));
    }

    /**
     * @brief [-2^bit,2^bit)の範囲の乱数値を取り出す
     * @tparam デフォルトは31
     * @return int
     */
    template <int bit = 31>
    inline int next_signed() {
        unsigned v = get();
        return (int)((v >> (31 - bit)) - (1 << (bit)));
    }

    /**
     * @brief next_int呼び出し時の最大値を取得
     * @tparam 31
     * @return int
     */
    template <int bit = 31>
    inline int range_max() {
        return (int)((1u << bit) - 1);
    };

    /**
     * @brief Construct a new XorShift32 object
     * @param seed
     * @details 初期シードをvalueとするXorShift32のインスタンスを生成
     */
    XorShift32(const unsigned seed) {
        value = seed;
        update();
    }

    /**
     * @brief Construct a new XorShift 32 object
     * @details 初期シードをプロセスIDとするXorShift32のインスタンスを生成
     */
    XorShift32() : XorShift32(pid) {}
};
/* #endregion */
/* #region Template.hpp*/
/**
 * @file Template.hpp
 * @brief 競技プログラミング用テンプレート
 * @author btk15049
 * @date 2019/05/02
 */


/* #endregion */
/* #region graph/Graph.hpp*/
/**
 * @file Graph.hpp
 * @brief グラフクラス
 * @author btk15049
 * @date 2019/03/11
 * @details
 *  verify: WUPC C
 */


/**
 * @brief 辺を扱う構造体の例
 * @details
 *   辺に重みなどを加えたい場合は変数とかを増やして作る．
 *   Graphに使うために必要な要件:
 *   - id,a,bは必須，他のパラメータ増やすときはコンストラクタを忘れずに
 *   - versusは必須，基本的にコピペでOK
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
    std::vector<E> edges;
    //! 隣接リスト
    std::vector<std::vector<int>> g;

  public:
    /**
     * @brief Construct a new Graph object
     * @param reserved_vertex_size 頂点数の最大値，vectorのサイズ確保用
     * @param reserved_edge_size 辺数の最大値，vectorのサイズ確保用
     */
    Graph(int reserved_vertex_size = 1, int reserved_edge_size = -1) {
        g.reserve(reserved_vertex_size);
        edges.reserve(std::max(reserved_vertex_size, reserved_edge_size));
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
        if ((int)g.size() <= std::max(a, b)) {
            g.resize(std::max(a, b) + 1);
        }
        g[a].emplace_back(id);
        g[b].emplace_back(id);
        edges.emplace_back(id, a, b, std::forward<Ts>(params)...);
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
        if ((int)g.size() <= std::max(a, b)) {
            g.resize(std::max(a, b) + 1);
        }
        g[a].emplace_back(id);
        edges.emplace_back(id, a, b, std::forward<Ts>(params)...);
    }

    /**
     * @brief 辺を追加 idは自動付与
     * @param e
     */
    inline void add_arc(E e) {
        e.id = edges.size();
        if ((int)g.size() <= std::max(e.a, e.b)) {
            g.resize(std::max(e.a, e.b) + 1);
        }
        g[e.a].emplace_back(e.id);
        edges.emplace_back(e);
    }

    /**
     * @brief vの隣接頂点を返す
     * @param v int
     * @return vector<int>
     */
    inline std::vector<int> Ns(const int v) {
        std::vector<int> ns(g[v].size());
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
    inline const std::vector<int>& operator[](const int v) { return g[v]; }

    /**
     * @brief 辺番号から辺の参照を取得する
     * @param edge_id
     * @return E&
     */
    inline E& i2e(const int edge_id) { return edges[edge_id]; }
};
/* #endregion */
/* #region graph/Dinic.hpp*/
/**
 * @file Dinic.hpp
 * @brief Dinic法の実装
 * @author btk15049
 * @date 2019/03/13
 * @details
 *  \todo verify
 *  verify: WUPC F
 */


#    include <queue>

/**
 * @brief フロー用の辺構造体
 * @tparam F 流量の型
 */
template <typename F>
struct FlowEdge {
    //! 辺id
    int id;
    //! 端点
    int a;
    //! 端点
    int b;
    //! その辺に流せる流量
    F cap;
    //! 逆向き辺のid
    int rev;
    /**
     * @brief Construct a new Edge object
     * @param id 辺番号
     * @param a 辺に接続する頂点番号
     * @param b 辺に接続する頂点番号
     * @param cap 辺に許容できる流量
     * @param rev 対応する逆向き辺のid
     */
    FlowEdge(int id = 0, int a = 0, int b = 0, F cap = 0, int rev = 0)
        : id(id), a(a), b(b), cap(cap), rev(rev) {}
    /**
     * @brief 辺における，vの対になってる頂点番号を取得する
     * @param v 頂点番号
     * @return int vじゃない方の頂点番号
     */
    inline int versus(const int v) const { return a ^ b ^ v; }
};

/**
 * @brief フロー用のグラフクラス,Graphを継承
 * @tparam E 辺構造体
 */
template <typename E>
class FlowGraph : public Graph<E> {
  private:
    using Graph<E>::add_arc; // add_arcは外から呼び出せないようにする
  public:
    /**
     * @brief a->bへ流量fの辺を追加
     * @tparam F 流量の型
     * @param a 頂点番号
     * @param b 頂点番号
     * @param f 最大流量
     * @details Graph::add_edge をオーバーライドしている．
     */
    template <typename F>
    inline void add_edge(int a, int b, F f) {
        const int id = this->degree();
        this->add_arc(a, b, f, id + 1);
        this->add_arc(b, a, 0, id);
    }
    /**
     * @brief Construct a new Flow Graph object
     * @details
     * 完全転送してるので詳しくはGraphクラスのコンストラクタを参照．
     */
    template <typename... Ts>
    FlowGraph(Ts&&... params) : Graph<E>(std::forward<Ts>(params)...) {}
};

/**
 * @brief Dinic法の実装
 * @tparam F 流量の型
 * @tparam flow_inf 流量の最大値
 */
template <typename F, F flow_inf>
class Dinic {
  private:
    using E = FlowEdge<F>;
    FlowGraph<E>* G;
    /**
     * @brief 最短路求めるBFSをする
     * @param s 始点
     * @return vector<int> sから各頂点への最短距離
     */
    std::vector<int> bfs(const int s) {
        int N = G->size();
        std::queue<int> que;
        std::vector<int> dist(N, -1);
        dist[s] = 0;
        que.push(s);
        for (; !que.empty(); que.pop()) {
            const int v = que.front();
            for (int id : (*G)[v]) {
                const E& e  = G->i2e(id);
                const int u = e.versus(v);
                if (e.cap > 0 && dist[u] == -1) {
                    dist[u] = dist[v] + 1;
                    que.push(u);
                }
            }
        }
        return dist;
    }
    /**
     * @brief s->tに向けてできるだけフローを流す
     */
    F dfs(const int v, const int s, const F f, std::vector<unsigned>& I,
          std::vector<int>& D) {
        if (v == s) return f;
        const std::vector<int>& edge_ids = (*G)[v];
        for (unsigned& i = I[v]; i < edge_ids.size(); i++) {
            E& e        = G->i2e(edge_ids[i]);
            E& re       = G->i2e(e.rev);
            const int u = e.versus(v);
            if (re.cap > 0 && D[v] > D[u]) {
                F d = dfs(u, s, std::min(f, re.cap), I, D);
                if (d > 0) {
                    e.cap += d;
                    re.cap -= d;
                    return d;
                }
            }
        }
        return 0;
    }

  public:
    /**
     * @brief 現在の残余グラフから得られる最大流を求めて流す．
     * @param s 始点
     * @param t 終点
     * @return F 流量
     */
    F solve(const int s, const int t) {
        F res = 0;
        while (true) {
            std::vector<int> dist = bfs(s);
            if (dist[t] < 0) break;
            std::vector<unsigned> iter(G->size(), 0);
            while (true) {
                F f = dfs(t, s, flow_inf, iter, dist);
                if (f == 0) break;
                res += f;
            }
        }
        return res;
    }
    /**
     * @brief Construct a new Dinic object
     * @param G 最大流を流したいグラフ
     */
    Dinic(FlowGraph<E>& G) : G(&G) {}
};
/* #endregion */
/* #region structure/UnionFind.hpp*/
/**
 * @file UnionFind.hpp
 * @author btk
 * @brief Union-Find 木
 * @version 0.1
 * @date 2019-06-26
 * @todo test
 */

/**
 * @brief unionとfindとsameができる普通のUnion-Find
 */
class UnionFind {
  private:
    std::vector<int> par, rank;

    /**
     * @brief ${x}の親を${new_par}に設定åå
     * @param x
     * @param new_par
     */
    inline void set_par(int x, int new_par) { par[x] = new_par; }

  public:
    /**
     * @brief xの親を探す
     * @param x
     * @return int
     */
    int find(int x) {
        if (par[x] != x) {
            int new_par = find(par[x]);
            set_par(x, new_par);
        }
        return par[x];
    }

    /**
     * @brief Construct a new Union Find object
     *
     * @param n
     */
    UnionFind(int n) : par(n), rank(n) {
        for (int i = 0; i < n; i++) {
            par[i] = i, rank[i] = 0;
        }
    }

    /**
     * @brief {xの属する集合}と{yの属する集合}をマージする
     *
     * @param x
     * @param y
     * @return true マージに成功したとき
     * @return false マージに失敗したとき（もともと同じ集合に属していた時）
     */
    bool unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        if (rank[x] < rank[y]) std::swap(x, y);
        set_par(y, x);
        if (rank[x] == rank[y]) rank[x]++;
        return true;
    }

    /**
     * @brief　xとyが同じ集合に属しているかどうか判定する
     * @param x
     * @param y
     * @return true
     * @return false
     */
    bool same(int x, int y) { return find(x) == find(y); }
};
/* #endregion */
/* #endregion */
/*</body>*/
#endif

int main() {
    int N;
    cin >> N;
    vector<int> P(N), Q(N);
    cin >> P >> Q;
    UnionFind p(N), q(N);
    FlowGraph<FlowEdge<int>> g(2 * N, 2 * N);
    for (int i : range(N)) {
        p.unite(i, P[i]);
        q.unite(i, Q[i]);
    }
    const int S = 2 * N;
    const int T = 2 * N + 1;
    g.resize(T + 1);
    int cap  = 0;
    auto RM  = [&g, T](int p) { g.add_edge(p, T, 1); };
    auto BM  = [&g, S](int p) { g.add_edge(S, p, 1); };
    auto RBM = [&g](int p, int q) { g.add_edge(p, q, 1); };
    auto RP  = [&g, &cap, &BM](int p) {
        cap++;
        BM(p);
    };
    auto BP = [&g, &cap, &RM](int p) {
        cap++;
        RM(p);
    };


    for (int i : range(N)) {
        int pi = p.find(i);
        int qi = q.find(i) + N;
        if (P[i] == Q[i] && Q[i] == i) {
            // do nothing
        }
        else if (Q[i] != P[i] && P[i] == i) {
            BP(qi);
        }
        else if (P[i] != Q[i] && Q[i] == i) {
            RP(pi);
        }
        else if (P[i] == Q[i] && Q[i] != i) {
            RP(pi);
            BP(qi);
            RBM(pi, qi);
            RBM(pi, qi);
        }
        else {
            RP(pi);
            BP(qi);
            RBM(pi, qi);
        }
    }

    cout << cap - Dinic<int, 312345>(g).solve(S, T) << endl;

    return 0;
}