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
typedef pair<int, int> P;
constexpr int L = 1123;
constexpr int N = 112;
int dist[N][L];
queue<P> que[L];
int r[N];
int c[N];
int R, C, n;
int d(int i, int j) {
	return abs(r[i] - r[j]) + abs(c[i] - c[j]);
}
int main() {
	cin >> R >> C >> n;
	if (R == 1 && C == 1) {
		cout << 0 << endl; return 0;
	}
	for (int i : range(N))for (int j : range(L))dist[i][j] = L;
	for (int i : range(n)) {
		cin >> r[i] >> c[i];
		int cost = r[i] + c[i] - 2;
		que[cost].push({ i,cost });
		chmin(dist[i][cost], cost);
	}
	for (int cost : range(L)) {
		while (que[cost].size()) {
			int v, l; tie(v, l) = que[cost].front(); que[cost].pop();

			if (cost > dist[v][l])continue;
			for (int u : range(n)) {
				int need = d(u, v) - l - 1;
				if(need <=0)need = 0;
				if (chmin(dist[u][need], cost + need)) {
					que[cost+need].push({ u,need });
				}
			}
			if (cost + 1 < L&&l + 1 < L) {
				if (chmin(dist[v][l + 1], cost + 1)) {
					que[cost + 1].push({ v,l + 1 });
				}
			}
		}
	}
	int ret = L;
	for (int i : range(n)) {
		for (int l : range(L)) {
			int cost = R - r[i] + C - c[i] - l;
			if (cost < 0)cost = 0;
			chmin(ret, dist[i][l] + cost);
		}
	}
	cout << ret << endl;
	return 0;
}
