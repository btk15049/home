//https://atcoder.jp/contests/dp/tasks/dp_v
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

int N,M;
vector<int> g[112345];
LL ret[112345];
vector<LL> LtoR[112345];
vector<LL> RtoL[112345];
void dfs(int v,int p){
    LtoR[v].resize(g[v].size()+2);
    RtoL[v].resize(g[v].size()+2);
    LtoR[v].front()=1;
    RtoL[v].back()=1;

    for(int u:g[v]){
        if(u==p)continue;
        dfs(u,v);
    }
    for(int e:range(g[v].size())){
        int u = g[v][e];
        LtoR[v][e+1]=LtoR[v][e];
        if(u==p)continue;
        LtoR[v][e+1]*=(LtoR[u].back()+1);
        LtoR[v][e+1]%=M;
    }
    for(int re:range(g[v].size())){
        int e=g[v].size()-re-1;
        int u = g[v][e];
        RtoL[v][e+1]=RtoL[v][e+2];
        if(u==p)continue;
        RtoL[v][e+1]*=(LtoR[u].back()+1);
        RtoL[v][e+1]%=M;
    }
    LtoR[v].back()=RtoL[v].front()=RtoL[v][1];
}
void solve(int v,int p,LL k){
    ret[v]=k*LtoR[v].back()%M;
    //cout<<v<<" "<<k<<endl;
    for(int e:range(g[v].size())){
        int u = g[v][e];
        if(u==p)continue;
        LL x = LtoR[v][e]*RtoL[v][e+2]%M;
        solve(u,v,(k*x+1)%M);
    }

}
int main(){
    cin>>N>>M;
    for(int i:range(N-1)){
        int a,b;
        cin>>a>>b;
        a--;b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs(0,0);
    solve(0,0,1);
    for(int i:range(N)){
        cout<<ret[i]<<endl;
    }
    //cout<<RtoL[0][2]<<endl;
    return 0;
}