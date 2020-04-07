// https://atcoder.jp/contests/abc148/tasks/abc148_f
#define CIN_ONLY
#define DECIMAL_DIGITS 10
#define STATIC_MOD 1e9 + 7

#ifdef BTK
/*<head>*/
#    include "Template.hpp"
#    include "graph/HeavyLightDecomposition.hpp"
#    include "graph/Tree.hpp"
#    include "structure/Buffer.hpp"
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
/* #region structure/Buffer.hpp*/

#    include <queue>

/**
 * @file Buffer.hpp
 * @brief メモリ管理クラス
 * @author btk15049
 * @date 2019/03/11
 * @details
 */
/**
 * @brief
 * バッファは基本的にこれを継承する
 * @tparam T
 */
template <typename T>
class BufferManager {
  protected:
    /**
     * @brief
     * 本体、ポインタで管理
     * \todo unique_ptrに変更
     */
    T* buf;

  public:
    /**
     * @brief Construct a new Buffer Manager object
     *
     * @param buf
     */
    BufferManager(T* buf) : buf(buf) {}
    /**
     * @brief
     * size分バッファを取得
     * @param size
     * @return T*
     */
    virtual T* pop(int size) = 0;
    /**
     * @brief
     * 領域をマネージャに返却（解放）する
     * @param p
     */
    virtual void push(T* p) = 0;
    /**
     * @brief
     * マネージャのリセット
     */
    virtual void clear() = 0;
};

/**
 * @brief 使った分だけメモリを使い捨てするmaneger
 * 使い回ししたい場合には不向き
 *
 * @tparam T
 */
template <typename T>
class DisposableBufferManager : public BufferManager<T> {
  private:
    //! どこまで使ったかを管理
    int ptr;

  public:
    /**
     * @brief Construct a new Disposable Buffer Manager object
     *
     * @param buf 配列を保持するポインタ
     */
    DisposableBufferManager(T* buf) : BufferManager<T>(buf), ptr(0){};

    /**
     * @brief ポインタを返して、使った分だけptrを進める
     *
     * @param size 欲しい領域のサイズ
     * @return T*
     */
    T* pop(int size) {
        ptr += size;
        return this->buf + ptr - size;
    }

    /**
     * @brief 何もしない
     *
     * @param p
     */
    void push(T* p) { unused_var(p); }

    /**
     * @brief ptrをリセット
     *
     */
    void clear() { ptr = 0; }

    /**
     * @brief Get the ptr object
     * 現在どこまで使っているかがわかる。主にデバッグ用
     * @return int
     */
    int get_ptr() { return ptr; }
};

/**
 * @def DisposableBuffer(type, size, var_name)
 * @brief
 * [var_name]という名前のDisposalBufferManagerを生成する
 */
#    define DisposableBuffer(type, size, var_name) \
        type var_name##_mem[size];                 \
        DisposableBufferManager<type> var_name(var_name##_mem);

/**
 * @brief
 * blocks*block_size分の領域をblocks個に区切って、やりくりする。
 * 使わなくなったらpopで返すのを忘れずに
 * @tparam T
 */
template <typename T>
class BlockBufferManager : public BufferManager<T> {
  private:
    //! 使われてないblockをキューで管理
    std::queue<T*> que;

  public:
    /**
     * @brief Construct a new Block Buffer Manager object
     *
     * @param buf
     * @param blocks
     * @param block_size
     */
    BlockBufferManager(T* buf, int blocks, int block_size)
        : BufferManager<T>(buf) {
        for (int i : range(blocks)) {
            que.push(this->buf + i * block_size);
        }
    };

    /**
     * @brief　blockを取得
     *
     * @param size 意味ないよ
     * @return T*
     */
    T* pop(int size = 0) {
        unused_var(size);
        T* ptr = que.front();
        que.pop();
        return ptr;
    }

    /**
     * @brief デストラクタとかでpush呼ぶのを忘れずに
     *
     * @param p
     */
    void push(T* p) { que.push(p); }

    /**
     * @brief 今の所何もしない
     * \todo 要検討
     */
    void clear() {}

    /**
     * @brief キューの残りサイズを取得 デバッグ用
     *
     * @return int
     */
    int get_queue_size() { return que.size(); }
};

/**
 * @def BlockBuffer(type, blocks, block_size, var_name)
 * @brief
 * [var_name]という名前のBlockBufferManagerを生成する
 * type型で、大きさ　block_size の領域をblocks分生成
 */
#    define BlockBuffer(type, blocks, block_size, var_name)         \
        type var_name##_mem[(blocks) * (block_size)];               \
        BlockBufferManager<type> var_name(var_name##_mem, (blocks), \
                                          (block_size));
/* #endregion */
/* #region graph/HeavyLightDecomposition.hpp*/
/**
 * @file HeavyLightDecomposition.hpp
 * @author btk
 * @brief 重軽分解
 * @version 0.1
 * @date 2019-06-04
 *
 */


/**
 * @brief 重軽分解
 * @details 各パスを色で塗っていく
 * col[v] = col[u] のときは同じ成分
 * col のナンバリング順は DFS ordering
 * とする。ある成分の子にあたる成分は必ず番号が大きくなる
 */
template <typename E>
class HeavyLightDecomposition {
  private:
    BufferManager<int>& lender;
    static constexpr int super_root = -1;
    //! col[v] := 頂点 v の色（含まれるパス成分の番号）
    int* col;
    //! i2v[i] := v HL分解の順にそった、元のグラフでのDFS-ordering
    int* i2v;
    //! i2v[v2i[v]]]=v
    int* v2i;

    //! 各パスのrootの開始位置(rootがordのどこにあるか)
    int* col_root;
    //! 各頂点の親
    int* par;

    /**
     * @brief
     * subに、各頂点を根とした部分木のサイズを求める
     * @param v
     * @param sub
     * @param f
     */
    void compute_subtrees(int v, std::vector<int>& sub, Forest<E>& f) {
        sub[v]++;
        for (int u : f.Ns(v)) {
            compute_subtrees(u, sub, f);
            sub[v] += sub[u];
        }
    }

    /**
     * @brief
     * compute_subtreesで求めた部分木サイズ使ってHL分解をする
     * @param v
     * @param sub
     * @param f
     * @param seg_id
     * @param col_id
     * @details
     * 太い枝を優先に色ぬりをしていく(細い枝に進むたびcol_idを進める)
     * 頂点に訪れる度seg_idを進める
     */
    void coloring(int v, std::vector<int>& sub, Forest<E>& f, int& seg_id,
                  int& col_id) {
        col[v]      = col_id;
        i2v[seg_id] = v;
        v2i[v]      = seg_id;
        seg_id++;
        if (f.degree(v) == 0) return;
        int top = 0;
        for (int i : range(f.degree(v))) {
            if (sub[f.i2e(f[v][top]).versus(v)]
                < sub[f.i2e(f[v][i]).versus(v)]) {
                top = i;
            }
        }
        {
            const int u = f.i2e(f[v][top]).versus(v);
            par[u]      = v;
            coloring(u, sub, f, seg_id, col_id);
        }
        for (int i : range(f.degree(v))) {
            if (top == i) continue;
            const int u        = f.i2e(f[v][i]).versus(v);
            par[u]             = v;
            col_root[++col_id] = seg_id;
            coloring(u, sub, f, seg_id, col_id);
        }
    }

  public:
    /**
     * @brief
     * get color of v
     * @param v
     * @return int
     */
    inline int color(int v) const { return col[v]; }

    /**
     * @brief
     * get id of v
     * @param v
     * @return int
     */
    inline int id(const int v) const { return v2i[v]; }

    /**
     * @brief
     * get v of id
     * @param id
     * @return int
     */
    inline int vertex(const int id) const { return i2v[id]; }

    /**
     * @brief
     * get parent of v
     * @param v
     * @return int
     */
    inline int parent(const int v) const { return par[v]; }


    /**
     * @brief
     * 色col_idが表すパスの長さ(頂点数）を取得
     * @param col_id
     * @return int
     */
    inline int len(int col_id) const {
        return col_root[col_id + 1] - col_root[col_id];
    }


    /**
     * @brief
     * vとuのlcaを返す
     * @param v
     * @param u
     * @return int
     * @details
     * パスの成分のidの大きい方を上にあげてく
     * 含まれる成分が一緒になったら、DFS-orderの小さい方が答え
     */
    inline int lca(int v, int u) const {
        while (v != super_root && u != super_root && col[v] != col[u]) {
            if (col[v] > col[u]) std::swap(v, u);
            u = par[i2v[col_root[col[u]]]];
        }
        if (v == super_root || u == super_root) return super_root;
        return i2v[std::min(v2i[v], v2i[u])];
    }

    /**
     * @brief Construct a new Heavy Light Decomposition object
     * lenderにはBlockBufferを使うのを推奨 N*5メモリがいるよ
     * @param f
     * @param lender
     */
    HeavyLightDecomposition(Forest<E>& f, BufferManager<int>& lender)
        : lender(lender) {
        const int n = f.size();

        col      = lender.pop(n + 10);
        v2i      = lender.pop(n + 10);
        i2v      = lender.pop(n + 10);
        col_root = lender.pop(n + 10);
        par      = lender.pop(n + 10);

        int col_id = 0;
        int seg_id = 0;
        std::vector<int> sub(n, 0);
        for (int r : f.get_roots()) {
            compute_subtrees(r, sub, f);
            par[r]           = super_root;
            col_root[col_id] = seg_id;
            coloring(r, sub, f, seg_id, col_id);
            col_id++;
        }
    }

    /**
     * @brief Destroy the Heavy Light Decomposition object
     * デストラクタ
     * メモリを返すよ
     */
    ~HeavyLightDecomposition() {
        lender.push(col);
        lender.push(v2i);
        lender.push(i2v);
        lender.push(col_root);
        lender.push(par);
    }
};
/* #endregion */
/* #endregion */
/*</body>*/
#endif

int ret = 0;
BlockBuffer(int, 10, 1000000, bb);
void dfs1(int v, Tree<>& t, vector<int>& ok) {
    for (int u : t.Ns(v)) {
        if (ok[v] == 0) ok[u] = 0;
        dfs1(u, t, ok);
    }
}
void dfs2(int v, Tree<>& t, vector<int>& ok, int d = 0) {
    if (ok[v] && t.degree(v) != 0) {
        chmax(ret, d);
    }
    for (int u : t.Ns(v)) {
        dfs2(u, t, ok, d + 1);
    }
}


int main() {
    /* write here */
    int N, D, O;
    cin >> N >> D >> O;
    O--;
    D--;
    Graph<> g(N, N);
    for (int i : range(N - 1)) {
        int a, b;
        cin >> a >> b;
        g.add_edge(a - 1, b - 1);
    }
    vector<int> ok(N, 1);

    {
        Tree<> t(g, D);
        HeavyLightDecomposition<Edge> dec(t, bb);
        int len = 0;
        {
            int z = O;
            while (z != D) {
                z = dec.parent(z);
                len++;
                cerr << z << endl;
            }
        }
        {
            int z = O;
            int i = 0;
            while (z != D && i <= (len - 1) / 2) {
                ok[z] = 0;
                z     = dec.parent(z);
                i++;
            }
        }
        dfs1(t.get_root(), t, ok);
    }

    {
        Tree<> t(g, O);

        // 奇数距離の場合
        // o-d-.:o-.-d:.-o-d: dから近づく

        // 偶数距離の場合
        // o-.d-.:o-.-.-d:.-o-.-d:
        // 結局葉の手前
        dfs2(t.get_root(), t, ok);
    }
    cout << ret << endl;
    return 0;
}