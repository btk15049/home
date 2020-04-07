// https://atcoder.jp/contests/agc006/tasks/agc006_c
/*<head>*/
// #include "Template.cpp"
/*</head>*/
/*<body>*/
/* #region header */
/**
 * @file template.cpp
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
#define ALL(v) (v).begin(), (v).end()
#define REC(ret, ...) std::function<ret(__VA_ARGS__)>
/* #endregion */

namespace _Template_ {
    struct cww {
        cww() {
            CIN_ONLY {
                ios::sync_with_stdio(false);
                cin.tie(0);
            }
        }
    } star;
    template <typename T>
    inline bool chmin(T& l, T r) {
        bool a = l > r;
        if (a) l = r;
        return a;
    }
    template <typename T>
    inline bool chmax(T& l, T r) {
        bool a = l < r;
        if (a) l = r;
        return a;
    }
    template <typename T>
    istream& operator>>(istream& is, vector<T>& v) {
        for (auto& it : v) is >> it;
        return is;
    }
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
int M;
LL x[112345];
LL K;
int as[64][112345];
int pos[112345];
int nps[112345];
LL dff[112345];
int main() {
    cout << fixed;
    cout << setprecision(10);
    cin >> N;
    for (int i : range(N)) {
        cin >> x[i];
    }
    cin >> M >> K;
    for (int i : range(N - 1)) {
        as[0][i] = i;
        pos[i]   = i;
    }
    for (int i : range(M)) {
        unused_var(i);
        int a;
        cin >> a;
        swap(as[0][a - 1], as[0][a - 2]);
    }
    for (int i : range(63)) {
        for (int j : range(N - 1)) {
            as[i + 1][j] = as[i][as[i][j]];
        }
    }
    int b = 0;
    while (K) {
        if (K & 1) {
            for (int i : range(N - 1)) {
                nps[i] = as[b][pos[i]];
            }
            for (int i : range(N - 1)) {
                pos[i] = nps[i];
            }
        }
        b++;
        K = K >> 1;
    }
    dff[0] = x[0];
    for (int i : range(N - 1)) {
        const int id = pos[i];
        // cerr << id << endl;
        dff[i + 1] = x[id + 1] - x[id] + dff[i];
    }
    for (int i : range(N)) {
        cout << dff[i] << endl;
    }
    return 0;
}