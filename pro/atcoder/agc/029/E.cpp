//https://atcoder.jp/contests/agc029/tasks/agc029_e
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

map<pair<int,int>,int> memo;
vector<int> G[212345];
int N;
int c[212345];
int Q(int v,int p,int x){
    if(memo.count({v,x}))return memo[{v,x}];
    int ret=0;
    for(int u:G[v]){
        if(p==u)continue;
        if(u>x)continue;
        ret+=1+Q(u,v,x);
    }
    return memo[{v,x}]=ret;
}
void solve(int v,int p,int mv,int mpv){
    if(v!=1){
        if(v>mpv){
            c[v]=c[p]+Q(v,p,mv)+1;
        }
        else{
            c[v]=c[p]-Q(v,p,mpv)+Q(v,p,mv);
        }
    }
    for(int u:G[v]){
        if(u==p)continue;
        solve(u,v,max(v,mv),max(mpv,p));
    }
}
int main(){
    cin>>N;
    for(int i:range(N-1)){
        int a,b;
        cin>>a>>b;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    solve(1,0,0,0);
    string sp(N,' ');sp.push_back('\n');
    for(int i:range(2,N+1)){
        cout<<c[i]<<sp[i];
    }
    return 0;
}