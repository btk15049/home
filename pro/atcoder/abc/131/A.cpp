// https://atcoder.jp/contests/abc131/tasks/abc131_a
#define CIN_ONLY
#define DECIMAL_DIGITS 10

#ifdef BTK
/*<head>*/
#    include "Template.hpp"
/*</head>*/
#else
/*<body>*/
/*</body>*/
#endif

int main() {
    string s;
    cin >> s;
    string ret = "Good";
    for (int i : range(3))
        if (s[i] == s[i + 1]) ret = "Bad";
    cout << ret << endl;
    return 0;
}