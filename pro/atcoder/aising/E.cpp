//https://atcoder.jp/contests/aising2019/tasks/aising2019_e
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

int N;
LL A[5123];
vector<int> g[5123];
vector<int> t[5123];
LL allB[5123][5123];
LL dp[5123][5123];
LL tmp[5123];
int sub[5123];
void dfs(int v,int p){
    sub[v]=1;
    for(int u:g[v]){
        if(u==p)continue;
        t[v].push_back(u);
        dfs(u,v);
        sub[v]+=sub[u];
    }
}
void solve(int v){
    for(int u:t[v]){
        solve(u);
    }
    int x=1;
    if(A[v]>0){
        allB[v][0]=1;
    }
    else{
        allB[v][0]=0;
    }
    dp[v][0]=A[v];
    for(int u:t[v]){
        const int nx=x+sub[u];
        for(int i:range(nx+1)){
            tmp[i]=0;
        }
        for(int i:range(x))for(int j:range(sub[u]+1)){
            tmp[i+j]|=(allB[v][i]&allB[u][j]);
        }
        for(int i:range(nx+1)){
            allB[v][i]=tmp[i];
            tmp[i]=1e18;
        }
        for(int i:range(x))for(int j:range(sub[u]+1)){
            chmin(tmp[i+j],dp[v][i]+dp[u][j]);
        }
        for(int i:range(nx+1)){
            dp[v][i]=tmp[i];
        }
        x=nx;
    }
    for(int i:range(x)){
        if(allB[v][i]||dp[v][i]<0){
            chmin(dp[v][i+1],0ll);
            allB[v][i+1]=1;
        }
    }
}
int main(){
    cin>>N;
    for(int i:range(N)){
        cin>>A[i+1];
    }
    for(int i:range(N-1)){
        int u,v;
        cin>>u>>v;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    dfs(1,1);
    solve(1);
    int ret=N-1;
    for(int i:range(N+1)){
        if(allB[1][i])chmin(ret,i);
        if(dp[1][i]<0)chmin(ret,i);
    }
    cout<<ret<<endl;
    return 0;
}