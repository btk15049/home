//http://codeforces.com/contest/1076/problem/E
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#ifdef BTK
#define DEBUG if(1)
#else
#define CIN_ONLY if(0)
struct cww {cww() {CIN_ONLY{ios::sync_with_stdio(false); cin.tie(0);}}}star;
#define DEBUG if(0)
#endif
#define ALL(v) (v).begin(),(v).end()
#define REC(ret, ...) std::function<ret (__VA_ARGS__)>
template <typename T>inline bool chmin(T &l, T r){bool a = l>r; if (a)l = r; return a;}
template <typename T>inline bool chmax(T &l, T r){bool a = l<r; if (a)l = r; return a;}
template <typename T>istream& operator>>(istream &is, vector<T> &v){for (auto &it : v)is >> it;return is;}
class range {private: struct I { int x; int operator*() { return x; }bool operator!=(I& lhs) { return x<lhs.x; }void operator++() { ++x; } }; I i, n;public:range(int n) :i({ 0 }), n({ n }) {}range(int i, int n) :i({ i }), n({ n }) {}I& begin() { return i; }I& end() { return n; }};
int n,m;
vector<int> g[312345];
vector<pair<int,int>> query[312345];
LL dep[312345];
LL sub[312345];
LL ret[321234];
void dfs(int v,int p,LL sum,int depth){
    for(auto it:query[v]){
        int d,x;
        tie(d,x)=it;
        sub[min(300010ll,depth+(LL)d)]+=x;
        sum+=x;
    }
    ret[v]=sum;
    for(int u:g[v]){
        if(u==p)continue;
        dfs(u,v,sum-sub[depth],depth+1);
    }
    for(auto it:query[v]){
        int d,x;
        tie(d,x)=it;
        sub[min(300010ll,depth+(LL)d)]-=x;
    }
}
int main(){
    scanf("%d",&n);
    for(int i:range(n-1)){
        int a,b;
        scanf("%d%d",&a,&b);
        g[a].push_back(b);
        g[b].push_back(a);
    }
    scanf("%d",&m);
    for(int i:range(m)){
        int v,d,x;
        scanf("%d%d%d",&v,&d,&x);
        query[v].push_back({d,x});
    }
    dfs(1,1,0,0);
    string s(n,' ');
    s.back()='\n';
    for(int i:range(n)){
        printf("%lld%c",ret[i+1],s[i]);
    }
    return 0;
}