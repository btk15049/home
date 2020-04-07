// https://atcoder.jp/contests/panasonic2020/tasks/panasonic2020_e
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

int ret;


vector<string> solve(string a, string b, string c) {
    vector<string> ab;
    int k = min(a.size(), b.size());
    for (int i : range(1, k + 1)) {
        bool ok  = true;
        string s = a.substr(0, a.size() - k);
        s.reserve(a.size() + b.size() - k);
        for (int j : range(k)) {
            int ai = a.size() - i + j;
            int bi = j;
            if (a[ai] == b[bi]) {
                s.push_back(a[ai]);
            }
            else if (a[ai] == '?') {
                s.push_back(b[bi]);
            }
            else if (b[bi] == '?') {
                s.push_back(a[ai]);
            }
            else {
                ok = false;
                break;
            }
        }
        if (ok == false) continue;
        s += b.substr(k);
        ab.push_back(s);
    }

    for (auto &_ab : ab) {
        string abc = _ab + c;
        auto Z     = Zalgorithm(abc);
        chmin(ret, abc.size()-)
    }
}
int main() {
    /* write here */
    string a, b, c;
    cin >> a >> b >> c;
    ret = a.size() + b.size() + c.size();


    cout << ret << endl;
    return 0;
}