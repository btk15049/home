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

typedef pair<int,int> P;
typedef vector<int> V;
typedef vector<V> VV;
VV g;
V X;
bool ret=true;
P dfs(int v,int p){
    V dp(5001,1e8);
    dp[0]=0;
    for(auto &u:g[v]){
        if(p==u)continue;
        V nxt(5001,1e8);
        auto child=dfs(u,v);
        FOR(i,child.fi,5001)
            chmin(nxt[i],dp[i-child.fi]+child.se);
        FOR(i,child.se,5001)
            chmin(nxt[i],dp[i-child.se]+child.fi);
        swap(dp,nxt);
        
    }
    FOR(i,1,5001)chmin(dp[i],dp[i-1]);
    if(dp[X[v]]==1e8)ret=false;
    return {X[v],dp[X[v]]};

}
int main(){
    int N;
    cin>>N;
    g.assign(N,V());
    X.assign(N,0);

    FOR(i,1,N){
        int p;
        cin>>p;
        p--;
        g[p].pb(i);
        g[i].pb(p);
    }
    cin>>X;
    dfs(0,0);
    if(ret)cout<<"POSSIBLE"<<endl;
    else cout<<"IMPOSSIBLE"<<endl;
    return 0;
}
