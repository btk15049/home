#ifndef VS
#include<bits/stdc++.h>
#endif

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

constexpr int INF = 1e7;
template<typename SEG> using SetInitialLeaf = function<void(SEG&, int)>;
template<typename SEG> using SetInitialSegment = function<void(SEG&, const int, const int)>;
template<typename RET, typename SEG> using GetSingleSegment = function<RET(SEG&, const int, const int)>;
template<typename RET> using GetMergedSegment = function<RET(RET, RET)>;
template<typename SEG, typename Q> using UpdateSingleSegment = function<void(SEG&, Q)>;
template<typename SEG> using LazyUpdate = function<void(SEG&, SEG&, SEG&)>;
template<typename T>
struct BufferManager {
	T *mem;
	int ptr;
	BufferManager(T* buf) {
		ptr = 0;
		mem = buf;
	}
	T* get(int m) {
		ptr += m;
		return mem + ptr - m;
	}
	void reset() {
		ptr = 0;
	}
};
struct val {
	LL value, count;
};
struct result {
	val maxi, mini;
};
struct node {
	result ret;
	LL add_value;
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
		LazyUpdate<Node> lu,
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

int R, C, Q;
LL A[112345];
LL B[112345];
int main() {
	while (cin >> R >> C >> Q) {
		for (int i : range(R))cin >> A[i];
		for (int i : range(C))cin >> B[i];
		SegmentTree<node,result> latte(R ,
			[](node &v, const int l, const int r) {
				return result{
					val{ v.ret.maxi.value + v.add_value, v.ret.maxi.count },
					val{ v.ret.mini.value + v.add_value, v.ret.mini.count }
				}; },
			[](result l, result r) {
				return result{
					l.maxi.value == r.maxi.value ?
					val{l.maxi.value,l.maxi.count + r.maxi.count } :
					(l.maxi.value > r.maxi.value ? l.maxi : r.maxi) ,
					l.mini.value == r.mini.value ?
					val{ l.mini.value,l.mini.count + r.mini.count } :
					(l.mini.value < r.mini.value ? l.mini : r.mini)
				}; },
			[](node &v, const int l, const int r) {v.add_value = 0; },
			[&](node &v, const int id) {v.ret.maxi = v.ret.mini = val{ A[id],1ll }; },
			[](node &v, node &l, node &r) {
				l.add_value += v.add_value;
				r.add_value += v.add_value;
				v.add_value = 0;
			}
		);
		SegmentTree<node, result> malta(C,
			[](node &v, const int l, const int r) {
				return result{
					val{ v.ret.maxi.value + v.add_value, v.ret.maxi.count },
					val{ v.ret.mini.value + v.add_value, v.ret.mini.count }
				}; },
			[](result l, result r) {
				return result{
					l.maxi.value == r.maxi.value ?
					val{ l.maxi.value,l.maxi.count + r.maxi.count } :
					(l.maxi.value > r.maxi.value ? l.maxi : r.maxi) ,
					l.mini.value == r.mini.value ?
					val{ l.mini.value,l.mini.count + r.mini.count } :
					(l.mini.value < r.mini.value ? l.mini : r.mini)
				}; },
				[](node &v, const int l, const int r) {v.add_value = 0; },
				[&](node &v, const int id) {v.ret.maxi = v.ret.mini = val{ B[id],1ll }; },
				[](node &v, node &l, node &r) {
					l.add_value += v.add_value;
					r.add_value += v.add_value;
					v.add_value = 0; 
				}
		);
		UpdateSingleSegment<node, int> add_query = [](node &v, int value) {
			v.add_value += value;
		};
		for (int q : range(Q)) {
			cin >> q;
			if (q == 1) {
				int a, b, c;
				cin >> a >> b >> c;
				latte.update_segment(a - 1, b, add_query, c);
			}
			else if (q == 2) {
				int a, b, c;
				cin >> a >> b >> c;
				malta.update_segment(a - 1, b, add_query, c);
			}
			else if (q == 3) {
				int a, b, c, d;
				cin >> a >> b >> c >> d; a--; c--;
				auto l = latte.get(a, b);
				auto r = malta.get(c, d);
				LL min_value = min({
					l.mini.value*r.mini.value,
					l.maxi.value*r.mini.value,
					l.mini.value*r.maxi.value,
					l.maxi.value*r.maxi.value
					});
				LL count = 0;
				if (min_value == 0) {
					LL lx = b - a, rx = d - c;
					LL lc = 0, rc = 0;
					if (l.mini.value == 0)lc = l.mini.count;
					if (l.maxi.value == 0)lc = l.maxi.count;
					if (r.mini.value == 0)rc = r.mini.count;
					if (r.maxi.value == 0)rc = r.maxi.count;
					count = lx * rx - (lx - lc)*(rx - rc);
				}
				else {
					if (l.mini.value == l.maxi.value && r.mini.value == r.maxi.value) {
						count = (b - a) * 1ll * (d - c);
					}
					else if (l.mini.value == l.maxi.value || r.mini.value == r.maxi.value) {
						if (l.mini.value*r.mini.value == min_value)count += l.mini.count*r.mini.count;
						if (l.maxi.value*r.maxi.value == min_value)count += l.maxi.count*r.maxi.count;
					}
					else {
						if (l.mini.value*r.mini.value == min_value)count += l.mini.count*r.mini.count;
						if (l.maxi.value*r.mini.value == min_value)count += l.maxi.count*r.mini.count;
						if (l.mini.value*r.maxi.value == min_value)count += l.mini.count*r.maxi.count;
						if (l.maxi.value*r.maxi.value == min_value)count += l.maxi.count*r.maxi.count;
					}
				}
				cout << min_value << " " << count << "\n";
			}
			else if (q == 4) {
				int a, b, c, d;
				cin >> a >> b >> c >> d; a--; c--;
				auto l = latte.get(a, b);
				auto r = malta.get(c, d);
				LL max_value = max({
					l.mini.value*r.mini.value,
					l.maxi.value*r.mini.value,
					l.mini.value*r.maxi.value,
					l.maxi.value*r.maxi.value
					});
				LL count = 0;
				if (max_value == 0) {
					LL lx = b - a, rx = d - c;
					LL lc = 0, rc = 0;
					if (l.mini.value == 0)lc = l.mini.count;
					if (l.maxi.value == 0)lc = l.maxi.count;
					if (r.mini.value == 0)rc = r.mini.count;
					if (r.maxi.value == 0)rc = r.maxi.count;
					count = lx * rx - (lx - lc)*(rx - rc);
				}
				else {
					if (l.mini.value == l.maxi.value && r.mini.value == r.maxi.value) {
						count = (b - a) * 1ll * (d - c);
					}
					else if (l.mini.value == l.maxi.value || r.mini.value == r.maxi.value) {
						if (l.mini.value*r.mini.value == max_value)count += l.mini.count*r.mini.count;
						if (l.maxi.value*r.maxi.value == max_value)count += l.maxi.count*r.maxi.count;
					}
					else {
						if (l.mini.value*r.mini.value == max_value)count += l.mini.count*r.mini.count;
						if (l.maxi.value*r.mini.value == max_value)count += l.maxi.count*r.mini.count;
						if (l.mini.value*r.maxi.value == max_value)count += l.mini.count*r.maxi.count;
						if (l.maxi.value*r.maxi.value == max_value)count += l.maxi.count*r.maxi.count;
					}
				}
				cout << max_value << " " << count << "\n";
			}
		}

		NodeBuffer::buffer.reset();
	}
}

