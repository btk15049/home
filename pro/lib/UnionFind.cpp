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
	REP(i,n)par[i] = i,rank[i] = 0;
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
