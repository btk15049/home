//https://atcoder.jp/contests/dp/tasks/dp_g
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
int dp[112345];
int id = 0;
int ord[112345];
int vis[112345];
void topo(int v){
    if(vis[v])return;
    vis[v]=1;
    for(int u:g[v]){
        topo(u);
    }
    ord[id]=v;
    id++;
}
int main(){
    cin>>N>>M;
    for(int i:range(M)){
        int a,b;
        cin>>a>>b;
        a--;b--;
        g[a].push_back(b);
    }
    for(int i:range(N))topo(i);
    reverse(ord,ord+N);
    for(int ii:range(N)){
        int v = ord[ii];
        for(int u:g[v])chmax(dp[u],dp[v]+1);
    }
    cout<<*max_element(dp,dp+N)<<endl;
    return 0;
}