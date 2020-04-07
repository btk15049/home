// https://atcoder.jp/contests/agc033/tasks/agc033_a
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
int R, C;
int hop[1123][1123];
struct P {
    int r, c;
};
int main() {
    queue<P> que;
    cin >> R >> C;
    for (int i : range(R + 2)) {
        for (int j : range(C + 2)) {
            hop[i][j] = 0;
        }
    }
    for (int i : range(R)) {
        string s;
        cin >> s;
        for (int j : range(C)) {
            if (s[j] == '.') {
                hop[i + 1][j + 1] = 2123;
            }
            else {
                que.push(P{i + 1, j + 1});
            }
        }
    }
    const int dr[4] = {0, 1, 0, -1};
    const int dc[4] = {1, 0, -1, 0};

    int ret = 0;
    while (que.size()) {
        P p = que.front();
        que.pop();
        for (int i : range(4)) {
            P q = {p.r + dr[i], p.c + dc[i]};
            if (chmin(hop[q.r][q.c], hop[p.r][p.c] + 1)) {
                que.push(q);
            }
        }
    }
    for (int i : range(1, R + 1)) {
        for (int j : range(1, C + 1)) {
            chmax(ret, hop[i][j]);
        }
    }
    cout << ret << endl;

    return 0;
}