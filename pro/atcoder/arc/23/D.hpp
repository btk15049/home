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

LL gcd(LL a, LL b) {
	return (b == 0) ? a : gcd(b, a%b);
}
namespace StaticRMQ {
	/*
	default:: range minimum query
	*/

	template<typename T>
	using MergeFunction = function<T(T, T)>;

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

	MergeFunction<LL>
		getGCD = [](LL l, LL r) {
		return gcd(l, r);
	};


	template<typename T>
	class BufferManager {
	private:
		T * const mem;
		int ptr;
	public:
		BufferManager(T* buf) :mem(buf) {
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

	namespace Buffer {
		// if N<=10^6 : BufferSize is enough for 5 * N
		constexpr int BufferSize = 5 * 112345;
		using NodeType = LL;
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
			: n(distance(bg, ed)),
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
	struct SmallRMQ {
		const int n;
		T* const mem;
		MergeFunction<T> Merge;
		void build(ITR bg, ITR ed) {
			int x = distance(bg, ed);
			for (auto p = mem; x > 0; x -= 4) {
				T tmp[4];
				tmp[0] = (*bg); ++bg;
				if (x >= 1)tmp[1] = (*bg); ++bg;
				if (x >= 2)tmp[2] = (*bg); ++bg;
				if (x >= 3)tmp[3] = (*bg); ++bg;
				for (int i = 0; i < 4; i++) {
					int ret = tmp[i];
					(*p) = ret; ++p;
					for (int j = i + 1; j < 4; j++) {
						ret = Merge(ret, tmp[j]);
						(*p) = ret; ++p;
					}
				}
			}
		}
		SmallRMQ(ITR bg, ITR ed,
			MergeFunction<T> f = getMin<T>,
			BufferManager<T> &bf = Buffer::buffer
		)
			: n(((distance(bg, ed) + 3) >> 2) << 2),
			mem(bf.get((n >> 2) * 10)),
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
			for (int x = distance(bg, ed); x > 0; ++p, x -= 4) {
				(*p) = (*bg); ++bg;
				if (x >= 1)(*p) = Merge(*p, *bg); ++bg;
				if (x >= 2)(*p) = Merge(*p, *bg); ++bg;
				if (x >= 3)(*p) = Merge(*p, *bg); ++bg;
			}
			return S(workspace, workspace + size, Merge, bf);
		}
		RMQ(ITR bg, ITR ed,
			MergeFunction<T> f = getMin<T>,
			BufferManager<T> &bf = Buffer::buffer
		) : n(((distance(bg, ed) + 15) >> 4) << 4),
			Merge(f),
			workspace(bf.get(n >> 2)),
			small(bg, ed, f, bf),
			medium(buildBlock<SmallRMQ<T, T*>, ITR>(bg, ed, bf, n >> 2)),
			large(buildBlock<SparseTable<T, T*>, T*>(workspace, workspace + (n >> 2), bf, n >> 4))
		{}
		inline T get(int l, int r) {
			int nl = (l >> 2) + 1;
			int nr = ((r - 1) >> 2);
			int ret = small.get(l, min(nl << 2, r));
			ret = Merge(ret, small.get(max(l, nr << 2), r));
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

LL a[112345];
int main() {
	map<LL, LL> ret;

	int n, m;
	cin >> n >> m;
	for (int i : range(n))cin >> a[i];
	StaticRMQ::RMQ<LL, LL*> rmq(a, a + n, StaticRMQ::getGCD);
	for (int i : range(n)) {
		int k = i;
		while (k < n) {
			int lb = k;
			int ub = n;
			LL g = rmq.get(i, k+1);
			while (ub - lb > 1) {
				const int mid = (ub + lb) / 2;
				(rmq.get(i, mid+1) == g ? lb : ub) = mid;
			}
			ret[g] += ub - k;
			k = ub;
		}
	}
	while (m--) {
		LL x;
		cin >> x;
		cout << ret[x] << endl;
	}

	return 0;
}
