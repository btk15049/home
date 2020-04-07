// https://atcoder.jp/contests/abc024/tasks/abc024_c
/*<head>*/
// #include "Template.cpp"
/*</head>*/

/*<body>*/
/* #region header */
/**
 * @file template.cpp
 * @brief 競技プログラミング用テンプレート
 * @author btk15049
 * @date 2019/03/08
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

LL N;
int D, K;
LL L[11234];
LL R[11234];
LL S[112];
LL T[112];
// L  lb,ub R
LL solve(int v) {
    LL lb = S[v], ub = S[v];
    for (int i : range(D)) {
        if (lb <= T[v] && T[v] <= ub) return i;
        if (lb <= R[i] && L[i] <= ub) {
            chmin(lb, L[i]);
            chmax(ub, R[i]);
        }
    }
    return D;
}

int main() {
    cin >> N >> D >> K;
    for (int i : range(D)) {
        cin >> L[i] >> R[i];
    }
    for (int i : range(K)) {
        cin >> S[i] >> T[i];
    }
    for (int i : range(K)) {
        cout << solve(i) << endl;
    }
    return 0;
}