#ifndef VS 
#include <bits/stdc++.h>
using namespace std;
#endif

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
class UF{
private:
    int *par,*rank;
    int find(int x){
	if (par[x] == x) return x;
	else return par[x] = find(par[x]);
    }
public:
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
	return true;
    }
    bool same(int x, int y){
	return find(x) == find(y);
    }
};
