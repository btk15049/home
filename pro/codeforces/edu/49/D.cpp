//http://codeforces.com/contest/1027/problem/D
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#ifdef BTK
#define DEBUG if(1)
#else
#define CIN_ONLY if(1)
struct cww {cww() {CIN_ONLY{ios::sync_with_stdio(false); cin.tie(0);}}}star;
#define DEBUG if(0)
#endif
#define ALL(v) (v).begin(),(v).end()
#define REC(ret, ...) std::function<ret (__VA_ARGS__)>
template <typename T>inline bool chmin(T &l, T r){bool a = l>r; if (a)l = r; return a;}
template <typename T>inline bool chmax(T &l, T r){bool a = l<r; if (a)l = r; return a;}
template <typename T>istream& operator>>(istream &is, vector<T> &v){for (auto &it : v)is >> it;return is;}
class range {private: struct I { int x; int operator*() { return x; }bool operator!=(I& lhs) { return x<lhs.x; }void operator++() { ++x; } }; I i, n;public:range(int n) :i({ 0 }), n({ n }) {}range(int i, int n) :i({ i }), n({ n }) {}I& begin() { return i; }I& end() { return n; }};

//The number of outdegree of vertex in graph "in" is 1
constexpr int USED = -2;
constexpr int BRANCH = -1;
constexpr int UNCYCLE = 11234567;
struct SunnyGraph {
	using V = vector<int>;
	using Graph = vector<V>;
	int size;
	Graph g; // g[i]    : vertexes of i th component's loop
	Graph in;// in[v]   : reverse edges(not in loop) toward v
	V K;     // K[v]    : id of connected component contains v
	V root;  // root[v] : root vertex of v (same connected components)
	int dfs1(int v, V& out, int id, V &loop) {
		auto &sign = K;
		sign[v] = -2;
		int u = out[v];
		if (sign[u] >= 0) {
			sign[v] = UNCYCLE;
			return BRANCH;
		}
		if (sign[u] == USED || (u = dfs1(u, out, id, loop)) >= 0) {
			sign[v] = id;
			root[v] = v;
			loop.push_back(v);
			if (v == u)return BRANCH;
			else return u;
		}
		K[v] = UNCYCLE;
		return BRANCH;
	}
	void dfs2(int v) {
		for (auto &u : in[v]) {
			K[u] = K[v];
			root[u] = root[v];
			dfs2(u);
		}
	}
	SunnyGraph(V out) {
		size = out.size();
		in.resize(size);
		K.resize(size, -1);
		root.resize(size);
		int id = 0;
		for (int v = 0; v < size; v++){
			V L;
			if (K[v] == -1)dfs1(v, out, id, L);
			if (L.size()) {
				g.push_back(L);
				id++;
			}
		}
		for (int v = 0; v < size; v++)
			if (K[v] == UNCYCLE)in[out[v]].push_back(v);
		for (auto &s : g)for (auto &v : s)dfs2(v);
	}
};


int main(){
    int n;
    cin>>n;
    vector<LL> c(n);
    vector<int> a(n);
    cin>>c;
    cin>>a;
    for(int i:range(n))a[i]--;
    SunnyGraph sg(a);
    LL ret=0;
    for(auto &loop:sg.g){
        LL ans = c[loop[0]];
        for(auto &v:loop)chmin(ans,c[v]);
        ret+=ans;
    }
    cout<<ret<<endl;
    return 0;
}