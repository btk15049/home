//https://beta.atcoder.jp/contests/code-festival-2018-final/tasks/code_festival_2018_final_e
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

struct node {
    int ret;
    int lazy;
};

SetInitialLeaf<node>
set_leaf = [](node &v, const int id) {
	v.ret = 0;
    v.lazy = 0;
};

SetInitialSegment<node>
set_segment = [](node &v, const int l, const int r) {
    v.ret=0;
    v.lazy=0;
};

GetSingleSegment<int, node>
segment_max = [](node &v, const int l, const int r) {
	return v.ret+v.lazy;
};

GetMergedSegment<int>
merge_segment = [](int l, int r) {
	return l > r ? l : r;
};

UpdateSingleSegment<node, int>
update = [](node &v, int l) {
	v.lazy += l;
};

LazyUpdate<node>
lazy_update = [](node& v,node &l,node &r){
    l.lazy+=v.lazy;
    r.lazy+=v.lazy;
    v.lazy=0;
};

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


/* %% how to use %%
int main(){
    int n = 100;
    init
    SegmentTree<node,int> rmq(n, segment_min, merge_segment, set_segment, set_leaf);

    set
    rmq.update_element(20, force_update, 1); // INF -> 1
    rmq.update_element(40, force_update, 4); // INF -> 4
    rmq.update_element(40, force_update, 6); // 4 -> 6
    rmq.update_element(60, force_update, 7); // INF -> 7

    chmin
    rmq.update_element(30, weak_update, 10); // INF -> 10
    rmq.update_element(40, weak_update, 10); // 6 -> 6 (because, 6<10)
    rmq.update_element(30, weak_update, 3);  // 7 -> 3

    // get [l,r)
    int q = rmq.get(31,45); // 3
}

*/


priority_queue<pair<LL,int>> que;
inline void PUSH(LL c,int i){
    que.push({-c,i});
}
inline void TOP(LL& c,int& i){
    tie(c,i)=que.top();
    c=-c;
}

int main(){
    int N,K;
    cin>>N>>K;
    SegmentTree<node,int> st(N+10,segment_max, merge_segment, set_segment, set_leaf,lazy_update);
    LL ret=0;
    for(int i:range(N)){
        LL A;
        cin>>A;
        PUSH(A,i);
        while(1){
            LL c;
            int pos;
            TOP(c,pos);
            int k = st.get(pos,i+1);
            if(k<K)break;
            else que.pop();
        }
        {
            LL c;int pos;
            TOP(c,pos);
            st.update_segment(pos,i+1,update,1);
            ret+=c;
        }
    }
    cout<<ret<<endl;
    return 0;
}