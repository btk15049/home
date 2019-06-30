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
string s, t;
LL INSERT, ERASE, REPLACE, ROTATE;
bool input() {
    cin >> s;
    if (s == "#") return false;
    cin >> t;
    cin >> INSERT >> ERASE >> REPLACE >> ROTATE;
    chmin(REPLACE, INSERT + ERASE);
    chmin(ROTATE, INSERT + ERASE);

    return true;
}
constexpr LL INF = 1e15;

using V = vector<LL>;

int main() {
    while (input()) {
        const int n = s.size();
        const int m = t.size();

        LL ret = INF;
        REP(i, n) {
            LL cost = i * ROTATE;
            vector<V> dp(n + 1, V(m + 1, INF));
            dp[0][0] = 0;
            REP(j, n + 1) REP(k, m + 1) {
                if (j == 0 && k == 0) continue;
                if (j > 0) {
                    if (j - 1 >= n - i) {
                        chmin(dp[j][k], dp[j - 1][k] + ERASE - ROTATE);
                    }
                    else {
                        chmin(dp[j][k], dp[j - 1][k] + ERASE);
                    }
                }
                if (k > 0) {
                    chmin(dp[j][k], dp[j][k - 1] + INSERT);
                }
                if (j > 0 && k > 0) {
                    if (s[j - 1] == t[k - 1]) {
                        chmin(dp[j][k], dp[j - 1][k - 1]);
                    }
                    else {
                        if (j - 1 >= n - i) {
                            chmin(dp[j][k],
                                  dp[j - 1][k - 1]
                                      + min(REPLACE, ERASE + INSERT - ROTATE));
                        }
                        else {
                            chmin(dp[j][k], dp[j - 1][k - 1] + REPLACE);
                        }
                    }
                }
            }
            cost += dp[n][m];
            chmin(ret, cost);
            s = s.substr(1, n) + string(1, s[0]);
        }
        cout << ret << endl;
    }
}