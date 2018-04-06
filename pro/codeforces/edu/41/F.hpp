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

namespace latte {
	void create_begin_bucket(vector<int>&v, vector<int>&bucket) {
		fill(bucket.begin(), bucket.end(), 0);
		for (int i = 0; i<(int)v.size(); i++)bucket[v[i]]++;
		int sum = 0;
		for (int i = 0; i<(int)bucket.size(); i++) { bucket[i] += sum; swap(sum, bucket[i]); }
	}

	void create_end_bucket(vector<int>&v, vector<int>&bucket) {
		fill(bucket.begin(), bucket.end(), 0);
		for (int i = 0; i<(int)v.size(); i++)bucket[v[i]]++;
		for (int i = 1; i<(int)bucket.size(); i++)bucket[i] += bucket[i - 1];
	}

	void induced_sort(vector<int>&v, vector<int>&sa, int mv, vector<int>&bucket, vector<int>&is_l) {
		create_begin_bucket(v, bucket);
		for (int i = 0; i<(int)v.size(); i++)if (sa[i]>0 && is_l[sa[i] - 1])sa[bucket[v[sa[i] - 1]]++] = sa[i] - 1;
	}

	void invert_induced_sort(vector<int>&v, vector<int>&sa, int mv, vector<int>&bucket, vector<int>&is_l) {
		create_end_bucket(v, bucket);
		for (int i = v.size() - 1; i >= 0; i--)if (sa[i]>0 && !is_l[sa[i] - 1])sa[--bucket[v[sa[i] - 1]]] = sa[i] - 1;
	}

	vector<int>sa_is(vector<int>v, int mv) {
		if (v.size() == 1)return vector<int>(1, 0);

		vector<int>is_l(v.size());
		vector<int>bucket(mv + 1);
		vector<int>sa(v.size(), -1);
		auto is_lms = [&](int x)->bool {return x>0 && is_l[x - 1] && !is_l[x]; };

		is_l[v.size() - 1] = 0;
		for (int i = v.size() - 2; i >= 0; i--)is_l[i] = v[i]>v[i + 1] || (v[i] == v[i + 1] && is_l[i + 1]);
		create_end_bucket(v, bucket);
		for (int i = 0; i<(int)v.size(); i++)if (is_lms(i))sa[--bucket[v[i]]] = i;
		induced_sort(v, sa, mv, bucket, is_l);
		invert_induced_sort(v, sa, mv, bucket, is_l);

		int cur = 0;
		vector<int>order(v.size());
		for (int i = 0; i<(int)v.size(); i++)if (is_lms(i))order[i] = cur++;

		vector<int>next_v(cur);
		cur = -1;
		int prev = -1;
		for (int i = 0; i<(int)v.size(); i++) {
			if (!is_lms(sa[i]))continue;
			bool diff = false;
			for (int d = 0; d<v.size(); d++) {
				if (prev == -1 || v[sa[i] + d] != v[prev + d] || is_l[sa[i] + d] != is_l[prev + d]) {
					diff = true;
					break;
				}
				else if (d>0 && is_lms(sa[i] + d))break;
			}
			if (diff) { cur++; prev = sa[i]; }
			next_v[order[sa[i]]] = cur;
		}

		vector<int>re_order(next_v.size());
		for (int i = 0; i<(int)v.size(); i++)if (is_lms(i))re_order[order[i]] = i;
		vector<int>next_sa = sa_is(next_v, cur);
		create_end_bucket(v, bucket);
		for (int i = 0; i<sa.size(); i++)sa[i] = -1;
		for (int i = next_sa.size() - 1; i >= 0; i--)sa[--bucket[v[re_order[next_sa[i]]]]] = re_order[next_sa[i]];
		induced_sort(v, sa, mv, bucket, is_l);
		invert_induced_sort(v, sa, mv, bucket, is_l);
		return sa;
	}

	vector<int> sa_is(string &s) {
		vector<int>v(s.size() + 1);
		for (int i = 0; i<(int)s.size(); i++)v[i] = s[i];
		return sa_is(v, *max_element(v.begin(), v.end()));
	}


}
namespace SA {
	int n, k;
	int R[1123456];
	int T[1123456];
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
			BufferManager<T> &bf = Buffer::buffer
			, MergeFunction<T> f = getMin<T>)
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
					int ret = tmp[i];
					(*p) = ret; ++p;
					for (int j = i + 1; j < 4; j++) {
						ret = Merge(ret,tmp[j]);
						(*p) = ret; ++p;
					}
				}
			}
		}
		SmallRMQ(ITR bg, ITR ed,
			BufferManager<T> &bf = Buffer::buffer
			, MergeFunction<T> f = getMin<T>)
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
			return S(workspace, workspace+size, bf, Merge);
		}
		RMQ(ITR bg, ITR ed,
			BufferManager<T> &bf = Buffer::buffer
			, MergeFunction<T> f = getMin<T>)
			: n(((distance(bg, ed) + 15) >> 4) << 4),
			Merge(f),
			workspace(bf.get(n >> 2)),
			small(bg, ed, bf, f),
			medium(buildBlock<SmallRMQ<T, T*>, ITR>(bg, ed, bf, n >> 2)),
			large(buildBlock<SparseTable<T, T*>, T*>(workspace, workspace + (n >> 2), bf, n >> 4))
		{}
		inline T get(int l, int r) {
			int nl = (l >> 2) + 1;
			int nr = ((r - 1) >> 2);
			int ret = small.get(l, min(nl << 2, r));
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

int a[1123456];
int id[1123456];
int main() {
	int n;
	string s;
	cin >> n >> s;
	int loop = (n + 1) / 2;
	string t(loop, ' ');
	t.back() = '\n';
	auto sa = SA::construct_sa(s);
	auto lcp = SA::construct_lcp(s, sa);
	for (int i : range(lcp.size()))a[i] = lcp[i];
	for (int i : range(sa.size())) {
		id[sa[i]] = i;
	}
	StaticRMQ::RMQ<int,int*> rmq(a, a + lcp.size());
	auto check = [&](int l, int r, int len) {
		l = id[l];
		r = id[r];
		if (l > r)swap(l, r);
		return rmq.get(l, r) >= len;
	};
	vector<int> ret(loop,-1);
	for (int i : range(n/2)) {
		int j = n - 1 - i;
		if (s[i] != s[j])continue;
		int lb = 0;
		int ub = i + 1;
		while (ub - lb > 1) {
			const int mid = (lb + ub) / 2;
			(check(i-mid,j-mid,mid*2+1) ? lb : ub) = mid; 
		}
		chmax(ret[i - lb], lb * 2 + 1);
	}
	for (int i : range(1, loop))chmax(ret[i], ret[i - 1] - 2);
	for (int i : range(loop))cout << ret[i] << t[i];

	return 0;
}
