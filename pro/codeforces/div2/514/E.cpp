#include<bits/stdc++.h>

using namespace std;
typedef long long LL;

#ifdef BTK
#define DEBUG if(1)
#else
#define CIN_ONLY if(1)
struct cww {cww() {CIN_ONLY{ios::sync_with_stdio(false); cin.tie(0);}}
}star;
#define DEBUG if(0)
#endif

#define ALL(v) (v).begin(),(v).end()
#define REC(ret, ...) std::function<ret (__VA_ARGS__)>
template <typename T>inline bool chmin(T &l, T r){bool a = l>r; if (a)l = r; return a;}
template <typename T>inline bool chmax(T &l, T r){bool a = l<r; if (a)l = r; return a;}
template <typename T>istream& operator>>(istream &is, vector<T> &v){for (auto &it : v)is >> it;return is;}

class range {private: struct I { int x; int operator*() { return x; }bool operator!=(I& lhs) { return x<lhs.x; }void operator++() { ++x; } }; I i, n;public:range(int n) :i({ 0 }), n({ n }) {}range(int i, int n) :i({ i }), n({ n }) {}I& begin() { return i; }I& end() { return n; }};

vector<LL> path;
int dep[112345];
int top[112345];
LL w[112345];
using V = vector<int>;
using VV = vector<V>;
VV g;
int n,L;
LL S;
int ret = 1;
void dfs(int v,int dep, LL W){
    W+=w[v];
    path.push_back(W);
    int ok = (int)path.size()-1;
    int ng = -1;
    while(ok-ng>1){
        const int mid = (ok+ng)/2;
        LL weight = W-path[mid];
        int length = dep+1-mid;
        if(weight<=S&&length<=L){
            ok=mid;
        }
        else ng=mid;
    }
    top[v]=dep+1;
    for(int u:g[v]){
        dfs(u,dep+1,W);
        chmin(top[v],top[u]);
    }
    ret+=g[v].size();
    if(top[v]!=dep+1)ret--;
    else top[v]=ok;
    path.pop_back();
}

int main() {
    
    cin>>n;
    g=VV(n);
    cin>>L>>S;
    for(int i:range(n)){
        cin>>w[i];
        if(w[i]>S){
            cout<<-1<<endl;
            return 0;
        }
    }
    for(int i:range(1,n)){
        int p;
        cin>>p;
        g[p-1].push_back(i);
    }
    path.push_back(0);
    dfs(0,0,0);
    cout<<ret<<endl;
    return 0;
}
