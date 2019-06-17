//https://code-festival-2018-final.contest.atcoder.jp/tasks/code_festival_2018_final_h
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

int N,M;
int A[71234];
int B[71234];
LL C[71234];
int P[71234];
LL S[71234];
LL E[71234];
LL D[71234];

using V=vector<int>;
using VV=vector<V>;

namespace CD{
    #define pb push_back
    struct centroid{
        int size;
        int par;
        V   cld;
        V   vex;
    }node[71234];
    int mem[71234];
    stack<int> st;
    int dfs(int v,int p,int all,VV &g,int *a,int *b,int &tar,int& ans,int *used){
        int cld_size=1;
        int cld_max=0;
        used[v]=0;
        for(auto &e:g[v]){
            int u=v^a[e]^b[e];
            if(used[u]!=-1)continue;
            if(u==p)continue;
            int cld=dfs(u,v,all,g,a,b,tar,ans,used);
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
    int construct(int v,VV&g,int *a,int *b,int *used,int p=-1){
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
        dfs(v,-1,vex.size(),g,a,b,v,lim,used);
        used[v]=1;

        node[v].size = vex.size();
        node[v].par  = p;
        node[v].vex  = vex;

        for(auto &e:g[v]){
            int u=v^a[e]^b[e];
            if(used[u])continue;
            node[v].cld.pb(construct(u,g,a,b,used,v));
        }
        return v;
    }
    int decomposition(VV &g,int bg=0){
        return construct(bg,g,A,B,mem);
    }
	vector<int> get_pars(int v){
		vector<int> ret;
		ret.reserve(50);
		while(v!=-1){
			ret.push_back(v);
			v=node[v].par;
		}
		return ret;
	}
}

namespace StaticRMQ {
	/*
	default:: range minimum query
	*/

	template<typename T>
	using MergeFunction = function<T(T,T)>;

	template<typename T>
	MergeFunction<T>
		getMin = [](T l, T r) {
		return l < r ? l : r;
	};

    template<typename T>
	MergeFunction<T>
		getMax = [](T l, T r) {
		return l > r ? l : r;
	};


	template<typename T>
	class BufferManager {
	private:
		T* const mem;
		int ptr;
	public:
		BufferManager(T* buf):mem(buf) {
			ptr = 0;
		}
		T* get(int m) {
			ptr += m;
			return mem + ptr - m;
		}
		void reset() {
			ptr = 0;
		}
	};

	namespace Buffer{
		// if N<=10^6 : BufferSize is enough for 5 * N
		constexpr int BufferSize = 5 * 212345;
		using NodeType = pair<int,int>;
		NodeType mem[BufferSize];
		BufferManager<NodeType> buffer(mem);
	}

	template<typename T, typename ITR>
	struct SparseTable {
		const int n;
		const int logn;
		T* const mem;
		MergeFunction<T> Merge;
		void build() {
			for (int h = 0; h + 1 < logn; h++) {
				const int half = 1 << h;
				const int len = half << 1;
				for (int i = 0; i + len <= n; i++) {
					mem[h*n + n + i] = Merge(mem[h*n + i], mem[h*n + i + half]);
				}
			}
		}
		static inline int get_log(const int n) {
			int l = 1;
			for (int tmp = 1; tmp < n; tmp <<= 1)l++;
			return l;
		}
		SparseTable(ITR bg, ITR ed,
            MergeFunction<T> f = getMin<T>,
			BufferManager<T> &bf = Buffer::buffer
            )
			: n(distance(bg,ed)),
			logn(get_log(n)),
			mem(bf.get(n*logn)),
			Merge(f) {
			for (auto p = mem; bg != ed; ++bg, ++p) {
				(*p) = (*bg);
			}
			build();
		}
		inline int get_msb(const int size) {
#ifdef BTK
			int id = 0;
			for (int i = 0; i < logn; i++)if (size >> i)id = i;
			return id;
#else
			return 31 - __builtin_clz(size);
#endif
		}
		inline T get(const int l, const int r) {
			const int msb = get_msb(r - l);
			return Merge(mem[msb*n + l], mem[msb*n + r - (1 << msb)]);
		}
	};

	template<typename T, typename ITR>
	struct SmallRMQ{
		const int n;
		T* const mem;
		MergeFunction<T> Merge;
		void build(ITR bg,ITR ed) {
			int x = distance(bg, ed);
			for (auto p = mem; x > 0; x -= 4) {
				T tmp[4];
				tmp[0] = (*bg); ++bg;
				if (x >= 1)tmp[1] = (*bg); ++bg;
				if (x >= 2)tmp[2] = (*bg); ++bg;
				if (x >= 3)tmp[3] = (*bg); ++bg;
				for (int i = 0; i < 4; i++) {
					T ret = tmp[i];
					(*p) = ret; ++p;
					for (int j = i + 1; j < 4; j++) {
						ret = Merge(ret,tmp[j]);
						(*p) = ret; ++p;
					}
				}
			}
		}
		SmallRMQ(ITR bg, ITR ed,
			MergeFunction<T> f = getMin<T>,
			BufferManager<T> &bf = Buffer::buffer
            )
            : n(((distance(bg, ed)+3)>>2)<<2),
			mem(bf.get((n>>2) * 10)),
			Merge(f) {
			build(bg, ed);
		}
		inline T get(int l, int r) {
			const int block = l >> 2;
			l &= 3; r--; r &= 3;
			const int segment = (10 - (((4 - l)*(4 - l + 1)) >> 1)) + (r - l);
			return mem[block * 10 + segment];
		}

	};
	template<typename T, typename ITR>
	struct RMQ {
		const int n;
		MergeFunction<T> Merge;
		T* const workspace;
		SmallRMQ<T, ITR> small;
		SmallRMQ<T, T*> medium;
		SparseTable<T, T*> large;
		template<typename S, typename Itr>
		inline S buildBlock(Itr bg, Itr ed, BufferManager<T>& bf, const int size) {
			T* p = workspace;
			for (int x = distance(bg, ed); x > 0; ++p, x-=4) {
				(*p) = (*bg); ++bg;
				if(x>=1)(*p) = Merge(*p, *bg); ++bg;
				if(x>=2)(*p) = Merge(*p, *bg); ++bg;
				if(x>=3)(*p) = Merge(*p, *bg); ++bg;
			}
			return S(workspace, workspace+size, Merge, bf);
		}
		RMQ(ITR bg, ITR ed,
			MergeFunction<T> f = getMin<T>,
			BufferManager<T> &bf = Buffer::buffer
        ): n(((distance(bg, ed) + 15) >> 4) << 4),
			Merge(f),
			workspace(bf.get(n >> 2)),
			small(bg, ed, f, bf),
			medium(buildBlock<SmallRMQ<T, T*>, ITR>(bg, ed, bf, n >> 2)),
			large(buildBlock<SparseTable<T, T*>, T*>(workspace, workspace + (n >> 2), bf, n >> 4))
		{}
		inline T get(int l, int r) {
			int nl = (l >> 2) + 1;
			int nr = ((r - 1) >> 2);
			T ret = small.get(l, min(nl << 2, r));
			ret = Merge(ret, small.get(max(l, nr << 2),r));
			l = nl; r = nr;
			nl = (l >> 2) + 1;
			nr = ((r - 1) >> 2);
			if (l >= r)return ret;
			ret = Merge(ret, medium.get(l, min(nl << 2, r)));
			ret = Merge(ret, medium.get(max(l, nr << 2), r));
			l = nl; r = nr;
			if (l >= r)return ret;
			else return Merge(ret, large.get(l, r));
		}
	};
}

int dep[71234];
LL len[71234];
pair<int,int> sec[212345];
int pos[71234];
void _dfs(VV &g, int &id, int v,int p){
    pos[v]=id;
    sec[id++]={dep[v],v};
    for(int e:g[v]){
        int u = A[e]^B[e]^v;
        if(u==p)continue;
        dep[u]=dep[v]+1;
        len[u]=len[v]+C[e];
        _dfs(g,id,u,v);
        sec[id++]={dep[v],v};
    }
}
using RMQ=StaticRMQ::RMQ<pair<int,int>,pair<int,int>*>;
RMQ dfs(VV &g){
    int id = 0;
    dep[0]=0;
    len[0]=0;
    _dfs(g,id,0,0);
    RMQ rmq(sec,sec+id);
    return rmq;
}
int lca(int p,int q,RMQ rmq){
    p=pos[p];
    q=pos[q];
    if(p>q)swap(p,q);
    return rmq.get(p,q+1).second;
}
LL dist(int p,int q,RMQ rmq){
    int pq=lca(p,q,rmq);
    return len[p]+len[q]-2*len[pq];
}

pair<pair<LL,int>,pair<int,int>> query[2123456];
LL ret[71234];
LL qr[71234];
int Q=0;
int main(){
    cin>>N>>M;
    VV g(N);
    for(int i:range(N-1)){
        cin>>A[i]>>B[i]>>C[i];
        A[i]--;B[i]--;
        g[A[i]].push_back(i);
        g[B[i]].push_back(i);
    }
    CD::decomposition(g);
    auto rmq=dfs(g);
    for(int i:range(M)){
        cin>>S[i]>>E[i]>>P[i]>>D[i];
		P[i]--;
		auto ps = CD::get_pars(P[i]);
		for(auto &t:ps){
			LL d=dist(P[i],t,rmq);
			query[Q++]={{S[i]-d,1},{t,i}};
			query[Q++]={{E[i]+d,0},{t,i}};
			//cout<<len[P[i]]<<" "<<len[t]<<endl;
			//cout<<"dist("<<P[i]<<","<<t<<")="<<d<<endl;
		}
    }
	sort(query,query+Q);
	for(int i:range(Q)){
		LL t=query[i].first.first;
		int q=query[i].second.second;
		int target=query[i].second.first;
		if(query[i].first.second==0){
			chmax(ret[target],qr[q]);
		}
		else{
			chmax(qr[q],ret[target]+D[q]);
			//cout<<t<<" "<<target<<" "<<q<<" "<<qr[q]<<endl;
		}
	}
	LL ans=0;
	for(int i:range(1,N+1)){
		chmax(ans,ret[i]);
	}
	cout<<ans<<endl;
    return 0;
}