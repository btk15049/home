//http://codeforces.com/contest/1029/problem/E
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
int n;
using V=vector<int>;
V g[212345];

LL allc_noself[212345];
LL allc_inself[212345];
LL putself[212345];
void dfs(int v,int p){
    putself[v]=1;
    allc_noself[v]=0;
    allc_inself[v]=n;
    for(int u:g[v]){
        if(u==p)continue;
        dfs(u,v);
        putself[v]+=allc_noself[u];
        allc_noself[v]+=allc_inself[u];
    }
    for(int u:g[v]){
        if(u==p)continue;
        chmin(allc_inself[v],allc_noself[v]-allc_inself[u]+putself[u]);
    }
    chmin(allc_inself[v],putself[v]);
    chmin(allc_noself[v],allc_inself[v]);

    DEBUG {
        cout<<v+1<<" ";
        cout<<allc_noself[v]<<" ";
        cout<<allc_inself[v]<<" ";
        cout<<putself[v]<<" ";
        cout<<endl;
    }
}
int main(){
    cin>>n;
    for(int i:range(n-1)){
        int a,b;
        cin>>a>>b;
        a--;
        b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    LL ret = 0;
    for(int u:g[0])for(int c:g[u]){
        if(c!=0)
        dfs(c,u);
        ret+=allc_noself[c];
    }
    cout<<ret<<endl;
    return 0;
}