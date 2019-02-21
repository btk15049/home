//https://atcoder.jp/contests/nikkei2019-qual/tasks/nikkei2019_qual_d
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
class reverse_range {private:struct I {int x;int operator*() {return x-1;}bool operator!=(I& lhs) {return x>lhs.x;}void operator++() {--x;}};I i, n;public:reverse_range(int n) :i({ 0 }), n({ n }){}reverse_range(int i, int n) :i({ i }), n({ n }){}I& begin() {return n;}I& end() {return i;}};
class range {private: struct I { int x; int operator*() { return x; }bool operator!=(I& lhs) { return x<lhs.x; }void operator++() { ++x; } }; I i, n;public:range(int n) :i({ 0 }), n({ n }) {}range(int i, int n) :i({ i }), n({ n }) {}I& begin() { return i; }I& end() { return n; }reverse_range operator!(){return reverse_range(*i,*n);}};

int N,M;
vector<int> g[112345];
int vis[112345];
int o[112345];
int root= -1;
int t[112345];
void dfs(int v,int &id){
    vis[v]=1;
    for(int u:g[v])if(vis[u]==0)dfs(u,id);
    if(id==0)root = v;
    o[v]=id--;
}
void dd(int v){
    vis[v]=1;
    for(int u:g[v]){
        if(o[t[u]]<o[v]){
            t[u]=v;
        }
        if(vis[u])continue;
        dd(u);
    }
}
int main(){
    cin>>N>>M;
    for(int i:range(N+M-1)){
        int a,b;
        cin>>a>>b;
        g[a-1].push_back(b-1);
    }
    int id = N-1;
    for(int i:range(N)){
        if(vis[i]==0){
            dfs(i,id);
        }
    }
    for(int i:range(N)){
        t[i]=root;
        vis[i]=0;
    }
    dd(root);
    //for(int i:range(N))cout<<i<<" "<<o[i]<<endl;
    for(int i:range(N)){
        if(i!=t[i]){
            cout<<t[i]+1<<endl;
        }
        else cout<<0<<endl;
    }
    return 0;
}