//https://beta.atcoder.jp/contests/code-festival-2018-final/tasks/code_festival_2018_final_f
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

struct val{int bot,top;};
struct node { val ret;int lazy; };

SetInitialLeaf<node>
set_leaf = [](node &v, const int id) {
	v.ret.bot = 0;
    v.ret.top = 0;
};

SetInitialSegment<node>
set_segment = [](node &v, const int l, const int r) {
    v.lazy = 0;
};

GetSingleSegment<val, node>
segment_min = [](node &v, const int l, const int r) {
	return val{v.ret.bot+v.lazy,v.ret.top+v.lazy};
};

GetMergedSegment<val>
merge_segment = [](val l, val r) {
	return val{
        l.bot < r.bot ? l.bot : r.bot,
        l.top > r.top ? l.top : r.top,
    };
};

UpdateSingleSegment<node, val>
update_element = [](node &v, val l) {
	v.ret = l;
};

UpdateSingleSegment<node, int>
range_add = [](node &v, int l) {
	v.lazy += l;
};

LazyUpdate<node>
lazy_update = [](node &v,node &l,node &r){
    l.lazy+=v.lazy;
    r.lazy+=v.lazy;
    v.lazy=0;
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

namespace ForHeap{
    constexpr int BufferSize = 812345;
    using Type = pair<int,int>;
    Type mem[BufferSize];
    BufferManager<Type> buffer(mem);
};

template<typename T>
struct IntervalHeap{
    T* h;
    int size;
    IntervalHeap(){}
    IntervalHeap(int reserved_size, BufferManager<T>& buf = NodeBuffer::buffer){
        h = buf.get(reserved_size);
        size = 0;
    }
    inline void inner_swap(int a,int b){
        std::swap(h[a],h[b]);
    }
    inline void heap_down(){
        int p;
        for(p=1;(p<<1)+3<size;){
            if(h[p-1]>h[p])inner_swap(p-1,p);
            int s=p-1,t=p<<1;
            if(h[s]>h[t]||h[s]>h[t+2]){
                if(h[t]>h[t+2])t+=2;
            }
            else if(h[++s]<h[++t]||h[s]<h[t+2]){
                if(h[t]<h[t+2])t+=2;
            }
            else return;
            inner_swap(s,t);
            p=t|1;
        }
        if(h[p-1]>h[p])inner_swap(p-1,p);
        for(int i=0,t=(p<<1);i<2&&t<size;i++,t+=2)if(h[p-1]>h[t])inner_swap(p-1,t);
        for(int i=0,t=(p<<1)+1;i<2&&t<size;i++,t+=2)if(h[p]<h[t])inner_swap(p,t);
        for(int t=(p<<1);t+1<size;t+=2)if(h[t]>h[t+1])inner_swap(t,t+1);
    }
   inline void push(T t){
        int n,p;
        h[n=size++]=t;
        if(n&1){if(h[n-1]>h[n]){inner_swap(n-1,n);n--;}}
        else if(n>0){
            p=(n-((n^2)&2))>>1;
            if(h[n]>h[p]){inner_swap(n,p);n=p;}
            else if(h[n]<h[p-1]){inner_swap(n,p-1);n=p-1;}
            else return;
        }
        else return;
        if(n&1){
            for (;n>1;n=p)
                if(h[p=(n-((n^2)&2))>>1]<h[n])inner_swap(p,n);
                else break;
        }
        else{
            for(;n>1;n=p)
                if(h[p=((n-((n^2)&2))>>1)-1]>h[n])inner_swap(p,n);
                else break;
        }
    }
    inline void pop(int x){
        inner_swap(x,size-1);
        if(--size>2)heap_down();
    }
    /*methods*/
    inline bool is_empty(){return size==0;}
    inline T get_min(){return h[0];}
    inline T get_max(){return h[size==1?0:1];}
    inline void pop_min(){pop(0);}
    inline void pop_max(){pop(1);}
    inline void clear(){size=0;}
};
int N,K;
IntervalHeap<ForHeap::Type> que[2];
int main(){
    cin>>N>>K;
    int now = 0;
    LL ret = 0;
    que[0]=IntervalHeap<pair<int,int>>(N+10,ForHeap::buffer);
    que[1]=IntervalHeap<pair<int,int>>(N+10,ForHeap::buffer);
    SegmentTree<node,val> st(N+10,segment_min,merge_segment,set_segment,set_leaf,lazy_update);
    for(int i:range(N)){
        string T;int a;
        cin>>T>>a;
        int t=T[0]-'0';
        if(t==1){
            while(now==K&&que[t].is_empty()==false&&que[t].get_min().first<a){
                auto p = que[t].get_min();
                int val,id;tie(val,id)=p;
                if(st.get(id,N).bot==0){
                    que[t].pop_min();
                    continue;
                }
                que[t].pop_min();
                ret-=val;
                now--;
                st.update_segment(id,N,range_add,-1);
                break;
            }
            if(now<K){
                que[t].push({a,i});
                now++;
                ret+=a;
                st.update_segment(i,N,range_add,1);
            }
        }
        else{
            while(now==0&&que[t].is_empty()==false&&que[t].get_min().first<a){
                auto p = que[t].get_min();
                int val,id;tie(val,id)=p;
                if(st.get(id,N).top==K){
                    que[t].pop_min();
                    continue;
                }
                que[t].pop_min();
                ret-=val;
                now++;
                st.update_segment(id,N,range_add,1);
                break;
            }
            if(now>0){
                que[t].push({a,i});
                now--;
                ret+=a;
                st.update_segment(i,N,range_add,-1);
            }
        }
    }
    cout<<ret<<endl;
    return 0;
}