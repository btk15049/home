#include<bits/stdc++.h>
using namespace std;

//heavy light decomposition
namespace hld{
    constexpr int BUF = 2123456*4;
    int mem[BUF];
    int ptr = 0;

    //reset pointer for multi testcases 
    inline void reset(){
        ptr = 0;
    }
    inline int* get(const int size){
        ptr+=size;
        return mem+ptr-size;
    }
    
    
};
typedef vector<int> V;
typedef vector<V> Graph;
class HLD{
private:
    int *treesize;
    Graph *tree;
public:
    int size,*group,*id,*par,*bg;
private:
    void setTreeSize(int v){
	treesize[v]=1;
	for(auto &u:(*tree)[v]){
	    setTreeSize(u);
	    treesize[v]+=treesize[u];
	}
    }
    void build(int v,int g,int& i){
	group[v]=g;
	id[v]=i++;
	Graph &gr=(*tree);
	const int sz=gr[v].size();
	if(sz){
	    int h=gr[v][0];
	    for(auto &u:gr[v])
		if(treesize[h]<treesize[u])h=u;
	    build(h,g,i);
	    for(auto &u:gr[v])
		if(h!=u){
		    par[size]=v;
		    bg[size]=i;
		    build(u,size++,i);
		}
	}
    }
public:
    HLD(Graph *tree,int root=0):tree(tree),size(0){
        int n = (*tree).size();
        id = treesize = hld::get(n+10);
        group = hld::get(n+10);
        par = hld::get(n+10);
        bg = hld::get(n+10);
        
	setTreeSize(root);
	int i=0;
	par[size]=-1;
	bg[size]=i;
	build(root,size++,i);
    }
    using P=pair<int,int>;
    int lca(int v,int u){
        while(group[v]!=group[u]){
            if(group[v]<group[u])swap(v,u);
            v=par[group[v]];
        }
        return id[v]<id[u]?v:u;
    }
    vector<P> decomposition(int v,int u){
        vector<P> res;
        while(group[v]!=group[u]){
            if(group[v]<group[u])swap(v,u);
            res.push_back({bg[group[v]],id[v]});
            v=par[group[v]];
        }
        res.push_back(minmax(id[v],id[u]));
        return res;
    }    
};
