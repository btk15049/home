//
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#ifdef BTK
#define DEBUG if(1)
#else
#define CIN_ONLY if(1)
#define DEBUG if(0)
#endif
#define ALL(v) (v).begin(),(v).end()
#define REC(ret, ...) std::function<ret (__VA_ARGS__)>
template <typename T>inline bool chmin(T &l, T r){bool a = l>r; if (a)l = r; return a;}
template <typename T>inline bool chmax(T &l, T r){bool a = l<r; if (a)l = r; return a;}
template <typename T>istream& operator>>(istream &is, vector<T> &v){for (auto &it : v)is >> it;return is;}
class reverse_range {private:struct I {int x;int operator*() {return x-1;}bool operator!=(I& lhs) {return x>lhs.x;}void operator++() {--x;}};I i, n;public:reverse_range(int n) :i({ 0 }), n({ n }){}reverse_range(int i, int n) :i({ i }), n({ n }){}I& begin() {return n;}I& end() {return i;}};
class range {private: struct I { int x; int operator*() { return x; }bool operator!=(I& lhs) { return x<lhs.x; }void operator++() { ++x; } }; I i, n;public:range(int n) :i({ 0 }), n({ n }) {}range(int i, int n) :i({ i }), n({ n }) {}I& begin() { return i; }I& end() { return n; }reverse_range operator!(){return reverse_range(*i,*n);}};

int N,Q;
char buf[212345];
string S;


/*
  sa[0]=n //空文字列
  lcp[i]:=suffix[sa[i]]とsuffix[sa[i+1]]の共通高さ
 */

namespace latte{
    void create_begin_bucket(vector<int>&v,vector<int>&bucket){
        fill(bucket.begin(),bucket.end(),0);
        for(int i=0;i<(int)v.size();i++)bucket[v[i]]++;
        int sum=0;
        for(int i=0;i<(int)bucket.size();i++){bucket[i]+=sum;swap(sum,bucket[i]);}
    }

    void create_end_bucket(vector<int>&v,vector<int>&bucket){
        fill(bucket.begin(),bucket.end(),0);
        for(int i=0;i<(int)v.size();i++)bucket[v[i]]++;
        for(int i=1;i<(int)bucket.size();i++)bucket[i]+=bucket[i-1];
    }

    void induced_sort(vector<int>&v,vector<int>&sa,int mv,vector<int>&bucket,vector<int>&is_l){
        create_begin_bucket(v,bucket);
        for(int i=0;i<(int)v.size();i++)if(sa[i]>0&&is_l[sa[i]-1])sa[bucket[v[sa[i]-1]]++]=sa[i]-1;
    }

    void invert_induced_sort(vector<int>&v,vector<int>&sa,int mv,vector<int>&bucket,vector<int>&is_l){
        create_end_bucket(v,bucket);
        for(int i=v.size()-1;i>=0;i--)if(sa[i]>0&&!is_l[sa[i]-1])sa[--bucket[v[sa[i]-1]]]=sa[i]-1;
    }

    vector<int>sa_is(vector<int>v,int mv){
        if(v.size()==1)return vector<int>(1,0);

        vector<int>is_l(v.size());
        vector<int>bucket(mv+1);
        vector<int>sa(v.size(),-1);
        auto is_lms=[&](int x)->bool{return x>0&&is_l[x-1]&&!is_l[x];};

        is_l[v.size()-1]=0;
        for(int i=v.size()-2;i>=0;i--)is_l[i]=v[i]>v[i+1]||(v[i]==v[i+1]&&is_l[i+1]);
        create_end_bucket(v,bucket);
        for(int i=0;i<(int)v.size();i++)if(is_lms(i))sa[--bucket[v[i]]]=i;
        induced_sort(v,sa,mv,bucket,is_l);
        invert_induced_sort(v,sa,mv,bucket,is_l);

        int cur=0;
        vector<int>order(v.size());
        for(int i=0;i<(int)v.size();i++)if(is_lms(i))order[i]=cur++;

        vector<int>next_v(cur);
        cur=-1;
        int prev=-1;
        for(int i=0;i<(int)v.size();i++){
            if(!is_lms(sa[i]))continue;
            bool diff=false;
            for(int d=0;d<v.size();d++){
                if(prev==-1||v[sa[i]+d]!=v[prev+d]||is_l[sa[i]+d]!=is_l[prev+d]){
                    diff=true;
                    break;
                }
                else if(d>0&&is_lms(sa[i]+d))break;
            }
            if(diff){cur++;prev=sa[i];}
            next_v[order[sa[i]]]=cur;
        }

        vector<int>re_order(next_v.size());
        for(int i=0;i<(int)v.size();i++)if(is_lms(i))re_order[order[i]]=i;
        vector<int>next_sa=sa_is(next_v,cur);
        create_end_bucket(v,bucket);
        for(int i=0;i<sa.size();i++)sa[i]=-1;
        for(int i=next_sa.size()-1;i>=0;i--)sa[--bucket[v[re_order[next_sa[i]]]]]=re_order[next_sa[i]];
        induced_sort(v,sa,mv,bucket,is_l);
        invert_induced_sort(v,sa,mv,bucket,is_l);
        return sa;
    }

    vector<int> sa_is(string &s){
        vector<int>v(s.size()+1);
        for(int i=0;i<(int)s.size();i++)v[i]=s[i];
        return sa_is(v,*max_element(v.begin(),v.end()));
    }

    
}
namespace SA {
    int n, k;
    int R[500000];
    int T[500000];
    bool compare_sa(int i, int j) {
        if (R[i] != R[j])return R[i] < R[j];
        else {
            int ri = i + k <= n ? R[i + k] : -1;
            int rj = j + k <= n ? R[j + k] : -1;
            return ri < rj;
        }
    }
    vector<int> construct_sa(string& S) {
        return latte::sa_is(S);
        n = S.size();
        vector<int> sa(n + 1);
        for (int i = 0; i <= n; i++) {
            sa[i] = i;
            R[i] = i < n ? S[i] : -1;
        }
 
        for (k = 1; k <= n; k *= 2) {
            sort(sa.begin(), sa.end(), compare_sa);
            T[sa[0]] = 0;
            for (int i = 1; i <= n; i++) 
                T[sa[i]] = T[sa[i - 1]] + (compare_sa(sa[i - 1], sa[i]) ? 1 : 0);
            for (int i = 0; i <= n; i++)
                R[i] = T[i];
        }
        return sa;
    }
    vector<int> construct_lcp(string& S, vector<int> &sa) {
        n = S.size();
        for (int i = 0; i <= n; i++)R[sa[i]] = i;
        int h = 0;
        vector<int> lcp(n + 1, 0);
        for (int i = 0; i < n; i++) {
            int j = sa[R[i] - 1];
            if (h > 0)h--;
            for (; j + h < n&&i + h < n; h++) {
                if (S[j + h] != S[i + h])break;
            }
            lcp[R[i] - 1] = h;
        }
        return lcp;
    }
}

int ret[212345];

vector<int> sa,lcp;
vector<int> id;


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
		constexpr int BufferSize = 5 * 1123456;
		using NodeType = int;
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
using RMQ_PTR=StaticRMQ::RMQ<int,decltype(lcp.begin())>;


inline pair<int,int> get_range(int pos,int len,RMQ_PTR&rmq){
    int lb=pos;
    int ub=pos+1;
    {
        int ok=pos;
        int ng=-1;
        while(abs(ok-ng)>1){
            const int mid=(ok+ng)/2;
            if(rmq.get(mid,pos)>=len){
                ok=mid;
            }
            else{
                ng=mid;
            }
        }
        chmin(lb,ok);
    }
    {
        int ok=pos;
        int ng=N+1;
        while(abs(ok-ng)>1){
            const int mid=(ok+ng)/2;
            if(rmq.get(pos,mid)>=len){
                ok=mid;
            }
            else{
                ng=mid;
            }
        }
        chmax(ub,ng);
    }
    return {lb,ub};
}


constexpr int INF = 1e7;
template<typename SEG> using SetInitialLeaf = function<void(SEG&, int)>;
template<typename SEG> using SetInitialSegment = function<void(SEG&, const int, const int)>;
template<typename RET, typename SEG> using GetSingleSegment = function<RET(SEG&, const int, const int)>;
template<typename RET> using GetMergedSegment = function<RET(RET, RET)>;
template<typename SEG, typename Q> using UpdateSingleSegment = function<void(SEG&, Q)>;
template<typename SEG> using LazyUpdate = function<void(SEG&, SEG&, SEG&)>;

struct node { vector<int> x; };

int query_lb;

SetInitialLeaf<node>
set_leaf = [](node &v, const int id) {
};

SetInitialSegment<node>
set_segment = [](node &v, const int l, const int r) {
    const int lb = l;
    const int ub = min(N+1,r);
    v.x.reserve(max(ub-lb,0)+1);
    for(int i:range(lb,ub)){
        v.x.push_back(sa[i]);
    }
    v.x.push_back(INF);
    sort(ALL(v.x));
};

GetSingleSegment<int, node>
segment_min = [](node &v, const int l, const int r) {
	return *lower_bound(ALL(v.x),query_lb);
};

GetMergedSegment<int>
merge_segment = [](int l, int r) {
	return l < r ? l : r;
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


#endif
namespace H {
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
		}
	}
	SegmentTree(
		int n,
		GetSingleSegment<RET, Node> gss,
		GetMergedSegment<RET> gms,
		SetInitialSegment<Node> sis,
		SetInitialLeaf<Node> sil,
		LazyUpdate<Node> lu = [](Node &v,Node &l,Node &r){},
		BufferManager<Node>& buf = H::buffer
	)
		:get_single_segment(gss),
		get_merged_segment(gms),
		lazy_update(lu) {
		size = 1; while (size<n)size *= 2;
		seg = buf.get(size * 2 + 10);
		init(0, size, sis, sil);
	}
    SegmentTree(){
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

SegmentTree<node,int> st;



inline bool check(int ql,int qr,int X_len,RMQ_PTR&rmq){
    if(X_len*3+3>qr-ql)return false;
    int lb,ub;
    tie(lb,ub)=get_range(id[ql],X_len,rmq);
    int p;
    {
        int X1=ql+X_len;
        query_lb = X1+1;
        p = st.get(lb,ub);
        int A1=p;
        int X2=p+X_len;
        if(X2>=N)return false;
        query_lb = X2+1;
        p = st.get(lb,ub);
        int A2=p;
        int X3=p+X_len;
        if(X3>=N)return false;
        int A3=qr;

        return A3-X3>=1;
    }
}





inline int solve(int ql,int qr,RMQ_PTR&rmq){
    int lb=0;
    int ub=qr-ql;
    while(ub-lb>1){
        const int mid = (lb+ub)/2;
        if(check(ql,qr,mid,rmq)){
            lb=mid;
        }
        else{
            ub=mid;
        }
    }
    return lb;
}




int main(){
    scanf("%d%d%s",&N,&Q,buf);
    reverse(buf,buf+N);
    S=buf;
    sa=SA::construct_sa(S);
    id=vector<int>(N+1);
    for(int i:range(N+1)){
        id[sa[i]]=i;
    }
    lcp=SA::construct_lcp(S,sa);
    RMQ_PTR rmq(lcp.begin(),lcp.end());
    st = SegmentTree<node,int>(N+1,segment_min, merge_segment, set_segment, set_leaf);


    for(int i:range(Q)){
        int l,r;
        scanf("%d%d",&l,&r);


        ret[i]=solve(N-r,N-l+1,rmq);
    }
    for(int i:range(Q)){
        printf("%d\n",ret[i]);
    }
    return 0;
}