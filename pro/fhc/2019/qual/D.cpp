//
/*<head>*/
// #include "Template.hpp"
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
/* #endregion */
/*</body>*/

int N, M;
int X[255];
int Y[255];
int Z[255];
int P[255];

void input() {
    cin >> N >> M;
    for (int i : range(M)) {
        cin >> X[i] >> Y[i] >> Z[i];
        X[i]--;
        Y[i]--;
        Z[i]--;
    }
}

class UF {
  private:
    vector<int> par, rank;

  public:
    int find(int x) {
        if (par[x] == x)
            return x;
        else
            return par[x] = find(par[x]);
    }
    UF(int n) : par(n), rank(n) {
        for (int i = 0; i < n; i++) {
            par[i] = i, rank[i] = 0;
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


using bs            = bitset<64>;
using hash_key_type = unsigned long long;
using V             = vector<int>;
unordered_map<hash_key_type, int> memo;

string get_vs(bs b) {
    vector<int> v;
    for (int i : range(N)) {
        if (b[i]) v.push_back(i);
    }
    if (v.size() == 0) return "";
    string ans;
    ans += "(";
    for (auto x : v) {
        ans += to_string(x + 1) + ",";
    }
    ans += "),";
    return ans;
}
void print(bs from, int root, array<bs, 64> s) {
    cerr << get_vs(from);
    cerr << " -> ";
    cerr << "{root = " << root + 1;
    cerr << " , s= {";
    for (int i : range(N)) cerr << get_vs(s[i]);
    cerr << "} }";
    cerr << endl;
}
bool split(int root, bs vst, array<bs, 64>& result) {
    vst[root] = false;
    UF uf(N);
    for (int i : range(M)) {
        if (vst[Z[i]]) {
            if (Z[i] != root) {
                if (X[i] == root || Y[i] == root) {
                    return false;
                }
            }
            uf.unite(X[i], Z[i]);
            uf.unite(Y[i], Z[i]);
        }
    }
    for (int i : range(M)) {
        if (Z[i] == root) {
            if (uf.same(X[i], Y[i])) return false;
        }
    }
    for (int i : range(N)) {
        if (vst[i]) {
            result[uf.find(i)][i] = true;
        }
    }
    return true;
}
int dfs(bs vst) {
    if (vst.count() <= 1) {
        return memo[vst.to_ullong()] = vst._Find_first();
    }
    if (memo.count(vst.to_ullong())) return memo[vst.to_ullong()];
    for (int i = vst._Find_first(); i < (int)vst.size();
         i     = vst._Find_next(i)) {
        array<bs, 64> s;
        bool ok = split(i, vst, s);
        if (ok == false) continue;
        for (int i : range(N)) {
            if (dfs(s[i]) == -1) {
                ok = false;
                break;
            }
        }
        if (ok == false) continue;
        return memo[vst.to_ullong()] = i;
    }
    return memo[vst.to_ullong()] = -1;
}

int set_answer(bs vst) {
    auto verticies = vst.to_ullong();
    if (verticies == 0) return N;
    array<bs, 64> s;
    int root = memo[verticies];
    split(root, vst, s);
    // print(vst, root, s);
    for (int i : range(N)) {
        int j = set_answer(s[i]);
        P[j]  = root;
    }
    return root;
}

void solve() {
    memo.clear();
    input();
    fill(P, P + N, -1);
    bs x((1llu << N) - 1);
    int root = dfs(x);
    // cerr << root + 1 << endl;
    if (root == -1) {
        cout << "Impossible" << endl;
    }
    else {
        set_answer(x.to_ullong());
        string sp(N, ' ');
        sp.back() = '\n';
        for (int i : range(N)) {
            cout << P[i] + 1 << sp[i];
        }
    }
}
int main() {
    int T;
    cin >> T;
    for (int i : range(T)) {
        cout << "Case #" << i + 1 << ": ";
        solve();
        cout.flush();
    }
    return 0;
}