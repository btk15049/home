#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define FOR(i,bg,ed) for(int i=(bg);i<(ed);i++)
#define REP(i,n) FOR(i,0,n)
#define ALL(v) (v).begin(),(v).end()
#define fi first
#define se second
#define pb push_back
typedef vector<int> V;
typedef vector<V> Graph;
const LL INF = 1e9;

typedef pair<int,int> P;
struct Tree{
    Graph g;
    void dfs(int v,int p,Graph &in){
        for(auto &u:in[v]){
            if(u==p)continue;
            g[v].pb(u);
            dfs(u,v,in);
        }
    }
    Tree(Graph& in):g(in.size()){
        dfs(0,0,in);
    }
    V& operator[](const int i){
        return g[i];
    }
    int size(){
        return (int)g.size();
    }
};

void euler_tour(int v,Tree &g,vector<P> &seg,int cnt){
    int l=cnt++;
    for(auto &u:g[v])
        euler_tour(u,g,seg,cnt);
    int r=cnt++;
    seg[v]={l,r};
}

