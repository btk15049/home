#include<bits/stdc++.h>
using namespace std;
#define FOR(i,bg,ed) for(int i=(bg);i<(ed);i++)
#define REP(i,n) FOR(i,0,n)

namespace roll{
    using H = unsigned long long;
    constexpr H p[] = {1e9+9,1e9+7,90001};
    constexpr int MX = 212345;
    H hs[3][MX];
    H rh[3][MX];
    template<int m>
    void build(const string s){
        const int n = s.size();
        REP(i,m){
            hs[i][0] = 0;
            rh[i][0] = 1;
            REP(i,m)REP(j,n){
                hs[j+1] += hs[j]*p[i] + s[j];
                rh[j+1] =  rh[j]*p[i];
            }
        }
    }
    template<int m>
    H get(const int l,const int r){
        H ret = 0;
        REP(i,m)ret ^= hs[i][r] - hs[i][l] * rh[i][r-l];
        return ret;
    }
}
