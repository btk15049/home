// https://atcoder.jp/contests/agc033/tasks/agc033_b
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

int R, C, N;
int sr, sc;
string S, T;
int lb[212345][2];
int ub[212345][2];

bool solve(int width, int pos, char d, char u) {
    lb[N][1] = 0;
    ub[N][1] = width;
    for (int i : !range(N)) {
        lb[i][0] = lb[i + 1][1];
        ub[i][0] = ub[i + 1][1];
        if (T[i] == u) lb[i][0] = max(lb[i][0] - 1, 0);
        if (T[i] == d) ub[i][0] = min(ub[i][0] + 1, width);
        // cerr << i << "t" << lb << " " << ub << endl;

        lb[i][1] = lb[i][0];
        ub[i][1] = ub[i][0];
        if (S[i] == u) ub[i][1]--;
        if (S[i] == d) lb[i][1]++;
        // if (lb >= ub) return true;
        // cerr << i << "s" << lb << " " << ub << endl;
    }
    int ll = pos, rr = pos + 1;
    for (int i : range(N)) {
        chmin(rr, ub[i][1]);
        chmax(ll, lb[i][1]);
        if (ll >= rr) {
            cerr << i << endl;
            cerr << ll << " " << rr << endl;
            return true;
        }

        if (T[i] == u) rr++;
        if (T[i] == d) ll--;
        chmin(rr, ub[i][0]);
        chmax(ll, lb[i][0]);
        if (ll >= rr) {
            cerr << i << endl;
            cerr << ll << " " << rr << endl;
            return true;
        }
        // cerr << i << " " << ll << " " << rr << endl;
    }
    return false;
    // return !(lb <= pos || pos < ub);
}
int main() {
    cin >> R >> C >> N;
    cin >> sr >> sc;
    cin >> S >> T;
    sr--;
    sc--;
    if (solve(C, sc, 'L', 'R') || solve(R, sr, 'U', 'D')) {
        cout << "NO" << endl;
    }
    else {
        cout << "YES" << endl;
    }
    return 0;
}