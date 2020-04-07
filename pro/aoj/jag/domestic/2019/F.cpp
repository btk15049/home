#include <bits/stdc++.h>

using namespace std;

#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define ALL(v) begin(v)

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

constexpr int base = 90001;
constexpr int mod  = 999999937;

class RollingHash {
  public:
    LL hash;
    LL potential;
    using RH = RollingHash;
    RollingHash(LL hash = 0, LL potential = 0)
        : hash(hash % mod), potential(potential) {}

    inline RH operator+(const RH o) const {
        return RH((hash * o.potential + o.hash) % mod,
                  potential * o.potential % mod);
    }


    inline RH operator*(LL n) const {
        RH ret;
        RH a(this->hash, this->potential);
        while (n) {
            if (n & 1) ret = ret + a;
            a = a + a;
            n >>= 1;
        }
        return ret;
    }

    inline bool operator==(const RH o) const {
        return hash == o.hash && potential == o.potential;
    }

    class Table {
      private:
        vector<RH> str;

      public:
        Table() {}
        Table(const string s) {
            const int n = s.size();
            str.resize(n + 1);
            REP(i, n) { str[i + 1] = str[i] + RH(s[i], base); }
        }
        RH substr(int l, int r) {
            return RH(
                (str[r].hash - str[l].hash * str[r - l].potential % mod + mod)
                    % mod,
                str[r - l].potential);
        }
    };
};

string s;
string t;
int n;
int m;
bool input() {
    cin >> s;
    n = s.size();
    if (s == "#") return false;
    cin >> t;
    m = t.size();
    return true;
}

using V  = vector<int>;
using VV = vector<V>;
VV g;
vector<RollingHash> rh;
vector<LL> has;
RollingHash Q;

void reset() {
    g.clear();
    rh.clear();
    has.clear();
    Q = RollingHash::Table(t).substr(0, m);
}
int new_node() {
    int ret = g.size();
    g.push_back(V());
    rh.push_back(RollingHash());
    has.push_back(0ll);
    return ret;
}

bool is_next_gnm(int &idx) {
    return (idx < n && (isalpha(s[idx]) || isdigit(s[idx])));
}
void parse(int p, int &idx);
void gnm(int v, int &idx) {
    LL re = 0;
    while (idx < n && isdigit(s[idx])) {
        re *= 10;
        re += s[idx] - '0';
        idx++;
    }
    if (re == 0) re = 1;
    if (isalpha(s[idx])) {
        rh[v] = RollingHash::Table(string(1, s[idx])).substr(0, 1);
        idx++;
    }
    else if (s[idx] == '(') {
        idx++;
        parse(v, idx);
        assert(s[idx] == ')');
        idx++;
    }
    rh[v] = rh[v] * re;
}
void parse(int p, int &idx) {
    int pr = -1;
    while (is_next_gnm(idx)) {
        int child = new_node();
        g[p].push_back(child);
        gnm(child, idx);
        if (pr != -1) {
            //
        }
        rh[p] = rh[p] + rh[child];
        pr    = child;
    }
}

void solve() {
    reset();
    int idx = 0;
    parse(new_node(), idx);
}
int main() {
    while (input()) {
        solve();
    }
}
