// https://atcoder.jp/contests/abc149/tasks/abc149_f
#define CIN_ONLY
#define DECIMAL_DIGITS 10
#define STATIC_MOD 1e9 + 7

#ifdef BTK
/*<head>*/
#    include "Template.hpp"
#    include "graph/Tree.hpp"
#    include "num/ModInt.hpp"
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
 * @todo 何故か2回includeされる（展開scriptに
 * @copyright Copyright (c) 2019
 *
 */


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
     * @brief グラフの頂点数を変更する
     * @todo 分かりづらいので，set_vertex_sizeとかに変える
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
     * @param v int 頂点番号
     * @return vector<int> 辺番号の集合
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
/* #region graph/Tree.hpp*/

/**
 * @file Tree.hpp
 * @brief 根付き森と根付き木
 * @author btk15049
 * @date 2019/05/07
 * @details
 *  verify:
 */

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
    std::vector<int> roots;

    /**
     * @brief
     * DFSで木を作る
     */
    void build_tree(Graph<E>& g, const int v, std::vector<bool>& used) {
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
        std::vector<bool> used(g.size());
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
    std::vector<int> get_roots() { return roots; }
};

/**
 * @brief
 * "木"に限定したクラス
 * @tparam Edge 辺構造体
 */
template <typename E = Edge>
class Tree : public Forest<E> {
  private:
    using Forest<E>::get_roots;
    //! 根
    const int root;

  public:
    /**
     * @brief Construct a new Tree object
     * @param g 元のグラフ
     * @param root 根を明示的に指定したい時
     */
    Tree(Graph<E>& g, const int root = 0) : Forest<E>(g, root), root(root) {}

    /**
     * @brief Get the root object
     * @return int
     */
    inline int get_root() { return root; }
};
/* #endregion */
/* #region num/ModInt.hpp*/

#    include <utility>

/**
 * @file ModInt.hpp
 * @brief mod構造体
 * @author btk15049
 * @date 2019/03/08
 * @details
 *  \todo verifyが足りない
 *  verify: CSA12E，RUPC day3 F
 */

//! [WARNING!] mod が入力で与えられる場合はconstexprを外す
#    ifdef STATIC_MOD
constexpr int mod = STATIC_MOD;
#    else
int mod;
#    endif

/**
 * @brief mod構造体
 * @details
 * 整数をラップして，常に保持されているデータがmodされた状態になるよう管理．
 */
class ModInt {
  private:
    //! 中身
    int x;

  public:
    /**
     * @brief ゲッター
     * @details 出力時などは "cout << *ret << endl;"のようにやるとよい．
     */
    long long operator*() const { return x; }
    /**
     * @brief デフォルトコンストラクタ．0で初期化される．
     */
    ModInt() { x = 0; }

    /**
     * @brief intからのコンストラクタ
     * @param[in] y 設定したい値
     * @details
     * modをとらないので高速．ただしmodより大きい値や負の数を入れると事故るので注意．
     */
    ModInt(const int y) { x = y; }

    /**
     * @brief long longからのコンストラクタ
     * @param[in] y 設定したい値
     * @details 毎回modを取るので低速．
     */
    ModInt(const long long y) { x = (int)((mod + y % mod) % mod); }

    /**
     * @brief ModIntからの代入演算子
     * @param[in] o 設定したい値
     * @details 高速
     */
    ModInt(const ModInt& o) { this->x = *o; }
    /**
     * @brief 整数から高速にModIntを作りたいときに使う
     * @param[in] x 設定したい値
     * @details xが[0,mod)であることが保証されてないと正しく動かない．
     */
    static inline ModInt raw(const long long x) {
        // assert(x<mod);
        return ModInt((int)x);
    }

    /**
     * @brief 整数から安全にModIntを作りたいときに使う
     * @param[in] x 設定したい値
     * @details mod2回取るから遅い．負数でもOK．
     */
    static inline ModInt get(const long long x) { return ModInt(x); }

    /**
     * @brief intからの代入演算子
     * @param[in] o 設定したい値
     * @details
     * modをとらないので高速．ただしmodより大きい値や負の数を入れると事故るので注意．
     */
    ModInt& operator=(const int o) {
        this->x = o >= mod ? o - mod : o;
        return *this;
    }

    /**
     * @brief long longからの代入演算子
     * @param[in] o 設定したい値
     * @details mod2回取るから遅い．負数でもOK．
     */
    ModInt& operator=(const long long o) {
        this->x = (int)((mod + o % mod) % mod);
        return *this;
    }

    /**
     * @brief ModIntからの代入演算子
     * @param[in] o 設定したい値
     * @details 高速
     */
    ModInt& operator=(const ModInt o) {
        this->x = *o;
        return *this;
    }
};

/**
 * @param[in] l ModInt
 * @param[in] r ModInt
 * @details if文使って少し高速化．
 */
inline ModInt add(const ModInt l, const ModInt r) {
    const long long x = *l + *r;
    return ModInt::raw(x >= mod ? x - mod : x);
}

/**
 * @param[in] l ModInt
 * @param[in] r ModInt．
 */
inline ModInt mul(const ModInt l, const ModInt r) {
    return ModInt::raw(*l * *r % mod);
}

/**
 * @brief a^x %modを求める
 * @param[in] a ModInt
 * @param[in] x long long．
 */
inline ModInt pow(ModInt a, long long x) {
    ModInt ret = ModInt::raw(1);
    while (x) {
        if (x & 1) {
            ret = mul(ret, a);
        }
        a = mul(a, a);
        x >>= 1;
    }
    return ret;
}

/**
 * @brief x^-1 %modを求める
 * @param[in] x ModInt．
 * @details
 *   内部ではユークリッドの拡張互助法を使っている．
 *   O(log(mod))
 */
inline ModInt inv(const ModInt x) {
    long long a = *x, b = mod, u = 1, v = 0;
    while (b) {
        long long t = a / b;
        std::swap(a -= t * b, b);
        std::swap(u -= t * v, v);
    }
    return ModInt::get(u);
}

/**
 * @brief 負数を求める単項演算子
 * @param[in] x ModInt
 */
inline ModInt operator-(const ModInt x) { return add(mod, -*x); }

/**
 * @param[in] l ModInt
 * @param[in] r ModInt
 */
inline ModInt operator+(const ModInt l, const ModInt r) { return add(l, r); }

/**
 * @param[in] l ModInt
 * @param[in] r ModInt
 */
inline ModInt operator*(const ModInt l, const ModInt r) { return mul(l, r); }

/**
 * @param[in] l ModInt
 * @param[in] r ModInt
 */
inline ModInt operator-(const ModInt l, const ModInt r) { return add(l, -r); }

/**
 * @param[in] l ModInt
 * @param[in] r int
 * @details
 * 右辺は定数を想定しているのでmodをとらないrawを使ってModIntに変換している．ただしmodより大きい値や負の数を入れると事故るので注意．
 */
inline ModInt operator+(const ModInt l, const int r) {
    return add(l, ModInt::raw(r));
}

/**
 * @param[in] l ModInt
 * @param[in] r int
 */
inline ModInt operator+(const ModInt l, const long long r) {
    return add(l, ModInt::get(r));
}

/**
 * @param[in] l ModInt
 * @param[in] r int
 * @details
 * 右辺は定数を想定しているのでmodをとらないrawを使ってModIntに変換している．ただしmodより大きい値や負の数を入れると事故るので注意．
 */
inline ModInt operator*(const ModInt l, const int r) {
    return mul(l, ModInt::raw(r));
}

/**
 * @param[in] l ModInt
 * @param[in] r int
 */
inline ModInt operator*(const ModInt l, const long long r) {
    return mul(l, ModInt::get(r));
}

/**
 * @param[in] l ModInt
 * @param[in] r int
 * @details
 * 右辺は定数を想定しているのでmodをとらないrawを使ってModIntに変換している．ただしmodより大きい値や負の数を入れると事故るので注意．
 */
inline ModInt operator-(const ModInt l, const int r) {
    return add(l, ModInt::raw(mod - r));
}

/**
 * @param[in] l ModInt
 * @param[in] r int
 */
inline ModInt operator-(const ModInt l, const long long r) {
    return add(l, -ModInt::get(r));
}

/**
 * @param[in] l ModInt
 * @param[in] r int
 * @details
 * 右辺は定数を想定しているのでmodをとらないrawを使ってModIntに変換している．ただしmodより大きい値や負の数を入れると事故るので注意．
 */
inline ModInt operator/(const ModInt l, const int r) {
    return mul(l, inv(ModInt::raw(r)));
}

/**
 * @param[in] l ModInt
 * @param[in] r int
 */
inline ModInt operator/(const ModInt l, const long long r) {
    return mul(l, inv(ModInt::get(r)));
}

/**
* @param[in] l ModInt
* @param[in] r long long
* @details
*   pow(l,r)を呼び出すだけなのでpowを参照のこと．
計算量はO(log mod)
*/
inline ModInt operator^(const ModInt l, const long long r) { return pow(l, r); }

/**
 * @brief
 * +=の実装、各operator+を呼ぶだけ
 * @tparam T
 * @param l ModInt
 * @param r 足すやつ
 * @return ModInt&
 */
template <typename T>
ModInt& operator+=(ModInt& l, T r) {
    l = l + r;
    return l;
}

/**
 * @brief
 * -=の実装、各operator-を呼ぶだけ
 * @tparam T
 * @param l ModInt
 * @param r 引くやつ
 * @return ModInt&
 */
template <typename T>
ModInt& operator-=(ModInt& l, T r) {
    l = l - r;
    return l;
}

/**
 * @brief
 * *=の実装、各operator*を呼ぶだけ
 * @tparam T
 * @param l ModInt
 * @param r かけるやつ
 * @return ModInt&
 */
template <typename T>
ModInt& operator*=(ModInt& l, T r) {
    l = l * r;
    return l;
}

/**
 * @namespace factorial
 * @brief 順列数関連の関数のまとめ
 * @details
 *   - combination
 *   - permutation
 *   - multiChoose
 */
namespace factorial {
    //! 順列数を格納する配列のサイズ
    constexpr int size =
#    ifdef FACTORIAL_SIZE
        FACTORIAL_SIZE;
#    else
        3123456;
#    endif
    //! 前計算ができているかどうかのフラグ
    bool is_build = false;

    //! 順列数を格納する配列
    ModInt factorial[size];
    //! (順列数)^-1を格納する配列
    ModInt inverse_factorial[size];

    /**
     * @brief 順列数の前計算
     * @details
     *   順列数と，その逆元を[0,size)まで求める.
     *   計算量は，O(size + log(mod))
     */
    void build() {
        is_build     = true;
        factorial[0] = 1;
        for (int i = 1; i < size; i++) {
            factorial[i] = factorial[i - 1] * i;
        }
        inverse_factorial[size - 1] = inv(factorial[size - 1]);
        for (int i = size - 1; i >= 1; i--) {
            inverse_factorial[i - 1] = inverse_factorial[i] * i;
        }
    }

    /**
     * @brief nPkを求める
     * @details
     *   前計算がしてあれば O(1)．前計算してない場合は is_build
     * を読み取って前計算をする．
     */
    inline ModInt permutation(int n, int k) {
        if (k < 0 || k > n) return ModInt::raw(0);
        if (!is_build) build();
        return factorial[n] * inverse_factorial[n - k];
    }

    /**
     * @brief nCkを求める
     * @details
     *   前計算がしてあれば O(1)．前計算してない場合は is_build
     * を読み取って前計算をする．
     */
    inline ModInt combination(int n, int k) {
        if (k < 0 || k > n) return ModInt::raw(0);
        if (!is_build) build();
        return factorial[n] * inverse_factorial[k] * inverse_factorial[n - k];
    }

    /**
     * @brief 重複組合せ
     * @param n 何種類のものを
     * @param r いくつ並べるか
     * @return ModInt nHr
     */
    ModInt multiChoose(int n, int r) {
        if (n == 0 && r == 0) return ModInt::raw(1);
        return combination(n + r - 1, r);
    }

    /**
     * @brief 上限付き重複組合せ
     * @details
     * 包除原理を用いて，lim個以上の品物が1,2,...,i種類の場合を足したり引いたりしていく
     * 計算量は O(min(n, r / lim))
     * @param n 何種類のものを
     * @param r いくつ並べるか
     * @param lim 1種類のものを選べる上限
     * @return ModInt
     */
    ModInt multiChoose(int n, int r, int lim) {
        ModInt ret = 0;
        for (int i = 0; i <= n; i++) {
            if (i * (lim + 1) > r) break;
            ret += ((i & 1) ? mod - 1 : 1) * combination(n, i)
                   * multiChoose(n, r - i * (lim + 1));
        }
        return ret;
    }

} // namespace factorial
  /* #endregion */
  /* #endregion */
  /*</body>*/
#endif
int N;
int sz[212345];
ModInt ret = 0;
Graph<> g;

void dfs(int v, Tree<> &t) {
    sz[v]      = 1;
    ModInt out = 0;
    for (int u : t.Ns(v)) {
        dfs(u, t);
        sz[v] += sz[u];
        out += inv(ModInt(2) ^ (N - sz[u] - 1));
    }
    if (v != 0) {
        int b = N - sz[v];
        out += inv(ModInt(2) ^ (N - b - 1));
    }
    out -= (g.degree(v) - 1) * inv(ModInt(2) ^ (N - 1));
    // cerr << v + 1 << " " << *out << endl;
    ret += inv(2) * (1 - out);
}
int main() {
    /* write here */
    cin >> N;
    for (int i : range(N - 1)) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        g.add_edge(a, b);
    }
    Tree<> t(g);

    dfs(0, t);
    cout << *ret << endl;
    return 0;
}