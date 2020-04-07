// https://atcoder.jp/contests/agc034/tasks/agc034_c
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
int N;
LL X;
struct node {
    LL b;
    LL lb;
    LL ub;
    LL mx;
} input[112345];
LL mxs[112345];
LL MX(int l, int r) { return mxs[r] - mxs[l]; }
LL border = 0;
bool check(LL num) {
    LL ret     = 0;
    const LL K = num / X;
    const LL k = num % X;
    for (int i : range(K)) {
        LL ans = MX(0, K + 1) - MX(i, i + 1);
        if (k >= input[i].b) {
            ans += input[i].lb * input[i].b + input[i].ub * (k - input[i].b);
        }
        else {
            ans += input[i].lb * k;
        }
        chmax(ret, ans);
    }
    for (int i : range(K, N)) {
        LL ans = MX(0, K);
        if (k >= input[i].b) {
            ans += input[i].lb * input[i].b + input[i].ub * (k - input[i].b);
        }
        else {
            ans += input[i].lb * k;
        }
        chmax(ret, ans);
    }

    return ret >= border;
}
int main() {
    cin >> N >> X;
    LL ok = 0, ng = -1;
    for (int i : range(N)) {
        cin >> input[i].b >> input[i].lb >> input[i].ub;
        border += input[i].b * input[i].lb;
        ok += input[i].b;
        input[i].mx = input[i].b * input[i].lb + (X - input[i].b) * input[i].ub;
    }
    sort(input, input + N,
         [](const node& l, const node& r) { return l.mx > r.mx; });
    for (int i : range(N)) {
        mxs[i + 1] = mxs[i] + input[i].mx;
    }
    while (ok - ng > 1) {
        const LL md           = (ok + ng) / 2;
        (check(md) ? ok : ng) = md;
    }
    cout << ok << endl;
    return 0;
}