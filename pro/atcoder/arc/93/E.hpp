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
namespace _DSU {
	constexpr int BUF = 212345 * 2;
	int ptr = 0;
	int mem[BUF];
	int* get(int size) {
		ptr += size;
		return mem + ptr - size;
	}
	void reset() {
		ptr = 0;
	}
}
class UF {
private:
	int *par, *rank;
public:
	int find(int x) {
		if (par[x] == x) return x;
		else return par[x] = find(par[x]);
	}
	UF(int n) :par(_DSU::get(n + 10)), rank(_DSU::get(n + 10)) {
		for (int i = 0; i<n; i++) {
			par[i] = i, rank[i] = 0;
		}
	}
	bool unite(int x, int y) {
		x = find(x); y = find(y);
		if (x == y)return false;
		if (rank[x] < rank[y])swap(x, y);
		par[y] = x;
		if (rank[x] == rank[y])rank[x]++;
		return true;
	}
	bool same(int x, int y) {
		return find(x) == find(y);
	}
};
int N, M;
LL X;
int a[112345];
int b[112345];
LL c[112345];
LL d[112345];
pair<LL, int> edge[112345];
LL kruskal(UF& uf) {
	LL ret = 0;
	for (int i : range(M)) {
		const int u = a[edge[i].second];
		const int v = b[edge[i].second];
		const LL cost = c[edge[i].second];
		if (uf.unite(u, v)) {
			ret += cost;
		}
	}
	return ret;
}
constexpr int mod = 1e9 + 7;
LL f(int size) {
	LL ret = 1;
	for (int i : range(size)) {
		ret *= 2;
		ret %= mod;
	}
	return ret;
}
int main() {
	while (cin >> N >> M >> X) {
		for (int i : range(M)) {
			cin >> a[i] >> b[i] >> c[i];
			a[i]--; b[i]--;
			edge[i] = { c[i],i };
		}
		sort(edge, edge + M);
		for (int i : range(M)) {
			UF uf(N);
			uf.unite(a[i], b[i]);
			d[i] = c[i] + kruskal(uf);
			_DSU::reset();
		}
		sort(d, d + M);
		int c1 = distance(d, upper_bound(d, d + M, X - 1));
		int c2 = distance(d, upper_bound(d, d + M, X));
		c1 = min(M, M - c1 + 1);
		c2 = min(M, M - c2 + 1);
		const LL ret = (mod + f(c1) -f(c2)) % mod;
		cout << ret << endl;
	}
	return 0;
}
