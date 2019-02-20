//https://atcoder.jp/contests/nikkei2019-final/tasks/nikkei2019_final_f
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
class reverse_range {private:struct I {int x;int operator*() {return x-1;}bool operator!=(I& lhs) {return x>lhs.x;}void operator++() {--x;}};I i, n;public:reverse_range(int n) :i({ 0 }), n({ n }){}reverse_range(int i, int n) :i({ i }), n({ n }){}I& begin() {return n;}I& end() {return i;}};
class range {private: struct I { int x; int operator*() { return x; }bool operator!=(I& lhs) { return x<lhs.x; }void operator++() { ++x; } }; I i, n;public:range(int n) :i({ 0 }), n({ n }) {}range(int i, int n) :i({ i }), n({ n }) {}I& begin() { return i; }I& end() { return n; }reverse_range operator!(){return reverse_range(*i,*n);}};

int N,S,T;
int R[112345];
int C[112345];
LL D[112345];
int latte[212345];
int malta=0;

constexpr LL INF = 1e16;
template<typename SEG> using SetInitialLeaf = function<void(SEG&, int)>;
template<typename SEG> using SetInitialSegment = function<void(SEG&, const int, const int)>;
template<typename RET, typename SEG> using GetSingleSegment = function<RET(SEG&, const int, const int)>;
template<typename RET> using GetMergedSegment = function<RET(RET, RET)>;
template<typename SEG, typename Q> using UpdateSingleSegment = function<void(SEG&, Q)>;
template<typename SEG> using LazyUpdate = function<void(SEG&, SEG&, SEG&)>;

struct node { LL ret;LL val; };

LazyUpdate<node>
lazy = [](node&v,node&l,node&r){
    if(l.ret!=INF)chmin(l.val,v.val);
    if(r.ret!=INF)chmin(r.val,v.val);
    v.val=INF;
};

SetInitialLeaf<node>
set_leaf = [](node &v, const int id) {
	v.ret = INF;
    v.val = INF;
};

SetInitialSegment<node>
set_segment = [](node &v, const int l, const int r) {
    v.ret= INF;
    v.val = INF;
};

GetSingleSegment<LL, node>
segment_min = [](node &v, const int l, const int r) {
    if(v.ret==INF)return INF;
    else return min(v.ret,v.val);
};

GetMergedSegment<LL>
merge_segment = [](LL l, LL r) {
	return l < r ? l : r;
};



UpdateSingleSegment<node, LL>
ret_update = [](node &v, LL l) {
	if (v.ret > l)v.ret = l;
};

UpdateSingleSegment<node, LL>
val_update = [](node &v, LL l) {
	if (v.val > l)v.val = l;
};


#ifndef NDBUF
#define NDBUF
template<typename T>
struct BufferManager {
	T *mem;
	int ptr;
	BufferManager(T* mem) {
		ptr = 0;
		this->mem = mem;
	}
	T* get(int m) {
		ptr += m;
		return mem + ptr - m;
	}
	void reset() {
		ptr = 0;
	}
};

namespace NodeBuffer {
	constexpr int BufferSize = 812345;
	using NodeType = node;
	NodeType mem[BufferSize];
	BufferManager<NodeType> buffer(mem);
}
#endif

template<typename Node, typename RET>
struct SegmentTree {
	int size;
	Node *seg;
	GetSingleSegment<RET, Node> get_single_segment;
	GetMergedSegment<RET> get_merged_segment;
	LazyUpdate<Node> lazy_update;
	void init(int l, int r, SetInitialSegment<Node>& init_segment, SetInitialLeaf<Node>& init_leaf, int k = 0) {
		auto &v = seg[k];
		init_segment(v, l, r);
		if (r - l == 1) {
			//葉の時の処理
			init_leaf(v, l);
		}
		else if (r - l>1) {
			int m = (l + r) / 2;
			init(l, m, init_segment, init_leaf, k * 2 + 1);
			init(m, r, init_segment, init_leaf, k * 2 + 2);
			v.ret = get_merged_segment(
				get_single_segment(seg[k * 2 + 1], l, m),
				get_single_segment(seg[k * 2 + 2], m, r)
			);
		}
	}
	SegmentTree(
		int n,
		GetSingleSegment<RET, Node> gss,
		GetMergedSegment<RET> gms,
		SetInitialSegment<Node> sis,
		SetInitialLeaf<Node> sil,
		LazyUpdate<Node> lu = [](Node &v,Node &l,Node &r){},
		BufferManager<Node>& buf = NodeBuffer::buffer
	)
		:get_single_segment(gss),
		get_merged_segment(gms),
		lazy_update(lu) {
		size = 1; while (size<n)size *= 2;
		seg = buf.get(size * 2 + 10);
		init(0, size, sis, sil);
	}
#define LQ a,b,k*2+1,l,m
#define RQ a,b,k*2+2,m,r
	RET get(int a, int b, int k, int l, int r) {
		if (a <= l && r <= b)return get_single_segment(seg[k], l, r);
		if (r - l > 1)lazy_update(seg[k], seg[2 * k + 1], seg[2 * k + 2]);
		int m = (l + r) / 2;
		bool ll = !(m <= a || b <= l);
		bool rr = !(r <= a || b <= m);
		RET ret;
		if (ll&&rr)ret = get_merged_segment(get(LQ), get(RQ));
		else if (ll)ret = get(LQ); else ret = get(RQ);
		seg[k].ret = get_merged_segment(
			get_single_segment(seg[k * 2 + 1], l, m),
			get_single_segment(seg[k * 2 + 2], m, r)
		);
		return ret;
	}
	RET get(int a, int b) {
		return get(a, b, 0, 0, size);
	}
	template<typename Q>
	void update(int a, int b, int k, int l, int r, UpdateSingleSegment<Node, Q> &update_segment, Q value) {
		if (r <= a || b <= l)return;
		if (a <= l && r <= b) {
			update_segment(seg[k], value);
		}
		else {
			if (r - l > 1)lazy_update(seg[k], seg[2 * k + 1], seg[2 * k + 2]);
			int m = (l + r) / 2;
			update(LQ, update_segment, value);
			update(RQ, update_segment, value);
			seg[k].ret = get_merged_segment(
				get_single_segment(seg[k * 2 + 1], l, m),
				get_single_segment(seg[k * 2 + 2], m, r)
			);
		}
	}
	template<typename Q>
	void update_segment(int a, int b, UpdateSingleSegment<Node, Q> &update_segment, Q value) {
		update(a, b, 0, 0, size, update_segment, value);
	}

	template<typename Q>
	void update_element(int a, UpdateSingleSegment<Node, Q> &update_segment, Q value) {
		update(a, a + 1, 0, 0, size, update_segment, value);
	}
};



int main(){
    cin>>N>>S>>T;
    S--;T--;
    for(int i:range(N)){
        cin>>R[i]>>C[i]>>D[i];
        latte[malta++]=R[i];
        latte[malta++]=C[i];
    }
    if(make_pair(R[S],C[S])>make_pair(R[T],C[T]))swap(S,T);
    sort(latte,latte+malta);
    malta=unique(latte,latte+malta)-latte;
    vector<vector<int>> o;
    for(int i:range(N)){
        R[i]=lower_bound(latte,latte+malta,R[i])-latte;
        C[i]=lower_bound(latte,latte+malta,C[i])-latte;
        o.push_back({R[i],C[i],i});
    }
    sort(ALL(o));
    LL ret=1e18;
    SegmentTree<node,LL> rmq(malta+10, segment_min, merge_segment, set_segment, set_leaf,lazy);
    for(int _:range(N)){
        const int i=o[_][2];
        LL x=rmq.get(0,C[i]+1)+D[i];
        if(i==S)x=0;
        rmq.update_element(C[i], ret_update, min(x,(LL)1e15));
        if(i==T){
            chmin(ret,x);
        }
        if(R[i]<=R[T]&&C[i]<=C[T]){
            chmin(ret,x+D[T]);
        }
        if(R[i]>=R[T]&&C[i]>=C[T]){
            chmin(ret,x+D[i]);
        }
        //cerr<<i+1<<" "<<R[i]<<" "<<C[i]<<" "<<x<<endl;
        if(D[i]==2){
            cerr << rmq.get(3,4)<<endl;
        }
        //cerr<<" "<<rmq.get(0,1)<<" "<<rmq.get(1,2)<<endl;
        rmq.update_segment(0,C[i]+1, val_update, x+D[i]);
        if(D[i]==2){
            //cerr << rmq.get(3,4)<<endl;
        }
    }
    cout<<ret<<endl;
    return 0;
}