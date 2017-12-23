#include <bits/stdc++.h>
using namespace std;
#define FOR(i,bg,ed) for(int i=(bg);i<(ed);i++)
#define REP(i,n) FOR(i,0,n)
#define ALL(v) (v).begin(),(v).end()
#define pb push_back





//Decomposition of Strongly Connected Components
//KYOURENKETSU SEIBUN BUNKAI
/*
  comp[v]: component id of vertex v
  node[k]: vertexes in component k
  edge[k]: link edges from component k to component t!=k
*/
typedef vector<int> V;
typedef vector<V> VV;
typedef VV Graph;
#define ITR(i,v) for(auto & i :(v))
class SCC{
private:
    Graph e,r_e;
    V vs;
public:
    int size;
    V comp;
    VV node;
    Graph edge;
private:
    void dfs(int v){
        comp[v]=0;
        ITR(u,e[v])if(comp[u]<0)dfs(u);
        vs.pb(v);
    }
    void rdfs(int v,int k){
        comp[v]=k;
        ITR(u,r_e[v])if(comp[u]<0)rdfs(u,k);
    }
    void decomposition(){
        comp.resize(size);
        fill(ALL(comp),-1);
        vs.reserve(size);
        REP(v,size)if(comp[v]<0)dfs(v);
        reverse(ALL(vs));
        fill(ALL(comp),-1);
        int k=0;
        ITR(v,vs)if(comp[v]<0)rdfs(v,k++);
        node.resize(k);
        edge.resize(k);
        REP(v,size){
            node[comp[v]].pb(v);
            for(auto& u : e[v]){
                if(!isSame(v,u)){
                    edge[comp[v]].pb(comp[u]);
                }
            }
        }
        size=k;
    }
public:
    bool isSame(int a,int b){
	return comp[a]==comp[b];
    }
    SCC(Graph& in){
        size=in.size();
        e=in;
        r_e.resize(size);
        REP(v,size)ITR(u,e[v])r_e[u].pb(v);
        decomposition();
    }
};


// for 2-SAT
void add_edge(Graph &g,int u,int v){
    g[u].pb(v);
}
void add_or(Graph& g,V &rev,int u,int v){
    add_edge(g,rev[u],v);
    add_edge(g,rev[v],u);
}
void add_xor(Graph& g,V &rev,int u,int v){
    add_or(g,rev,u,v);
    add_or(g,rev,rev[u],rev[v]);
}
