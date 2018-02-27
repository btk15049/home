#ifndef VS
#include<bits/stdc++.h>
using namespace std;
#endif

template<typename T>
vector<int> Zalgorithm(T S) {
    int sz = S.size();
    vector<int> ret(sz);
    ret[0] = sz;
    int i = 1, j = 0;
    while (i < sz) {
        while (i + j < sz && S[j] == S[i + j]) ++j;
        ret[i] = j;
        if (j == 0) { ++i; continue; }
        int k = 1;
        while (i + k < sz && k + ret[k] < j) ret[i + k] = ret[k], ++k;
        i += k; j -= k;
    }
    return ret;
}
