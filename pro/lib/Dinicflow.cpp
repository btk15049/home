#include <bits/stdc++.h>
using namespace std;
#define pb push_back

using FLOW = int;
namespace flow{
    constexpr FLOW INF = 1e7;
    struct edge{
        FLOW flow;
        int to,rev;
    };
    typedef vector<edge> E;
    typedef vector<E> Graph;
    void addedge(Graph&g,int from,int to,FLOW f){
        int x=g[from].size();
        int y=g[to].size();
        g[from].pb(edge{f,to,y});
        g[to].pb(edge{(FLOW)0,from,x});
    }

    vector<int> bfs(Graph& G,int s){
        int N = G.size();
        queue<int> que;
        vector<int> dist(N,-1);
        dist[s] = 0;
        que.push(s);
        for(;!que.empty();que.pop()){
            auto v=que.front();
            for(auto& e : G[v])
                if(e.flow>0&&dist[e.to]==-1){
                    dist[e.to] = dist[v] + 1;
                que.push(e.to);
                }
        }
        return dist;
    }
}
FLOW maxflow(flow::Graph& G,int s,int t){
    using namespace flow;
    FLOW res=0;
    int N = G.size();
    while(true){
        auto dist = bfs(G,s);
        if(dist[t] < 0)break;
        vector<unsigned> iter(N,0);
        std::function<FLOW(int,FLOW)> dfs=[&](int v,FLOW f){
            if(v==s)return f;
            for(auto &i = iter[v]; i < G[v].size(); i++){
                edge &e = G[v][i];
                edge &re = G[e.to][e.rev];
                if(re.flow>0 && dist[v] >dist[e.to]){
                    FLOW d=dfs(e.to,min(f,re.flow));
                    if(d>0){e.flow+=d;re.flow-=d;return d;}
                }
            }
            return (FLOW)0;
        };
        FLOW f;
        while((f=dfs(t,INF))> 0)res+=f;
    }
    return res;
}
