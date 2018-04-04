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

constexpr int MAX_N = 812345;
struct P{
	int r, c;
};
istream& operator>>(istream &is, P &v) { is >> v.r >> v.c; return is; }

P S, T;
int N;
P in[MAX_N];
namespace Z{
	int latte[MAX_N];
	int id;
	void init() {
		id = 0;
	}
	inline void set(int v) {
		latte[id++] = v;
	}
	inline void build() {
		sort(latte, latte + id);
		id = unique(latte, latte + id) - latte;
	}
	inline int ItoZ(int v) {
		return lower_bound(latte, latte + id, v) - latte;
	}
	inline int ZtoI(int v) {
		return latte[v];
	}
}

bool input() {
	if(cin >> S >> T);
	else return false;
	cin >> N;
	Z::init();
	for (int j : {-1, 0, 1}) {
		Z::set(S.r + j);
		Z::set(S.c + j);
		Z::set(T.r + j);
		Z::set(T.c + j);
	}
	for (int i : range(N)) {
		cin >> in[i];
		for (int j : {-1, 0, 1}) {
			Z::set(in[i].r + j);
			Z::set(in[i].c + j);
		}
	}
	Z::build();
	S.r = Z::ItoZ(S.r);	S.c = Z::ItoZ(S.c);
	T.r = Z::ItoZ(T.r);	T.c = Z::ItoZ(T.c);
	for (int i : range(N)) {
		in[i].r = Z::ItoZ(in[i].r);
		in[i].c = Z::ItoZ(in[i].c);
	}
#ifdef BTK
	cout << S.r << " " << S.c << endl;
	cout << T.r << " " << T.c << endl;
	cout << N << endl;
	for (int i : range(N)) {
		cout << in[i].r << " " << in[i].c << endl;
	}
#endif
	return true;
}
typedef vector<int> V;
typedef vector<V> VV;
typedef vector<VV> VVV;
constexpr int dr[4] = { 1,0,0,-1 };
constexpr int dc[4] = { 0,1,-1,0 };
const string ds = { "DRLU" };
struct Tate {
	static constexpr int index = 0;
	static inline bool comp(const int lr, const int lc, const int rr, const int rc) {
		return lr == rr ? lc < rc : lr < rr;
	}
};
struct Yoko {
	static constexpr int index = 1;
	static inline bool comp(const int lr, const int lc, const int rr, const int rc) {
		return lc == rc ? lr < rr : lc < rc;
	}
};

namespace pts {
	int pt[2][MAX_N];
	int cr[MAX_N];
	template<typename dir>
	inline bool ice_comp(const int li, const int ri) {
		return dir::comp(in[li].r, in[li].c, in[ri].r, in[ri].c);
	}
	void build() {
		iota(pt[Yoko::index], pt[Yoko::index] + N, 0);
		iota(pt[Tate::index], pt[Tate::index] + N, 0);
		sort(pt[Yoko::index], pt[Yoko::index] + N, ice_comp<Yoko>);
		sort(pt[Tate::index], pt[Tate::index] + N, ice_comp<Tate>);
	}
	template<typename dir>
	inline int lower_bound(int r, int c) {
		int lb = -1, ub = N;
		while (ub - lb > 1) {
			const int mid = (lb + ub) / 2;
			(!dir::comp(r, c, in[pt[dir::index][mid]].r, in[pt[dir::index][mid]].c) ? lb : ub) = mid;
		}
		return ub;
	}
	inline bool isIce(int r, int c) {

		int id = lower_bound<Yoko>(r, c);
		return id != N && in[pt[Yoko::index][id]].r == r && in[pt[Yoko::index][id]].c == c;
	}
}

struct Down {
	static constexpr int index = 0;
	static inline int getIce(int r, int c) {
		int id = pts::lower_bound<Yoko>(r, c);
		if (id != N && in[pts::pt[Yoko::index][id]].c == c)
			return pts::pt[Yoko::index][id];
		else return -1;
	}
};

struct Right {
	static constexpr int index = 1;
	static inline int getIce(int r, int c) {
		int id = pts::lower_bound<Tate>(r, c);
		if (id != N && in[pts::pt[Tate::index][id]].r == r)
			return pts::pt[Tate::index][id];
		else return -1;
	}
};
struct Left {
	static constexpr int index = 2;
	static inline int getIce(int r, int c) {
		int id = pts::lower_bound<Tate>(r, c) - 1;
		if (id != -1 && in[pts::pt[Tate::index][id]].r == r)
			return pts::pt[Tate::index][id];
		else return -1;
	}
};
struct Up {
	static constexpr int index = 3;
	static inline int getIce(int r, int c) {
		int id = pts::lower_bound<Yoko>(r, c) - 1;
		if (id != -1 && in[pts::pt[Yoko::index][id]].c == c)
			return pts::pt[Yoko::index][id];
		else return -1;
	}
};
		
inline bool isReachable(int r,int c,int nr,int nc) {
	if (r == nr) {
		if (c < nc) {
			const int id = Right::getIce(r, c);
			return id == -1 || nc < in[id].c;
		}
		else if (nc < c) {
			const int id = Left::getIce(r, c);
			return id == -1 || in[id].c < nc;
		}
		else return true;
	}
	else if (c == nc) {
		if (r < nr) {
			const int id = Down::getIce(r, c);
			return id == -1 || nr < in[id].r;
		}
		else if (nr < r) {
			const int id = Up::getIce(r, c);
			return id == -1 || in[id].r < nr;
		}
		else return true;
	}
	else return false;
}


vector<P> g[MAX_N][4];
vector<P> rg[MAX_N][4];

int dist[MAX_N][4];
int rdist[MAX_N][4];
template<typename dir> 
inline void addArc(const int i, const int j, const int r,const int c) {
	const int id = dir::getIce(r, c);
	if (id != -1) {
		g[i][j].push_back(P{ id,3 - dir::index });
		rg[id][3 - dir::index].push_back(P{ i,j });
	}
}
void buildGraph(){
	for (int i : range(N)) {
		for (int d : range(4)) {
			int r = in[i].r + dr[d];
			int c = in[i].c + dc[d];
			if (pts::isIce(r, c))continue;
			addArc<Down>(i, d, r, c);
			addArc<Up>(i, d, r, c);
			addArc<Left>(i, d, r, c);
			addArc<Right>(i, d, r, c);
		}
	}
}
template<typename dir>
void uku(){
	int id = dir::getIce(S.r, S.c);
	if (id != -1) {
		const int r = in[id].r + dr[3 - dir::index];
		const int c = in[id].c + dc[3 - dir::index];
		dist[id][3 - dir::index] = (S.r != r || S.c != c);
	}
}

constexpr int INF = 1e7;
queue<P> que;
void bfs() {
	uku<Down>();
	uku<Left>();
	uku<Right>();
	uku<Up>();
	for (int i : range(N)) {
		for (int d : range(4)) {
			if (dist[i][d] == 0)que.push(P{ i,d });
		}
	}
	for (int i : range(N)) {
		for (int d : range(4)) {
			if (dist[i][d] == 1)que.push(P{ i,d });
		}
	}
	while (!que.empty()) {
		int i = que.front().r;
		int j = que.front().c;
		que.pop();
		for (auto &it : g[i][j]) {
			int ni = it.r;
			int nj = it.c;
			if (chmin(dist[ni][nj], dist[i][j] + 1)) {
				que.push(it);
			}
		}
	}
	for (int i : range(N)) {
		for (int d : range(4)) {
			const int r = in[i].r + dr[d];
			const int c = in[i].c + dc[d];
			if (isReachable(r, c, T.r, T.c)) {
				rdist[i][d] = 0;
				que.push(P{ i,d });
			}
		}
	}
	while (!que.empty()) {
		int i = que.front().r;
		int j = que.front().c;
		que.pop();
		for (auto &it : rg[i][j]) {
			int ni = it.r;
			int nj = it.c;
			if (chmin(rdist[ni][nj], rdist[i][j] + 1)) {
				que.push(it);
			}
		}
	}
}

template<typename SEG> using SetInitialLeaf = function<void(SEG&, int)>;
template<typename SEG> using SetInitialSegment = function<void(SEG&, const int, const int)>;
template<typename RET, typename SEG> using GetSingleSegment = function<RET(SEG&, const int, const int)>;
template<typename RET> using GetMergedSegment = function<RET(RET, RET)>;
template<typename SEG, typename Q> using UpdateSingleSegment = function<void(SEG&, Q)>;

struct node { int ret; };

SetInitialLeaf<node>
set_leaf = [](node &v, const int id) {
	v.ret = INF;
};

SetInitialSegment<node>
set_segment = [](node &v, const int l, const int r) {};

GetSingleSegment<int, node>
segment_min = [](node &v, const int l, const int r) {
	return v.ret;
};

GetMergedSegment<int>
merge_segment = [](int l, int r) {
	return l < r ? l : r;
};

UpdateSingleSegment<node, int>
force_update = [](node &v, int l) {
	v.ret = l;
};

UpdateSingleSegment<node, int>
weak_update = [](node &v, int l) {
	if (v.ret > l)v.ret = l;
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
		BufferManager<Node> buf = NodeBuffer::buffer
	)
		:get_single_segment(gss),
		get_merged_segment(gms) {
		size = 1; while (size<n)size *= 2;
		seg = buf.get(size + 10);
		init(0, size, sis, sil);
	}
#define LQ a,b,k*2+1,l,m
#define RQ a,b,k*2+2,m,r
	RET get(int a, int b, int k, int l, int r) {
		if (a <= l && r <= b)return get_single_segment(seg[k], l, r);
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

int ret = INF;
void solve_down() {
	constexpr int dir = Down::index;
	constexpr int s = Left::index;
	SegmentTree<node, int> rmq(Z::id, segment_min, merge_segment, set_segment, set_leaf);
	auto query = [&](int l, int r) {
		if (r - l >= 1)return rmq.get(l, r);
		else return INF;
	};
	for (int lb = 0; lb < N;) {
		int ub = lb;
		int* pt = pts::pt[Tate::index];
		while (ub < N&&
			in[pt[lb]].r == in[pt[ub]].r) {
			ub++;
		}
		chmin(ret, rdist[pt[lb]][s] + query(0, in[pt[lb]].c) + 1);
		for (int i : range(lb, ub-1)) {
			const int seg_cost = query(in[pt[i]].c + 1, in[pt[i + 1]].c);
			chmin(ret, rdist[pt[i]][3 - s] + seg_cost + 1);
			chmin(ret, rdist[pt[i + 1]][s] + seg_cost + 1);
		}
		chmin(ret, rdist[pt[ub - 1]][3 - s] + query(in[pt[ub - 1]].c + 1, Z::id) + 1);
		for (int i : range(lb, ub)) {
			rmq.update_element(in[pt[i]].c, force_update, dist[pt[i]][dir]);
			rmq.update_element(in[pt[i]].c + dc[s], weak_update, dist[pt[i]][s]);
			rmq.update_element(in[pt[i]].c + dc[3 - s], weak_update, dist[pt[i]][3 - s]);
		}
		lb = ub;
	}
	NodeBuffer::buffer.reset();
}

void solve_right() {
	constexpr int dir = Right::index;
	constexpr int s = Up::index;
	SegmentTree<node, int> rmq(Z::id, segment_min, merge_segment, set_segment, set_leaf);
	auto query = [&](int l, int r) {
		if (r - l >= 1)return rmq.get(l, r);
		else return INF;
	};
	for (int lb = 0; lb < N;) {
		int ub = lb;
		int* pt = pts::pt[Yoko::index];
		while (ub < N&&
			in[pt[lb]].c == in[pt[ub]].c) {
			ub++;
		}
		chmin(ret, rdist[pt[lb]][s] + query(0, in[pt[lb]].r) + 1);
		for (int i : range(lb, ub - 1)) {
			const int seg_cost = query(in[pt[i]].r + 1, in[pt[i + 1]].r);
			chmin(ret, rdist[pt[i]][3 - s] + seg_cost + 1);
			chmin(ret, rdist[pt[i + 1]][s] + seg_cost + 1);
		}
		chmin(ret, rdist[pt[ub - 1]][3 - s] + query(in[pt[ub - 1]].r + 1, Z::id) + 1);
		for (int i : range(lb, ub)) {
			rmq.update_element(in[pt[i]].r, force_update, dist[pt[i]][dir]);
			rmq.update_element(in[pt[i]].r + dr[s], weak_update, dist[pt[i]][s]);
			rmq.update_element(in[pt[i]].r + dr[3 - s], weak_update, dist[pt[i]][3 - s]);
		}
		lb = ub;
	}
	NodeBuffer::buffer.reset();
}

void solve_up() {
	constexpr int dir = Up::index;
	constexpr int s = Left::index;
	SegmentTree<node, int> rmq(Z::id, segment_min, merge_segment, set_segment, set_leaf);
	auto query = [&](int l, int r) {
		if (r - l >= 1)return rmq.get(l, r);
		else return INF;
	};
	for (int lb = N-1; lb >= 0;) {
		int ub = lb;
		int* pt = pts::pt[Tate::index];
		while (ub >=0 &&
			in[pt[lb]].r == in[pt[ub]].r) {
			ub--;
		}
		chmin(ret, rdist[pt[ub+1]][s] + query(0, in[pt[ub+1]].c) + 1);
		for (int i : range(ub+1, lb)) {
			const int seg_cost = query(in[pt[i]].c + 1, in[pt[i + 1]].c);
			chmin(ret, rdist[pt[i]][3 - s] + seg_cost + 1);
			chmin(ret, rdist[pt[i + 1]][s] + seg_cost + 1);
		}
		chmin(ret, rdist[pt[lb]][3 - s] + query(in[pt[lb]].c + 1, Z::id) + 1);
		for (int i : range(ub+1, lb+1)) {
			rmq.update_element(in[pt[i]].c, force_update, dist[pt[i]][dir]);
			rmq.update_element(in[pt[i]].c + dc[s], weak_update, dist[pt[i]][s]);
			rmq.update_element(in[pt[i]].c + dc[3 - s], weak_update, dist[pt[i]][3 - s]);
		}
		lb = ub;
	}
	NodeBuffer::buffer.reset();
}

void solve_left() {
	constexpr int dir = Left::index;
	constexpr int s = Up::index;
	SegmentTree<node, int> rmq(Z::id, segment_min, merge_segment, set_segment, set_leaf);
	auto query = [&](int l, int r) {
		if (r - l >= 1)return rmq.get(l, r);
		else return INF;
	};
	for (int lb = N-1; lb >= 0;) {
		int ub = lb;
		int* pt = pts::pt[Yoko::index];
		while (ub >=0&&
			in[pt[lb]].c == in[pt[ub]].c) {
			ub--;
		}
		chmin(ret, rdist[pt[ub+1]][s] + query(0, in[pt[ub+1]].r) + 1);
		for (int i : range(ub+1, lb)) {
			const int seg_cost = query(in[pt[i]].r + 1, in[pt[i + 1]].r);
			chmin(ret, rdist[pt[i]][3 - s] + seg_cost + 1);
			chmin(ret, rdist[pt[i + 1]][s] + seg_cost + 1);
		}
		chmin(ret, rdist[pt[lb]][3 - s] + query(in[pt[lb]].r + 1, Z::id) + 1);
		for (int i : range(ub+1, lb+1)) {
			rmq.update_element(in[pt[i]].r, force_update, dist[pt[i]][dir]);
			rmq.update_element(in[pt[i]].r + dr[s], weak_update, dist[pt[i]][s]);
			rmq.update_element(in[pt[i]].r + dr[3 - s], weak_update, dist[pt[i]][3 - s]);
		}
		lb = ub;
	}
	NodeBuffer::buffer.reset();
}
inline bool isReachableWithHop(int r,int c) {
	return (isReachable(r, c, r, T.c) &&
		isReachable(r, T.c, T.r, T.c)) ||
		(isReachable(r, c, T.r, c) &&
			isReachable(T.r, c, T.r, T.c));
}

int main() {
	while (input()) {
		pts::build();
		if (isReachableWithHop(S.r, S.c)) {
			cout << 0 << endl; continue;
		}
		for (int i : range(N)) {
			for (int j : range(4)) {
				g[i][j].clear();
				rg[i][j].clear();
				dist[i][j] = INF;
				rdist[i][j] = INF;
			}
		}
		buildGraph();
		bfs();
		
		for (int i : range(N)) {
			for (int j : range(4)) {
				const int r = in[i].r + dr[j];
				const int c = in[i].c + dc[j];
				if (isReachableWithHop(r, c)) {
					chmin(ret, dist[i][j]);
					isReachableWithHop(r, c);
				}
			}
		}

		for (int i : range(N)) {
			if (isReachable(S.r,S.c,S.r,in[i].c)) {
				const int r = S.r;
				const int c = in[i].c;
				if (Down::getIce(r, c) == i)
					chmin(ret, rdist[i][3 - Down::index] + 1);
				if (Left::getIce(r, c) == i)
					chmin(ret, rdist[i][3 - Left::index] + 1);

				if (Right::getIce(r, c) == i)
					chmin(ret, rdist[i][3 - Right::index] + 1);
				if (Up::getIce(r, c) == i)
					chmin(ret, rdist[i][3 - Up::index] + 1);
			}
			if (isReachable(S.r, S.c, in[i].r, S.c)) {
				const int r = in[i].r;
				const int c = S.c;
				if (Down::getIce(r, c) == i)
					chmin(ret, rdist[i][3 - Down::index] + 1);
				if (Left::getIce(r, c) == i)
					chmin(ret, rdist[i][3 - Left::index] + 1);
				if (Right::getIce(r, c) == i)
					chmin(ret, rdist[i][3 - Right::index] + 1);
				if (Up::getIce(r, c) == i)
					chmin(ret, rdist[i][3 - Up::index] + 1);
			}
		}
		solve_down();
		solve_up(); 
		solve_left();
		solve_right();
		if (ret == INF)cout << -1 << endl;
		else cout << ret << endl;
	}
	return 0;
}
