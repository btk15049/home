// https://atcoder.jp/contests/diverta2019/tasks/diverta2019_d
/*<head>*/
#include "Template.hpp"
/*</head>*/

/*<body>*/
/*</body>*/
LL N;


int main() {
    cin >> N;
    LL ret = 0;
    for (LL x : range(1, min(N, 1123456ll))) {
        LL lb = 1;
        LL ub = (N / x + 1);
        while (ub - lb > 1) {
            const LL m = (lb + ub) / 2;
            if (x * m + x <= N)
                lb = m;
            else
                ub = m;
        }
        if (N / lb == N % lb) ret += lb;
    }
    // N = mx + m
    // N = mx+m
    cout << ret << endl;
    return 0;
}