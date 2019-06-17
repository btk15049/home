//https://atcoder.jp/contests/nikkei2019-qual/tasks/nikkei2019_qual_e
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

namespace _DSU{
    constexpr int BUF = 212345*2;
    int ptr=0;
    int mem[BUF];
    int* get(int size){
        ptr+=size;
        return mem+ptr-size;
    }
    void reset(){
        ptr = 0;
    }
}
LL W[212345];
class UF{
private:
    int *par,*rank;
    public:
    int find(int x){
        if (par[x] == x){
            return x;
        }
        else{
            return par[x] = find(par[x]);
        }
    }
    UF(int n):par(_DSU::get(n+10)),rank(_DSU::get(n+10)){
	for(int i = 0;i<n;i++){
            par[i] = i,rank[i] = 0;
        }
    }
    bool unite(int x, int y){
    	x = find(x);y = find(y);
	if (x == y)return false;
	if (rank[x] < rank[y])swap(x,y);
    par[y] = x;

    if (rank[x] == rank[y])rank[x]++;
    W[x]+=W[y];
    W[y]=0;
	return true;
    }
    bool same(int x, int y){
        return find(x) == find(y);
    }
};


int N,M;
int a[112345];
int b[112345];
LL  c[112345];
LL  w[112345];
pair<LL,int> edge[112345];
vector<int> g[112345];
bool vis[112345];
bool ok[112345];
void f(int v,LL th){
    if(vis[v])return;
    vis[v]=true;
    for(int e:g[v]){
        if(c[e]>th)break;
        const int u = a[e]^b[e]^v;
        f(u,th);
    }
}
int main(){
    cin>>N>>M;
    for(int i:range(N)){
        cin>>w[i];
    }
    for(int i:range(M)){
        cin>>a[i]>>b[i]>>c[i];
        a[i]--;
        b[i]--;
        g[a[i]].push_back(i);
        g[b[i]].push_back(i);
        edge[i]={c[i],i};
    }
    sort(edge,edge+M);
    for(int i:range(N)){
        sort(ALL(g[i]),[&](int l,int r){return c[l]<c[r];});
    }
    UF uf(N);
    for(int i:range(N))W[i]=w[i];
    for(int i:range(M)){
        int e=edge[i].second;
        uf.unite(a[e],b[e]);
        ok[e] = c[e]<=W[uf.find(a[e])];
    }
    reverse(edge,edge+M);
    int ret=0;
    for(int i:range(M)){
        int e=edge[i].second;
        if(ok[e]||vis[a[e]]){
            f(a[e],c[e]);
        }
        else{
            ret++;
        }
    }
    cout<<ret<<endl;
    return 0;
}