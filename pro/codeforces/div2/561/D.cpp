// http://codeforces.com/contest/1166/problem/D
/*<head>*/
// #include "Template.hpp"
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

/* #endregion */
/*</body>*/
LL a, b, m;
LL C[64];
void CI() {
    C[0] = 1;
    C[1] = 1;
    for (int i : range(2, 64)) C[i] = C[i - 1] * 2;
}
constexpr LL INF = 1e18;
LL r[64];
bool solve_k(int k) {
    LL rest       = b;
    double rest_d = b;
    for (int i : !range(k - 1)) {
        rest -= C[i] * 1;
        rest_d -= C[i] * 1.0;
        r[k - 1 - i] = 1;
    }
    rest -= C[k - 1] * a;
    rest_d -= C[k - 1] * (double)a;
    r[0] = a;
    for (int i : !range(k - 1)) {
        if (rest_d < -INF) return false;
        LL rc = rest / C[i];
        chmin(rc, m - 1);
        chmax(rc, 0ll);
        rest -= C[i] * rc;
        rest_d -= C[i] * rc;
        r[k - 1 - i] += rc;
        if (rest_d < -INF) return false;
    }
    // 1r[0]
    // 1r[0]+1r[1]
    // 2r[0]+1r[1]+r[2]
    // 4r[0]+2r[1]+r[2]+r[3]
    if (rest == 0) {
        string sp(k + 1, ' ');
        sp.back() = '\n';
        cout << k << " ";
        for (int i : range(1, k + 1)) {
            LL x = 0;
            for (int j : range(i)) {
                x += r[j] * C[i - 1 - j];
            }
            cout << x << sp[i];
        }
        return true;
    }
    else {
        return false;
    }
}
void solve() {
    cin >> a >> b >> m;
    for (int k : range(1, 51)) {
        if (solve_k(k)) {
            return;
        }
    }
    cout << -1 << endl;
    return;
}
int main() {
    CI();
    int q;
    cin >> q;
    for (int qi : range(q)) {
        unused_var(qi);
        solve();
    }
    return 0;
}