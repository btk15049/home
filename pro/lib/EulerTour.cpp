#ifndef VS
#include <bits/stdc++.h>
using namespace std;
#endif
typedef long long LL;
typedef vector<int> V;
typedef vector<V> Graph;
const LL INF = 1e9;

typedef pair<int,int> P;
struct Tree{
    Graph g;
    void dfs(int v,int p,Graph &in){
        for(auto &u:in[v]){
            if(u==p)continue;
            g[v].push_back(u);
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

void euler_tour(int v,Tree &g,vector<P> &seg,int& cnt){
    int l=cnt++;
    for(auto &u:g[v])
        euler_tour(u,g,seg,cnt);
    int r=cnt++;
    seg[v]={l,r};
}

