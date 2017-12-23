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



//The number of outdegree of vertex in graph "in" is 1
constexpr int USED = -2;
constexpr int BRANCH = -1;
constexpr int UNCYCLE = 11234567;
struct sunny_graph{
    int size;
    
    Graph g,in;
    V K;    // K[v]    : id of connected component contains v
    V root; // root[v] : root vertex of v (same connected components)
    int dfs1(int v,V& out,int id,V &loop){
        auto &sign = K;
        sign[v]=-2;
        int u=out[v];
        if(sign[u]>=0){
            sign[v]=UNCYCLE;
            return BRANCH;
        }
        if(sign[u]==USED||(u=dfs1(u,out,id,loop))>=0){
            sign[v]=id;
            root[v]=v;
            loop.pb(v);
            if(v==u)return BRANCH;
            else return u;
        }
        K[v]=UNCYCLE;
        return BRANCH;
    }
    void dfs2(int v){
        for(auto &u:in[v]){
            K[u]=K[v];
            root[u]=root[v];
            dfs2(u);
        }            
    }
    sunny_graph(V out){
        size=out.size();
        in.resize(size);
        K.resize(size,-1);
        root.resize(size);
        int id=0;
        REP(v,size){
            V L;
            if(K[v]==-1)dfs1(v,out,id,L);
            if(L.size()){
                g.pb(L);
                id++;
            }
        }
        REP(v,size)if(K[v]==UNCYCLE)in[out[v]].pb(v);
        for(auto &s:g)for(auto &v:s)dfs2(v);
    }
};
