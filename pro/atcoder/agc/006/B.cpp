// https://atcoder.jp/contests/agc006/tasks/agc006_b
#include <bits/stdc++.h>
using namespace std;
#define TEMPLATE
#ifdef BTK
#define DEBUG if (1)
#else
#define CIN_ONLY if (1)
struct cww {
    cww() {
        CIN_ONLY {
            ios::sync_with_stdio(false);
            cin.tie(0);
        }
    }
} star;
#define DEBUG if (0)
#endif
#define ALL(v) (v).begin(), (v).end()
#define REC(ret, ...) std::function<ret(__VA_ARGS__)>
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
template <typename T>
inline T& unused_var(T& v) {
    return v;
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
using LL = long long;

int pos[212345];
int used[212345];
int main() {
    int N, x;
    cin >> N >> x;
    if (x == 1 || x == 2 * N - 1) {
        cout << "No" << endl;
        return 0;
    }
    else {
        cout << "Yes" << endl;
    }
    pos[N]      = x - 1;
    pos[N - 1]  = x;
    pos[N - 2]  = x + 1;
    used[x - 1] = used[x] = used[x + 1] = 1;
    if (N >= 3) {
        if (x == 2 * N - 2) {
            pos[N - 3]  = x - 2;
            used[x - 2] = 1;
        }
        else {
            pos[N + 1]  = x + 2;
            used[x + 2] = 1;
        }
    }
    int p = 0;
    for (int i : range(1, 2 * N)) {
        if (used[i]) continue;
        while (pos[p] != 0) p++;
        pos[p++] = i;
    }
    for (int i : range(2 * N - 1)) {
        cout << pos[i] << endl;
    }
    return 0;
}