//http://codeforces.com/contest/1006/problem/E
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

using V=vector<int>;
int n,q;
V g[212345];
int bg[212345];
int ed[212345];
int seq[212345];
int id = 0;
void dfs(int v,int p){
    seq[id] = v;
    bg[v]=id;
    id++;
    for(int u:g[v]){
        if(u==p)continue;
        dfs(u,v);
    }
    ed[v]=id;
}
int main(){
    cin>>n>>q;
    for(int i:range(1,n)){
        int p;
        cin>>p;p--;
        g[p].push_back(i);
        g[i].push_back(p);
    }
    for(int i:range(n)){
        sort(ALL(g[i]));
    }
    dfs(0,0);
    while(q--){
        int u,k;
        cin>>u>>k;
        u--;
        if(ed[u]-bg[u]<k){
            cout<<-1<<"\n";
        }
        else{
            cout<<seq[bg[u]+k-1]+1<<"\n";
        }
    }

    return 0;
}