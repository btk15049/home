// https://atcoder.jp/contests/abc130/tasks/abc130_d
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
//[1,n],0は扱えない!
namespace BIT_ {
    using RET         = int;
    constexpr int BUF = 1123456;
    int ptr           = 0;
    RET t[BUF];
    inline RET* get(const int size) {
        ptr += size;
        return t + ptr - size;
    }
} // namespace BIT_
struct BIT {
    using T = BIT_::RET;
    T* bit;
    int sz;
    BIT(int n) : bit(BIT_::get(n + 10)), sz(n) { fill(bit, bit + n + 10, 0); }
    T sum(int i) {
        T s = 0;
        while (i > 0) {
            s += bit[i];
            i -= i & -i;
        }
        return s;
    }
    T sum(int lb, int ub) { return sum(ub) - sum(lb - 1); }
    void add(int i, T x) {
        while (i <= sz) {
            bit[i] += x;
            i += i & -i;
        }
    }
    // v[1]+v[2]+...+v[x]>=wとなる最小のxを求める
    int lowerbound(T w) {
        if (w <= 0) return 0;
        int x = 0;
        for (int k = (1 << (31 - __builtin_clz(sz))); k > 0; k >>= 1)
            if (x + k <= sz && bit[x + k] < w) {
                w -= bit[x + k];
                x += k;
            }
        return x + 1;
    }
};
int N;
LL K;
LL A[212345];
LL AS[212345];
LL latte[212345];
int malta = 0;
int main() {
    cin >> N >> K;
    for (int i : range(N)) cin >> A[i];
    for (int i : range(N)) AS[i + 1] = AS[i] + A[i];
    for (int i : range(N + 1)) latte[malta++] = AS[i];
    sort(latte, latte + malta);
    malta = unique(latte, latte + malta) - latte;
    BIT bit(N + 10);
    bit.add(1, 1);
    LL ret = 0;
    for (int i : range(N)) {
        LL X  = AS[i + 1] - K;
        int p = upper_bound(latte, latte + malta, X) - latte;
        int q = lower_bound(latte, latte + malta, AS[i + 1]) - latte + 1;
        ret += bit.sum(p);
        bit.add(q, 1);
    }
    cout << ret << endl;

    return 0;
}