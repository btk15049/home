//http://codeforces.com/contest/1076/problem/D
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
int n,m,k;
int x[312345];
int y[312345];
LL w[312345];
vector<int> g[312345];

LL d[312345];
int used[312345];
int ret[312345];
int sz=0;
void dfs(int v,int p=0){
    used[v]=1;
    for(int e:g[v]){
        int u=x[e]^y[e]^v;
        if(p==u)continue;
        if(d[v]+w[e]==d[u]&&used[u]==0){
            if(sz<k)ret[sz++]=e;
            dfs(u,v);
        }
    }
}
int main(){
    scanf("%d%d%d",&n,&m,&k);
    for(int i:range(m)){
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);a--;b--;
        x[i]=a;
        y[i]=b;
        w[i]=c;
        g[x[i]].push_back(i);
        g[y[i]].push_back(i);
    }
    priority_queue<pair<LL,int>> que;
    fill(d,d+n,1e17);
    d[0]=0;
    que.push({0,0});
    while(que.empty()==false){
        LL c;int v;
        tie(c,v)=que.top();que.pop();c=-c;
        if(d[v]<c)continue;
        for(int e:g[v]){
            int u=x[e]^y[e]^v;
            if(chmin(d[u],d[v]+w[e])){
                que.push({-d[u],u});
            }
        }
    }
    dfs(0);
    printf("%d\n",sz);
    //sort(ret,ret+sz);
    for(int i:range(sz)){
        printf("%d ",ret[i]+1);
    }
    printf("\n");
    return 0;
}