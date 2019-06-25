// https://atcoder.jp/contests/diverta2019-2/tasks/diverta2019_2_f
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

namespace xorshift {
    unsigned yy = 143132322;
    inline unsigned rand() {
        yy        = yy ^ (yy << 13);
        yy        = yy ^ (yy >> 17);
        return yy = yy ^ (yy << 5);
    }
    inline unsigned randInt() { return rand(); }
} // namespace xorshift

LL w[11][11];
int N;
int calc() {
    unordered_map<LL, int> cnt;
    vector<int> o(N);
    iota(ALL(o), 0);
    int c = 0;
    LL mx = 0;
    do {
        LL k = 0;
        for (int i : range(N - 1)) {
            k += w[o[i]][o[i + 1]];
        }
        cnt[k]++;
        if (cnt[k] >= 3) {
            c++;
        }
        chmax(mx, k);
    } while (next_permutation(ALL(o)));
    cerr << c << " " << mx << endl;
    return c;
}
LL magic_number[] = {1, 2, 4, 7, 12, 20, 29, 38, 52};
LL magic_sum[]    = {2, 4, 5, 12, 20, 33, 50, 68, 81};
int main() {
    cin >> N;
    LL bottom = 1;
    for (int i : range(1, N)) {
        for (int j : range(i)) {
            w[i][j] = w[j][i] = bottom * magic_number[j];
        }
        bottom *= magic_sum[i - 1];
    }
    // int cur = calc();
    for (int i : range(N)) {
        for (int j : range(N)) {
            cout << w[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}