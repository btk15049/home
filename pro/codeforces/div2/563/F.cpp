// https://codeforces.cm/contest/1174/problem/F
/*<head>*/
// #include "HeavyLightDecomposition.hpp"
/*</head>*/

/*<body>*/
/* #region header */
/* #region 1*/
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
/* #endregion */
/* #region 2*/

/**
 * @file Buffer.hpp
 * @brief メモリ管理クラス
 * @author btk15049
 * @date 2019/03/11
 * @details 
 */
namespace _Buffer_ {
    /**
     * @brief
     * バッファは基本的にこれを継承する
     * @tparam T
     */
    template <typename T>
    class BufferManager {
      protected:
        T* buf;

      public:
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

    template <typename T>
    class DisposableBufferManager : public BufferManager<T> {
      private:
        int ptr;

      public:
        DisposableBufferManager(T* buf) : BufferManager<T>(buf), ptr(0){};

        T* pop(int size) {
            ptr += size;
            return this->buf + ptr - size;
        }

        void push(T* p) {}

        void clear() { ptr = 0; }
    };

    /**
     * @brief
     * blocks*block_size分の領域をblocks個に区切って、やりくりする。
     * 使わなくなったらpopで返すのを忘れずに
     * @tparam T
     */
    template <typename T>
    class BlockBufferManager : public BufferManager<T> {
      private:
        std::queue<T*> que;

      public:
        BlockBufferManager(T* buf, int blocks, int block_size)
            : BufferManager<T>(buf) {
            for (int i : range(blocks)) {
                que.push(this->buf + i * block_size);
            }
        };

        T* pop(int size = 0) {
            T* ptr = que.front();
            que.pop();
            return ptr;
        }

        void push(T* p) { que.push(p); }

        void clear() {}
    };

} // namespace _Buffer_
using namespace _Buffer_;

/**
 * @brief
 * [var_name]という名前のBlockBufferManagerを生成する
 * type型で、大きさ　block_size の領域をblocks分生成
 */
#define BlockBuffer(type, blocks, block_size, var_name) \
    type var_name##_mem[(blocks) * (block_size)];       \
    BlockBufferManager<type> var_name(var_name##_mem, (blocks), (block_size));
/* #endregion */
/* #region 3*/

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
/* #endregion */
/* #region 4*/

/**
 * @file Tree.hpp
 * @brief 根付き森と根付き木
 * @author btk15049
 * @date 2019/05/07
 * @details 
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
/* #region 5*/
/**
 * @file HeavyLightDecomposition.hpp
 * @author btk
 * @brief 重軽分解
 * @version 0.1
 * @date 2019-06-04
 *
 */


namespace _HeavyLightDecomposition_ {
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

        void compute_subtrees(int v, vector<int>& sub, Forest<E>& f) {
            sub[v]++;
            for (int u : f.Ns(v)) {
                compute_subtrees(u, sub, f);
                sub[v] += sub[u];
            }
        }

        void coloring(int v, vector<int>& sub, Forest<E>& f, int& seg_id,
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
                col_id++;
            }
            for (int i : range(f.degree(v))) {
                if (top == i) continue;
                const int u = f.i2e(f[v][i]).versus(v);
                par[u]      = v;
                coloring(u, sub, f, seg_id, col_id);
                col_id++;
            }
            col_root[col_id] = seg_id;
        }


      public:
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
            while (col[v] != col[u]) {
                if (col[v] > col[u]) swap(v, u);
                u = par[i2v[col_root[col[u]]]];
            }
            return i2v[min(v2i[v], v2i[u])];
        }

        HeavyLightDecomposition(Forest<E>& f, BufferManager<int>& lender)
            : lender(lender) {
            const int n = f.size();
            col         = lender.pop(n + 10);
            v2i         = lender.pop(n + 10);
            i2v         = lender.pop(n + 10);
            col_root    = lender.pop(n + 10);
            par         = lender.pop(n + 10);

            int col_id = 0;
            int seg_id = 0;
            vector<int> sub(n, 0);
            for (int r : f.get_roots()) {
                compute_subtrees(r, sub, f);
                par[r] = super_root;
                coloring(r, sub, f, seg_id, col_id);
            }
        }

        inline int get_color(int v) const { return col[v]; }

        inline int get_id(const int v) const { return v2i[v]; }

        inline int get_vertex(const int id) const { return i2v[id]; }
    };
} // namespace _HeavyLightDecomposition_
using namespace _HeavyLightDecomposition_;
/* #endregion */
/* #endregion */
/*</body>*/

BlockBuffer(int, 5, 212345, bb);

void output(int v) {
    cout << "! " << v + 1 << endl;
    cout.flush();
    exit(0);
}
int D(int v) {
    cout << "d " << v + 1 << endl;
    cout.flush();
    int d;
    cin >> d;
    if (d == 0) {
        output(v);
    }
    if (d == 1) {
        cout << "s " << v + 1 << endl;
        cout.flush();
        cin >> v;
        v--;
        output(v);
    }

    return d;
}
int S(int v) {
    cout << "s " << v + 1 << endl;
    cout.flush();
    cin >> v;
    return v - 1;
}

int main() {
    int N;
    cin >> N;
    Graph<> g(N, N - 1);
    for (int i : range(N - 1)) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        g.add_edge(a, b);
    }
    Tree<> t(g);
    HeavyLightDecomposition<Edge> hld(t, bb);
    int v   = 0;
    int len = D(v);
    for (int loop : range(20)) {
        assert(loop <= 18);
        if (len == 0) output(v);

        int u;
        int expected_len;
        {
            int lb = 0, ub = len + 1;
            while (ub - lb > 1) {
                const int mid = (lb + ub) / 2;
                int target_id = hld.get_id(v) + mid;
                if (target_id < N
                    && hld.get_color(v)
                           == hld.get_color(hld.get_vertex(target_id))) {
                    lb = mid;
                }
                else {
                    ub = mid;
                }
            }
            chmin(lb, len);

            u            = hld.get_vertex(hld.get_id(v) + lb);
            expected_len = lb;
        }
        int ans      = D(u);
        int downword = (len + expected_len - ans) / 2;
        if (downword > 0) {
            v = hld.get_vertex(hld.get_id(v) + downword);
        }
        v = S(v);
        len -= downword + 1;
    }
    return 0;
}

// expected_len = a+b;
// len = a+c;
// ans = b+c;

// b = expected_len - a
// c = len - a
// ans = len+expected_len - 2a
// a = (len+expected_len-ans)/2