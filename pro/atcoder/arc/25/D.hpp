#include<bits/stdc++.h>

using namespace std;
typedef long long LL;

#ifdef BTK
#define DEBUG if(1)
#else
#define CIN_ONLY if(1)
struct cww {cww() {CIN_ONLY{ios::sync_with_stdio(false); cin.tie(0);}}
}star;
#define DEBUG if(0)
#endif

#define ALL(v) (v).begin(),(v).end()
#define REC(ret, ...) std::function<ret (__VA_ARGS__)>
template <typename T>inline bool chmin(T &l, T r){bool a = l>r; if (a)l = r; return a;}
template <typename T>inline bool chmax(T &l, T r){bool a = l<r; if (a)l = r; return a;}
template <typename T>istream& operator>>(istream &is, vector<T> &v){for (auto &it : v)is >> it;return is;}

class range {private: struct I { int x; int operator*() { return x; }bool operator!=(I& lhs) { return x<lhs.x; }void operator++() { ++x; } }; I i, n;public:range(int n) :i({ 0 }), n({ n }) {}range(int i, int n) :i({ i }), n({ n }) {}I& begin() { return i; }I& end() { return n; }};

typedef LL D;
constexpr int S = 4;
struct M {
	int len;
	D v[S][S];
	D& operator()(int i, int j) {
		return v[i][j];
	}
}mat[60];
int H;
constexpr int mod = 1e9 + 7;
void mat_mul(M &a, M& b, M &c) {
	for (int i = 0; i < S; i++)	for (int j = 0; j < S; j++)c(i, j) = 0;
	if (a.len == 1 && b.len == 1) {
		for (int i : range(4)) {
			for (int j : range(4)) {
				c(i, j) += a(i, i)*b(j, j) % mod;
			}
		}
		for (int i : {0, 2}) {
			for (int j : {0, 2}) {
				c(i | 1, j | 1) += a(i, i)*b(j, j) % mod;
			}
		}
		for (int i : {0, 1}) {
			for (int j : {0, 1}) {
				c(i | 2, j | 2) += a(i, i)*b(j, j) % mod;
			}
		}
		c(3, 3) += a(0, 0)*b(0, 0);
	}
	else if (a.len == 1) {
		for (int i : range(4)) {
			for (int j : range(4)) {
				c(i, j) += a(i, i)*((b(0, j) + b(1, j) + b(2, j) + b(3, j)) % mod) % mod;
			}
		}
		for (int i : {0, 2}) {
			for (int j : range(4)) {
				c(i | 1, j) += a(i, i)*((b(0, j) + b(2, j)) % mod) % mod;
			}
		}
		for (int i : {0, 1}) {
			for (int j : range(4)) {
				c(i | 2, j) += a(i, i)*((b(0, j) + b(1, j)) % mod) % mod;
			}
		}
		for (int j : range(4)) {
			c(3, j) += a(0, 0)*b(0, j) % mod;
		}
	}
	else if (b.len == 1) {
		for (int i : range(4)) {
			for (int j : range(4)) {
				c(i, j) += b(j, j)*((a(i, 0) + a(i, 1) + a(i, 2) + a(i, 3)) % mod) % mod;
			}
		}
		for (int i : range(4)) {
			for (int j : {0, 2}) {
				c(i, j | 1) += b(j, j)*((a(i, 0) + a(i, 2)) % mod) % mod;
			}
		}
		for (int i : range(4)) {
			for (int j : {0, 1}) {
				c(i, j | 2) += b(j, j)*((a(i, 0) + a(i, 1)) % mod) % mod;
			}
		}
		for (int i : range(4)) {
			c(i, 3) += b(0, 0)*a(i, 0) % mod;
		}
	}
	else {
		for (int i : range(4)) {
			for (int j : range(4)) {
				D di = (a(i, 0) + a(i, 1)) % mod;
				D ui = (a(i, 0) + a(i, 2)) % mod;
				D dj = (b(0, j) + b(1, j)) % mod;
				D uj = (b(0, j) + b(2, j)) % mod;
				D alli = (a(i, 0) + a(i, 1) + a(i, 2) + a(i, 3)) % mod;
				D allj = (b(0, j) + b(1, j) + b(2, j) + b(3, j)) % mod;
				c(i, j) += alli * allj%mod;
				c(i, j) += ui * uj%mod;
				c(i, j) += di * dj%mod;
				c(i, j) += a(i, 0) * b(0, j) % mod;
				c(i, j) %= mod;
			}
		}
	}
	for (int i = 0; i < S; i++)	for (int j = 0; j < S; j++)c(i, j) %= mod;
	c.len = a.len + b.len;
}
void mayo() {
	if (H == 2) {
		for (int i : range(4))
			for (int j : range(4))
				mat[0](i, j) = 0;
		mat[0](0, 0) = 1;
		mat[0](3, 3) = 1;
	}
	else {
		for (int i : range(4))
			for (int j : range(4))
				mat[0](i, j) = 0;
		mat[0](2, 2) = 1;
	}
	mat[0].len = 1;
	for (int i : range(40)) {
		mat_mul(mat[i], mat[i], mat[i + 1]);
	}
}
M beet(int bit,LL len) {
	M x;
	for (int i : range(4))for (int j : range(4))x(i, j) = 0;
	x(bit, bit) = 1;
	x.len = 1;
	if (bit == 0) {
		x(3, 3) = 1;
	}
	int id = 0;
	while (len) {
		if (len & 1) {
			M y;
			mat_mul(x, mat[id], y);
			x = y;
		}
		len >>= 1;
		id++;
	}
	
	return x;
}
constexpr int MAX_N = 21234;
namespace Z {
	LL latte[MAX_N];
	int id;
	void init() {
		id = 0;
	}
	inline void set(LL v) {
		latte[id++] = v;
	}
	inline void build() {
		sort(latte, latte + id);
		id = unique(latte, latte + id) - latte;
	}
	inline int ItoZ(LL v) {
		return lower_bound(latte, latte + id, v) - latte;
	}
	inline LL ZtoI(int v) {
		return latte[v];
	}
}

LL s[MAX_N];
LL t[MAX_N];



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

struct node { M ret; };


SetInitialSegment<node>
set_segment = [](node &v, const int l, const int r) {};

GetSingleSegment<M, node>
seg = [](node &v, const int l, const int r) {
	return v.ret;
};

GetMergedSegment<M>
merge_segment = [](M l, M r) {
	M ret;
	mat_mul(l, r, ret);
	return ret;
};

UpdateSingleSegment<node, M>
force_update = [](node &v, M l) {
	v.ret = l;
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
	constexpr int BufferSize = 112345;
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
			//—t‚ÌŽž‚Ìˆ—
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
		LazyUpdate<Node> lu = [](Node &v, Node &l, Node &r) {},
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
		if (a <= l && r <= b)
			return get_single_segment(seg[k], l, r);
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
int c[112345];
int main() {
	Z::init();
	LL W; int N;
	cin >> H >> W >> N;
	mayo();
	Z::set(0);
	Z::set(W);
	for (int i : range(N)) {
		cin >> s[i] >> t[i];
		s[i]--; t[i]--;
		Z::set(t[i]);
	}
	Z::build();
	for (int i : range(N)) {
		t[i] = Z::ItoZ(t[i]);
	}
	int width = Z::id;
	SetInitialLeaf<node>
		set_leaf = [&](node &v, const int id) {
		if (id < width - 1) {
			if (H == 2) {
				v.ret = beet(0, Z::ZtoI(id + 1) - Z::ZtoI(id) - 1);
				c[id] = 0;
			}
			else {
				v.ret = beet(2, Z::ZtoI(id + 1) - Z::ZtoI(id) - 1);
				c[id] = 2;
			}
		}
	};
	SegmentTree<node, M> aizu(width,seg,merge_segment,set_segment,set_leaf);
	for (int i : range(N)) {
		c[t[i]] ^= (1 << s[i]);
		M new_mat = beet(c[t[i]], Z::ZtoI(t[i]+1) - Z::ZtoI(t[i]) - 1);
		aizu.update_element(t[i], force_update, new_mat);
		M ret_mat = aizu.get(0, width-1);
		LL ret = 0;
		for (int p : range(4))for (int q : range(4)) {
			ret += ret_mat(p, q);
		}
		cout << ret % mod << endl;
	}
	return 0;
}
