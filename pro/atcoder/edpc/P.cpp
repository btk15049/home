//https://atcoder.jp/contests/dp/tasks/dp_p
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
vector<int> g[112345];
LL dp[112345][2];
constexpr int mod = 1e9+7;
void dfs(int v,int p){
    LL allw = 0;
    dp[v][0]=1;
    dp[v][1]=1;
    for(int u:g[v]){
        if(u==p)continue;
        dfs(u,v);
        dp[v][1]*=dp[u][0];
        dp[v][0]*=(dp[u][0]+dp[u][1])%mod;
        dp[v][0]%=mod;
        dp[v][1]%=mod;
    }
}
int main(){
    cin>>N;
    for(int i:range(N-1)){
        int x,y;
        cin>>x>>y;
        x--;y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    dfs(0,0);
    cout<<(dp[0][0]+dp[0][1])%mod<<endl;
    return 0;
}