#include<bits/stdc++.h>
using namespace std;

typedef long long LL;

#define pb push_back
template <typename T>inline bool chmax(T &l,T r)
{bool a=l<r;if(a)l=r;return a;}

constexpr int SIZE = 112345;

int a[SIZE];
int b[SIZE];
int c[SIZE];
int used[SIZE];

typedef vector<int> V;
typedef vector<V> VV;
namespace CD{
    struct centroid{
        int size;
        int par;
        V   cld;
        V   vex;
    }node[1123456];
    stack<int> st;
    int dfs(int v,int p,int all,VV &g,int &tar,int& ans){
        int cld_size=1;
        int cld_max=0;
        used[v]=0;
        for(auto &e:g[v]){
            int u=v^a[e]^b[e];
            if(used[u]!=-1)continue;
            if(u==p)continue;
            int cld=dfs(u,v,all,g,tar,ans);
            chmax(cld_max,cld);
            cld_size+=cld;
        }
        chmax(cld_max,all-cld_size);
        if(cld_max<ans){
            tar=v;
            ans=cld_max;
        }
        return cld_size;
    }
    int construct(int v,int p,VV&g){
        st.push(v);
        V vex;
        vex.pb(v);
        used[v]=-1;
        while(st.size()){
            int s=st.top();st.pop();
            for(auto &e:g[s]){
                int t=s^a[e]^b[e];
                if(used[t])continue;
                st.push(t);
                used[t]=-1;
                vex.pb(t);
            }
        }
        
        int lim = vex.size()+1;
        dfs(v,-1,vex.size(),g,v,lim);
        used[v]=1;
        
        node[v].size = vex.size();
        node[v].par  = p;
        node[v].vex  = vex;

        for(auto &e:g[v]){
            int u=v^a[e]^b[e];
            if(used[u])continue;
            node[v].cld.pb(construct(u,v,g));
        }
        return v;
    }    
}

