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
constexpr int S = 312;
string s;
int n;

int dp[S][S][2][2];
int vis[S][S];
void init() {
    for (int i : range(n + 1)) {
        for (int j : range(n + 1)) {
            dp[i][j][0][0] = S;
            dp[i][j][0][1] = S;
            dp[i][j][1][0] = S;
            dp[i][j][1][1] = S;

            vis[i][j] = 0;
        }
    }
}
auto or_func  = [](int l, int r) { return l | r; };
auto and_func = [](int l, int r) { return l & r; };
auto xor_func = [](int l, int r) { return l ^ r; };

void rec(int l, int r) {
    if (vis[l][r]) return;
    vis[l][r] = 1;
    if (r - l < 1) return;
    if (r - l == 1) {
        chmin(dp[l][r][1][1], s[l] == '1' ? 0 : 1);
        chmin(dp[l][r][0][0], s[l] == '0' ? 0 : 1);
        chmin(dp[l][r][1][0], s[l] == 'x' ? 0 : 1);
        chmin(dp[l][r][0][1], s[l] == 'X' ? 0 : 1);
        return;
    }
    for (int m : range(l + 1, r - 1)) {
        rec(l + 1, m);
        rec(m + 1, r - 1);
        auto update = [&](char c, function<int(int, int)> f) {
            int cost = 0;
            cost += (s[l] == '(' ? 0 : 1);
            cost += (s[m] == c ? 0 : 1);
            cost += (s[r - 1] == ')' ? 0 : 1);
            for (int li : range(2)) {
                for (int ri : range(2)) {
                    for (int lj : range(2)) {
                        for (int rj : range(2)) {
                            chmin(dp[l][r][f(li, ri)][f(lj, rj)],
                                  dp[l + 1][m][li][lj]
                                      + dp[m + 1][r - 1][ri][rj] + cost);
                        }
                    }
                }
            }
        };
        update('&', and_func);
        update('|', or_func);
        update('^', xor_func);
    }
}
void solve() {
    cin >> s;
    n = s.size();
    init();
    rec(0, n);
    cout << min(dp[0][n][1][1], dp[0][n][0][0]) << endl;
    ;
}

int main() {
    int T;
    cin >> T;
    for (int i : range(T)) {
        cout << "Case #" << i + 1 << ": ";
        solve();
    }
    return 0;
}