//http://codeforces.com/contest/1027/problem/E
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
using V  = vector<LL>;
using VV = vector<V>;
LL cnt[600];
int main(){
    int n,m;
    cin>>n>>m;
    VV dp(7,V(7));
    dp[1][1]=1;
    for(int i:range(1,n)){
        VV nxt(i+10,V(i+10));
        for(int j:range(i+5)){
            for(int k:range(i+5)){
                dp[j][k]%=mod;
                {
                    int nk = k+1;
                    int nj = max(nk,j);
                    nxt[nj][nk]+=dp[j][k];
                }
                nxt[j][1]+=dp[j][k];
            }
        }
        swap(dp,nxt);
    }
    for(int i:range(n+1))for(int j:range(n+1))cnt[i]+=dp[i][j]%mod;
    for(int i:range(n+1))cnt[i]%=mod;
    LL ret = 0;
    for(int i:range(1,n+1))for(int j:range(1,n+1)){
        if(i*j<m)ret+=cnt[i]*cnt[j]%mod;
    }
    cout<<ret*2%mod<<endl;
    return 0;
}