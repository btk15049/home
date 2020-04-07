// https://atcoder.jp/contests/abc130/tasks/abc130_f
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
int N;
constexpr int S = 112345;
LL x[S], y[S];
int d[S];
int dx[S];
int dy[S];
constexpr LL INF = 1e18;
LL lbx(LL sec) {
    LL ret = INF;
    for (int i : range(N)) {
        chmin(ret, x[i] + sec * dx[d[i]]);
    }
    return ret;
}
LL ubx(LL sec) {
    LL ret = -INF;
    for (int i : range(N)) {
        chmax(ret, x[i] + sec * dx[d[i]]);
    }
    return ret;
}
LL lby(LL sec) {
    LL ret = INF;
    for (int i : range(N)) {
        chmin(ret, y[i] + sec * dy[d[i]]);
    }
    return ret;
}
LL uby(LL sec) {
    LL ret = -INF;
    for (int i : range(N)) {
        chmax(ret, y[i] + sec * dy[d[i]]);
    }
    return ret;
}

int main() {
    cin >> N;
    dx['R'] = dy['U'] = 1;
    dx['L'] = dy['D'] = -1;
    for (int i : range(N)) {
        string s;
        cin >> x[i] >> y[i] >> s;
        x[i] *= 2;
        y[i] *= 2;
        d[i] = s[0];
    }
    vector<LL> X, Y;
    X.push_back(0);
    Y.push_back(0);
    vector<LL> diff = {-2ll, -1ll, 0ll, 1ll, 2ll};
    for (auto df : diff) {
        LL lb = X.back() - 1;
        LL ub = 1e9;
        while (ub - lb > 1) {
            const LL md             = (lb + ub) / 2;
            const LL p              = ubx(md) - lbx(md);
            const LL q              = ubx(md + 1) - lbx(md + 1);
            (q - p == df ? lb : ub) = md;
        }
        X.push_back(ub);
    }

    for (auto df : diff) {
        LL lb = Y.back() - 1;
        LL ub = 1e9;
        while (ub - lb > 1) {
            const LL md             = (lb + ub) / 2;
            const LL p              = uby(md) - lby(md);
            const LL q              = uby(md + 1) - lby(md + 1);
            (q - p == df ? lb : ub) = md;
        }
        Y.push_back(ub);
    }
    X.push_back(1e9);
    Y.push_back(1e9);
    // for (auto xx : X) cerr << xx << " ";
    // cerr << endl;
    // for (auto xx : Y) cerr << xx << " ";
    // cerr << endl;

    double ret = INF;
    for (int i : range(5)) {
        for (int j : range(5)) {
            LL bg = max(X[i], Y[j]);
            LL ed = min(X[i + 1], Y[j + 1]);
            LL xb = ubx(bg) - lbx(bg);
            LL yb = uby(bg) - lby(bg);
            LL xe = ubx(ed) - lbx(ed);
            LL ye = uby(ed) - lby(ed);

            chmin(ret, xb * 1.0 * yb);
            chmin(ret, xe * 1.0 * ye);
        }
    }

    cout << fixed;
    cout << setprecision(10);
    cout << ret / 4 << endl;

    return 0;
}