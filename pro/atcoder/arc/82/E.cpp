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
#include <dvector.h>
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

int cross(int x1,int y1,int x2,int y2){
    return x1*y2-y1*x2;
}
const int mod=998244353;
int main(){
    int n;
    cin>>n;
    vector<int> x(n),y(n);
    REP(i,n)cin>>x[i]>>y[i];
    vector<int> line;
    vector<vector<int>> used(n,vector<int>(n,0));
    REP(i,n)used[i][i]=1;
    REP(i,n)REP(j,n)if(used[i][j]==0){
        vector<int> l;
        REP(k,n)
            if(cross(
                     x[i]-x[j],
                     y[i]-y[j],
                     x[i]-x[k],
                     y[i]-y[k]
                     )==0)
                l.pb(k);
        for(auto a:l)
            for(auto b:l)
                used[a][b]=1;
        line.pb(l.size());
    }
    LL ret=1;
    REP(i,n)ret=(ret+ret)%mod;
    ret+=mod-n-1;ret%=mod;
    for(auto &it:line){
        DEBUG cout<<it<<endl;
        LL s=1;
        REP(i,it)s=(s+s)%mod;
        s+=mod-it-1;s%=mod;
        ret+=mod-s;ret%=mod;   
    }
    cout<<ret<<endl;
    return 0;
}
