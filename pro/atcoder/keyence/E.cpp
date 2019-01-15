//https://atcoder.jp/contests/keyence2019/tasks/keyence2019_e
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

#ifndef VS
#include<bits/stdc++.h>
using namespace std;
#endif

/*
    default:: range minimum query
    - update(element) : chmin (weak update), set (force update) 
    - get   (segment) : min(l,r)
*/

constexpr int INF = 1e7;
template<typename SEG> using SetInitialLeaf = function<void(SEG&, int)>;
template<typename SEG> using SetInitialSegment = function<void(SEG&, const int, const int)>;
template<typename RET, typename SEG> using GetSingleSegment = function<RET(SEG&, const int, const int)>;
template<typename RET> using GetMergedSegment = function<RET(RET, RET)>;
template<typename SEG, typename Q> using UpdateSingleSegment = function<void(SEG&, Q)>;
template<typename SEG> using LazyUpdate = function<void(SEG&, SEG&, SEG&)>;

int N;
LL D;
LL A[212345];
struct ret{
    int id;
    int bid;
    LL y;
    LL b;
};
struct node { ret y;LL a;bool is_leaf;};
inline void update(node &v,LL a){
    chmin(v.a,a);
    if(v.is_leaf||v.y.y>v.a+v.y.b){
        v.y.y=v.a+v.y.b;
        v.y.id=v.y.bid;
    }
}

SetInitialLeaf<node>
set_leaf = [](node &v, const int id) {
    v.y.y=1e17;
    v.y.id = id;
	v.y.b = A[id%N];
    if(id<N)v.y.b+=D*(id%N);
    else v.y.b+=-D*(id%N);
    v.y.bid=id;
    v.a = 1e17;
    update(v,v.a);
};

SetInitialSegment<node>
set_segment = [](node &v, const int l, const int r) {
    v.a=1e17;
    v.is_leaf = (r-l==1);
};

GetSingleSegment<ret, node>
segment_min = [](node &v, const int l, const int r) {
    return v.y;
};

GetMergedSegment<ret>
merge_segment = [](ret l, ret r) {
	ret x;
    if(l.y<r.y){
        x.id=l.id;
        x.y=l.y;
    }
    else{
        x.id=r.id;
        x.y=r.y;
    }
    if(l.b<r.b){
        x.bid=l.bid;
        x.b=l.b;
    }
    else{
        x.bid=r.bid;
        x.b=r.b;
    }
    return x;
};

UpdateSingleSegment<node, LL>
update_b = [](node &v, LL l) {
	v.y.b = l;
    update(v,v.a);
};

UpdateSingleSegment<node, LL>
update_a = [](node &v, LL l) {
    update(v,l);
};
LazyUpdate<node>
lazy_update=[](node&v,node &l,node&r){
    update(l,v.a);
    update(r,v.a);
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
	constexpr int BufferSize = 1612345;
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
			v.y = get_merged_segment(
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
		seg[k].y = get_merged_segment(
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
			seg[k].y = get_merged_segment(
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
    cin>>N>>D;
    for(int i:range(N)){
        cin>>A[i];
    }
    SegmentTree<node,ret> st(2*N,segment_min,merge_segment, set_segment, set_leaf,lazy_update);
    auto update=[&](int id){
        st.update_element<LL>(id,update_b,1e17);
        st.update_element<LL>(id+N,update_b,1e17);
        if(id>0)st.update_segment<LL>(N,N+id,update_a,A[id]+id*D);
        if(id+1<N)st.update_segment<LL>(id+1,N,update_a,A[id]-id*D);
    };
    update(0);
    LL ret=0;
    for(int i:range(N-1)){
        auto ans = st.get(0,2*N);
        ret+=ans.y;
        update(ans.id%N);
        //cout<<ans.y<<" "<<ans.b<<" "<<ans.id<<endl;
    }
    cout<<ret<<endl;
    return 0;
}