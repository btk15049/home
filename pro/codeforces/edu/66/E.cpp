// http://codeforces.com/contest/1175/problem/E
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
#    define CIN_ONLY if (0)
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
constexpr int sz = 212345;
int N, Q;
int li[sz];
int ri[sz];
int lq[sz];
int rq[sz];
const int MX = 20;
int nx[MX][sz];
int ret[sz];
void doubling() {
    for (int d : range(MX - 1)) {
        for (int i : range(N)) {
            if (nx[d][i] != -1) {
                nx[d + 1][i] = nx[d][nx[d][i]];
            }
            else {
                nx[d + 1][i] = -1;
            }
        }
    }
}
void input() {
    scanf("%d%d", &N, &Q);
    for (int i : range(N)) {
        scanf("%d%d", li + i, ri + i);
        ri[i]++;
    }
    for (int i : range(Q)) {
        scanf("%d%d", lq + i, rq + i);
        rq[i]++;
    }
}
int calc(int v, int d, int ub) {
    // cerr << v << " " << d << " " << ub << " " << ri[v] << endl;
    if (ub <= ri[v]) return 0;
    while (d >= 0 && nx[d][v] == -1) d--;
    if (d == -1) return -1e7;
    if (d > 0 && ri[nx[d][v]] >= ub) {
        d--;
    }
    return (1 << d) + calc(nx[d][v], d, ub);
}

int main() {
    input();
    {
        vector<int> o(N);
        iota(ALL(o), 0);
        sort(ALL(o), [&](int l, int r) { return li[l] < li[r]; });
        set<pair<int, int>> s;
        for (int i : o) {
            while (s.size()) {
                const int f = s.begin()->second;
                const int b = s.rbegin()->second;
                if (ri[f] <= li[i]) {
                    if (ri[f] < ri[b]) {
                        nx[0][f] = b;
                    }
                    else {
                        nx[0][f] = -1;
                    }
                    s.erase({ri[f], f});
                }
                else {
                    break;
                }
            }
            s.insert({ri[i], i});
        }
        while (s.size()) {
            const int f = s.begin()->second;
            const int b = s.rbegin()->second;
            if (ri[f] < ri[b]) {
                nx[0][f] = b;
            }
            else {
                nx[0][f] = -1;
            }
            s.erase({ri[f], f});
        }
    }
    doubling();
    {
        vector<int> oi(N);
        iota(ALL(oi), 0);
        sort(ALL(oi), [&](int l, int r) { return li[l] < li[r]; });
        set<pair<int, int>> s;
        vector<int> oq(Q);
        iota(ALL(oq), 0);
        sort(ALL(oq), [&](int l, int r) { return lq[l] < lq[r]; });

        int i = 0;
        for (int q : oq) {
            while (i < N) {
                if (li[oi[i]] <= lq[q]) {
                    s.insert({ri[oi[i]], oi[i]});
                    i++;
                }
                else {
                    break;
                }
            }

            while (s.size()) {
                const int f = s.begin()->second;
                if (ri[f] <= lq[q]) {
                    s.erase({ri[f], f});
                }
                else {
                    break;
                }
            }

            if (s.size()) {
                // cerr << s.rbegin()->second << endl;
                ret[q] = 1 + calc(s.rbegin()->second, MX - 1, rq[q]);
                chmax(ret[q], -1);
            }
            else {
                ret[q] = -1;
            }
        }
    }
    for (int q : range(Q)) printf("%d\n", ret[q]);
    return 0;
}
