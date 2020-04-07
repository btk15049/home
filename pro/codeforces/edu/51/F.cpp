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

using V=vector<int>;
using VV = vector<V>;
constexpr int S=112345;
int a[S];
int b[S];
LL c[S];
bool inT[S];
VV g;
LL dep[S];
LL dist[S*21];
bool used[S];
void dfs(int v){
    used[v]=true;
    for(int e:g[v]){
        const int u = v^a[e]^b[e];
        if(used[u])continue;
        inT[e]=true;
        dep[u]=dep[v]+c[e];
        dfs(u);
    }
}
using P=pair<LL,int>;
priority_queue<P> que;
void dijkstra(int s, LL *d){
    que.push({0,s});
    for(int i:range(g.size()))d[i]=1e18;
    d[s]=0;
    while(que.size()){
        LL cost;int v;
        tie(cost,v)=que.top();que.pop();
        cost=-cost;
        if(d[v]<cost)continue;
        for(int e:g[v]){
            const int u = v^a[e]^b[e];
            if(chmin(d[u],d[v]+c[e])){
                que.push({-d[u],u});
            }
        }
    }
}
using Graph = VV;
struct Tree {
    Graph g;
    void dfs(int v, int p, Graph &in) {
        for (auto e : in[v]) {
            const int u = v^a[e]^b[e];
            if (u == p)continue;
            if(inT[e]==false)continue;
            g[v].push_back(u);
            dfs(u, v, in);
        }
    }
    Tree(Graph& in) :g(in.size()) {
        dfs(0, 0, in);
    }
    V& operator[](const int i) {
        return g[i];
    }
    int size() {
        return (int)g.size();
    }
};

namespace LCA {
    /*
      use doubling
      - build : O(nlogn)
      - query : O(logn)
    */
    constexpr int BUF = 112345;
    constexpr int LOG = 20; // LOG >= log(BUF)
    int pp[LOG][BUF];
    int *p = pp[0];
    int depth[BUF];

    void dfs(int v, Tree &g) {
        for (int u : g[v]) {
            depth[u] = depth[v] + 1;
            p[u] = v;
            dfs(u, g);
        }
    }

    void build(Tree &g, int root = 0) {
        int n = g.size();
        for (int i = 0; i < n; i++) {
            pp[0][i] = -1;
        }
        depth[root] = 0;
        dfs(root, g);
        for (int k = 0, f = 1; f; k++) {
            f = 0;
            for(int i = 0; i < n; i++) {
                if (pp[k][i]<0)pp[k + 1][i] = -1;
                else {
                    pp[k + 1][i] = pp[k][pp[k][i]];
                    f = 1;
                }
            }
        }
    }

    inline int lca(int u, int v) {
        if (depth[u] > depth[v])swap(u, v);
        for (int k = 0, d; (d = depth[v] - depth[u]); k++) {
            if ((d >> k) & 1) {
                v = pp[k][v];
            }
        }
        if (u == v)return v;
        for (int k = LOG - 1; k >= 0; k--) {
            if (pp[k][u] != pp[k][v]) {
                u = pp[k][u];
                v = pp[k][v];
            }
        }
        return pp[0][u];
		
    }	
    inline int dist(int a, int b) {
        int c = lca(a, b);
        return depth[a] + depth[b] - 2 * depth[c];
    }
    inline int lca(int a, int b, int c) {
        int d = lca(a, b);
        int e = lca(b, c);
        int f = lca(c, a);
        int dd = dist(d, a) + dist(d, b) + dist(d, c);
        int ee = dist(e, a) + dist(e, b) + dist(e, c);
        int ff = dist(f, a) + dist(f, b) + dist(f, c);
        vector<pair<int, int>> v = { {dd,d},{ee,e},{ff,f} };
        return min_element(v.begin(),v.end())->second;
    }
}
int main() {
    int n,m;
    cin>>n>>m;
    g=VV(n);
    
    for(int i:range(m)){
        cin>>a[i]>>b[i]>>c[i];
        a[i]--;b[i]--;
        g[a[i]].push_back(i);
        g[b[i]].push_back(i);
    }
    dfs(0);
    V r;
    for(int i:range(m)){
        if(inT[i]==false)r.push_back(a[i]);
    }
    for(int i:range(r.size())){
        dijkstra(r[i],dist+n*i);
    }
    Tree t(g);
    LCA::build(t);
    
    int q;
    cin>>q;
    while(q--){
        int x,y;
        cin>>x>>y;
        x--;y--;
        LL ret=1e18;
        for(int i:range(r.size())){
            LL *d = dist+i*n;
            chmin(ret,d[x]+d[y]);
            DEBUG cout<<d[x]+d[y]<<" ";
        }
        int z = LCA::lca(x,y);
        DEBUG cout<<z<<" "<<dep[x]+dep[y]-2*dep[z]<<" ";;
        chmin(ret,dep[x]+dep[y]-2*dep[z]);
        cout<<ret<<endl;
    }
    return 0;
}
