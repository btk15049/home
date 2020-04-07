//http://codeforces.com/contest/1067/problem/A
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#ifdef BTK
#define DEBUG if(1)
#else
#define CIN_ONLY if(1)
struct cww {cww() {CIN_ONLY{ios::sync_with_stdio(false); cin.tie(0);}}}star;
#define DEBUG if(0)
#endif
#define ALL(v) (v).begin(),(v).end()
#define REC(ret, ...) std::function<ret (__VA_ARGS__)>
template <typename T>inline bool chmin(T &l, T r){bool a = l>r; if (a)l = r; return a;}
template <typename T>inline bool chmax(T &l, T r){bool a = l<r; if (a)l = r; return a;}
template <typename T>istream& operator>>(istream &is, vector<T> &v){for (auto &it : v)is >> it;return is;}
class range {private: struct I { int x; int operator*() { return x; }bool operator!=(I& lhs) { return x<lhs.x; }void operator++() { ++x; } }; I i, n;public:range(int n) :i({ 0 }), n({ n }) {}range(int i, int n) :i({ i }), n({ n }) {}I& begin() { return i; }I& end() { return n; }};

constexpr int mod = 998244353;
using V=vector<LL>;
using VV=vector<V>;
int a[312345];
int main(){
    int n;
    cin>>n;
    for(int i:range(n)){
        cin>>a[i];a[i]--;
    }
    V dp1(200,0);
    V dp2(200,0);
    if(a[0]==-2){
        dp1=V(200,1);
    }
    else{
        dp1[a[0]]=1;
    }
    for(int i:range(1,n)){
        V nxt1(200,0);
        V nxt2(200,0);
        V dp1_sum(201,0);
        V dp2_sum(201,0);
        for(int j:range(200)){
            dp1_sum[j+1]+=dp1_sum[j]+dp1[j];
            dp2_sum[j+1]+=dp2_sum[j]+dp2[j];
            if(dp1_sum[j+1]>=mod)dp1_sum[j+1]-=mod;
            if(dp2_sum[j+1]>=mod)dp2_sum[j+1]-=mod;
        }
        int lb = 0;
        int ub = 200;
        if(a[i]!=-2){
            lb=a[i];
            ub=a[i]+1;
        }
        for(int j:range(lb,ub)){
            LL dp1_lo = dp1_sum[j];
            LL dp1_same = dp1[j];
            LL dp1_hi = mod+dp1_sum.back()-dp1_sum[j+1];
            LL dp2_lo = dp2_sum[j];
            LL dp2_same = dp2[j];
            LL dp2_hi = mod+dp2_sum.back()-dp2_sum[j+1];
            nxt1[j]+=dp1_lo;
            nxt2[j]+=dp1_same;
            nxt1[j]+=dp2_lo;
            nxt2[j]+=dp2_same;
            nxt2[j]+=dp2_hi;
            nxt1[j]%=mod;
            nxt2[j]%=mod;
        }
        swap(dp1,nxt1);
        swap(dp2,nxt2);
    }
    LL ret = 0;
    for(int i:range(200))ret+=dp2[i];
    cout<<ret%mod<<endl;
    return 0;
}