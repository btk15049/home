#include<bits/stdc++.h>
using namespace std;
typedef long long LL;

#define CIN_ONLY if(1)
struct cww{cww(){
    CIN_ONLY{
        ios::sync_with_stdio(false);cin.tie(0);
    }
}}star;
#ifdef BTK
#include<dvector.h>
#define DEBUG if(1)
#else
#define DEBUG if(0)
#endif

#define fin "\n"
#define FOR(i,bg,ed) for(int i=(bg);i<(ed);i++)
#define REP(i,n) FOR(i,0,n)
#define ALL(v) (v).begin(),(v).end()
#define fi first
#define se second
#define pb push_back
#define REC(ret, ...) std::function<ret (__VA_ARGS__)>
template <typename T>inline bool chmin(T &l,T r)
{bool a=l>r;if(a)l=r;return a;}
template <typename T>inline bool chmax(T &l,T r)
{bool a=l<r;if(a)l=r;return a;}
template <typename T>
istream& operator>>(istream &is,vector<T> &v){
    for(auto &it:v)is>>it;
    return is;
}
typedef vector<LL> V;
typedef vector<V> VV;
constexpr LL INF=1e15;
int main(){
    int N,M,R;
    cin>>N>>M>>R;
    VV d(N,V(N,INF));
    V r(R);
    cin>>r;
    REP(i,R)r[i]--;
    REP(i,M){
        int a,b;LL c;
        cin>>a>>b>>c;
        a--;b--;
        chmin(d[a][b],c);
        chmin(d[b][a],c);

    }
    REP(i,N)d[i][i]=0;
    REP(k,N)REP(i,N)REP(j,N)
        chmin(d[i][j],d[i][k]+d[k][j]);
    VV dp(1<<R,V(R,INF));
    REP(i,R)dp[1<<i][i]=0;
    REP(i,(1<<R))REP(v,R){
        REP(j,R)
            chmin(dp[i|(1<<j)][j],dp[i][v]+d[r[v]][r[j]]);
    }
    LL ret=INF;
    REP(i,R)chmin(ret,dp.back()[i]);
    cout<<ret<<endl;
    return 0;
}
