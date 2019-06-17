//https://atcoder.jp/contests/dp/tasks/dp_j
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

int cnt[4];
int N;

using V=vector<double>;
using VV=vector<V>;
using VVV=vector<VV>;
using Vb=vector<int>;
using VVb=vector<V>;
using VVVb=vector<VV>;
double solve(int i,int j,int k,VVV&dp,VVVb&vis){
    if(vis[i][j][k])return dp[i][j][k];
    vis[i][j][k]=true;
                    double d=0;
                //E=(a*A+b*B+c*C)/(1-d)
                if(i>0){
                    double a=i/(N+0.0);
                    dp[i][j][k]+=a*solve(i-1,j+1,k,dp,vis);
                    d+=a;
                }
                if(j>0){
                    double a=j/(N+0.0);
                    dp[i][j][k]+=a*solve(i,j-1,k+1,dp,vis);
                    d+=a;
                }
                if(k>0){
                    double a=k/(N+0.0);
                    dp[i][j][k]+=a*solve(i,j,k-1,dp,vis);
                    d+=a;
                }
                //cout<<i<<j<<k<<d<<" "<<dp[i][j][k]<<endl;
                if(i+j+k>0){
                    dp[i][j][k]++;
                    dp[i][j][k]/=d;
                }

    return dp[i][j][k];
}
int main(){
    cin>>N;
    for(int i:range(N)){
        int a;
        cin>>a;
        cnt[a]++;
    }

    VVV dp(N+1,VV(N+1,V(N+1)));
    VVVb vis(N+1,VV(N+1,V(N+1)));

    cout<<fixed;
    cout<<setprecision(10);
    cout<<solve(cnt[3],cnt[2],cnt[1],dp,vis)<<endl;
    return 0;
}