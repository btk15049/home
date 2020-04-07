//http://codeforces.com/contest/1037/problem/D
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
using VV=vector<V>;
VV g;
VV t;
void dfs(int v,int p){
    for(int u:g[v]){
        if(u==p)continue;
        dfs(u,v);
        t[v].push_back(u);
    }
}
int main(){
    cin>>n;
    g=VV(n);
    t=VV(n);
    for(int i:range(n-1)){
        int a,b;
        cin>>a>>b;
        a--;b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs(0,0);
    V q(n);
    cin>>q;
    for(int i:range(n))q[i]--;
    queue<V> que;
    que.push({0});
    int ptr = 0;
    while(que.size()){
        V x = que.front();que.pop();
        //for(auto &it:x)cout<<it<<" ";cout<<endl;
        int m = x.size();
        if(m==0)continue;
        V y;
        for(int i:range(m)){
            y.push_back(q[ptr+i]);
        }
        auto xx = x;
        auto yy = y;
        sort(ALL(xx));
        sort(ALL(yy));
        if(xx!=yy){
            cout<<"No"<<endl;
            return 0;
        }
        for(int v:y){
            que.push(t[v]);
        }
        ptr+=m;
    }
    cout<<"Yes"<<endl;
    return 0;
}