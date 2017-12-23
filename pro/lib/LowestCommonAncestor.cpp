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

namespace LCA{
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
    //lcaÇÃèÄîı
    void build(int n){
        for(int k = 0,f = 1;f; k++){
            f=0;
            REP(i,n){
                if(pp[k][i]<0)pp[k+1][i]=-1;
                else{
                    pp[k+1][i]=pp[k][pp[k][i]];
                    f=1;
                }
            }
        }
    }
    
    inline int lca(int u,int v){
        if(depth[u] > depth[v])swap(u,v);
        for(int k = 0,d;(d=depth[v]-depth[u]); k++){
            if((d >> k) & 1){
                v=pp[k][v];
            }
            if(u==v)return v;
            for(int k = LOG-1; k >=0 ; k--){
                if(pp[k][u]!=pp[k][v]){
                    u=pp[k][u];
                    v=pp[k][v];
                }
            }
            return pp[0][u];
        }
    }
}
    
