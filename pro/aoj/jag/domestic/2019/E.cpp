#include <bits/stdc++.h>

using namespace std;

#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define ALL(v) begin(v), end(v)

using LL = long long;
template <typename T>
inline bool chmin(T &l, T r) {
    bool f = l > r;
    if (f) l = r;
    return f;
}
template <typename T>
inline bool chmax(T &l, T r) {
    bool f = l < r;
    if (f) l = r;
    return f;
}

int N, M;
using B = bitset<64>;
B g[41];
int a[1123][41];
bool input() {
    cin >> N >> M;
    if (N + M == 0) return false;
    REP(i, N) REP(j, M) { cin >> a[i][j]; }

    REP(i, M) g[i] = B();
    REP(i, N) REP(j, N) {
        if (i == j) continue;
        B X, Y;
        REP(k, M) {
            if (a[i][k] < a[j][k]) X[k] = true;
            if (a[i][k] > a[j][k]) Y[k] = true;
        }
        REP(k, M) {
            if (X[k]) g[k] = g[k] | Y;
            if (Y[k]) g[k] = g[k] | X;
        }
    }
    return true;
}
int dp[1 << 20];
int main() {
    while (input()) {
        int h   = M / 2;
        int r   = M - h;
        int ret = 0;

        REP(i, 1 << r) dp[i] = 0;
        REP(i, 1 << r) {
            B b(i);
            bool ok = true;
            REP(j, r) REP(k, r) {
                if (b[j] && b[k] && g[j + h][k + h]) ok = false;
            }
            if (ok) {
                chmax(dp[i], (int)b.count());
            }
            REP(j, r) { chmax(dp[i | (1 << j)], dp[i]); }
        }
        REP(i, 1 << h) {
            B b(i);
            bool ok = true;
            B mask((1 << r) - 1);
            REP(j, h) {
                if (b[j] == false) continue;
                REP(k, h) {
                    if (b[k] && g[j][k]) ok = false;
                }
                REP(k, r) if (g[j][k + h]) mask[k] = false;
            }
            if (ok) {
                chmax(ret, (int)b.count() + dp[mask.to_ulong()]);
            }
        }
        cout << ret << endl;
    }
}