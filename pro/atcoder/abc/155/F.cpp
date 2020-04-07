// https://atcoder.jp/contests/abc155/tasks/abc155_f
#define CIN_ONLY
#define DECIMAL_DIGITS 10
#define STATIC_MOD 1e9 + 7

#ifdef BTK
/*<head>*/
#    include "Template.hpp"
/*</head>*/
#else
/*<body>*/
/*</body>*/
#endif

pair<LL, int> AB[212345];
int L[212345];
int R[212345];
priority_queue<pair<int, int>, vector<int>, greater<int>> v[212345];


int main() {
    /* write here */
    int n, m;
    cin >> n >> m;
    for (int i : range(n)) {
        cin >> AB[i].first >> AB[i].second;
    }
    sort(AB, AB + n);
    for (int i : range(m)) {
        LL l, r;
        cin >> l >> r;
        L[i] = lower_bound(AB, AB + n, make_pair(l, -1)) - AB;
        R[i] = upper_bound(AB, AB + n, make_pair(r + 1, -1)) - AB;
        v[L[i]];
    }

    return 0;
}