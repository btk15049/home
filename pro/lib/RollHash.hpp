#include<bits/stdc++.h>
using namespace std;
#define FOR(i,bg,ed) for(int i=(bg);i<(ed);i++)
#define REP(i,n) FOR(i,0,n)

namespace roll{
    using H = unsigned long long;
                     //0123456789
    constexpr H p[] = {1000000009,
                       1000000007,
                       90001};
    constexpr int MX = 1123456;
    H hs[3][MX];
    H rh[3][MX];
    template<int m = 1>
    void build(const string s){
        const int n = s.size();
        REP(i,m){
            hs[i][0] = 0;
            rh[i][0] = 1;
            REP(i,m)REP(j,n){
                hs[i][j+1] = hs[i][j]*p[i] + s[j];
                rh[i][j+1] = rh[i][j]*p[i];
            }
        }
    }
    template<int m = 1>
    H get(const int l,const int r){
        H ret = 0;
        REP(i,m){
            ret ^= hs[i][r] - hs[i][l] * rh[i][r-l];
        }
        return ret;
    }
}
