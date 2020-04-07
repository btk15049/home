// https://atcoder.jp/contests/agc006/tasks/agc006_a
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
        int operator*() {
            return x - 1;
        }
        bool operator!=(I& lhs) {
            return x > lhs.x;
        }
        void operator++() {
            --x;
        }
    };
    I i, n;

  public:
    reverse_range(int n) : i({0}), n({n}) {}
    reverse_range(int i, int n) : i({i}), n({n}) {}
    I& begin() {
        return n;
    }
    I& end() {
        return i;
    }
};
class range {
  private:
    struct I {
        int x;
        int operator*() {
            return x;
        }
        bool operator!=(I& lhs) {
            return x < lhs.x;
        }
        void operator++() {
            ++x;
        }
    };
    I i, n;

  public:
    range(int n) : i({0}), n({n}) {}
    range(int i, int n) : i({i}), n({n}) {}
    I& begin() {
        return i;
    }
    I& end() {
        return n;
    }
    reverse_range operator!() {
        return reverse_range(*i, *n);
    }
};
using LL = long long;

int main() {
    int N;
    string s, t;
    cin >> N >> s >> t;
    int S = s.size();
    int T = t.size();
    int ret = 200;
    for (int i : range(min(S, T) + 1)) {
        if (s.substr(S - i, i) == t.substr(0, i)) { chmin(ret, S + T - i); }
    }
    cout << ret << endl;
    return 0;
}