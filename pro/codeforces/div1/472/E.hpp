#ifndef VS
#include<bits/stdc++.h>
#endif

using namespace std;
typedef long long LL;

#ifdef BTK
#define DEBUG if(1)
#else
#define DEBUG if(0)
#endif

#define ALL(v) (v).begin(),(v).end()
#define REC(ret, ...) std::function<ret (__VA_ARGS__)>
template <typename T>inline bool chmin(T &l, T r){bool a = l>r; if (a)l = r; return a;}
template <typename T>inline bool chmax(T &l, T r){bool a = l<r; if (a)l = r; return a;}
template <typename T>istream& operator>>(istream &is, vector<T> &v){for (auto &it : v)is >> it;return is;}

class range {private: struct I { int x; int operator*() { return x; }bool operator!=(I& lhs) { return x<lhs.x; }void operator++() { ++x; } }; I i, n;public:range(int n) :i({ 0 }), n({ n }) {}range(int i, int n) :i({ i }), n({ n }) {}I& begin() { return i; }I& end() { return n; }};
constexpr int MAX_N = 11234;
int N,l, r;
int a[MAX_N];
int b[MAX_N];
bool once = true;
inline bool input() {
#ifdef VS
	bool ret = !!(cin >> N >> l >> r);
	for (int i : range(N)) {
		cin >> a[i];
	}
	for (int i : range(N)) {
		cin >> b[i];
	}
	return ret;
#else
	if (once) {
		scanf("%d %d %d", &N, &l, &r);
		for (int i : range(N)) {
			scanf("%d", a + i);
		}
		for (int i : range(N)) {
			scanf("%d", b + i);
		}
		once = false;
		return true;
	}
	return false;
#endif
}
int ord[MAX_N];
constexpr int INF = 1e7;
typedef bitset<2 * MAX_N> B;
int dp[2 * MAX_N];
int main() {
	while (input()) {
		iota(ord, ord + N, 0);
		sort(ord, ord + N, [&](int ll, int rr) {return a[ll] > a[rr]; });
		int ret = 0;
		B can(0);
		for (int i : range(MAX_N)) {
			dp[i] = -INF;
		}
		can[0] = true;
		for (int i : range(N)) {
			const int id = ord[i];
			if (b[id] == 0) {
				can|= can << a[id];
			}
		}
		for (int i : range(r + 1)) {
			if (can[i])dp[i] = 0;
		}
		for (int i : range(N)) {
			const int id = ord[i];
			if (b[id] == 1) {
				for (int _ : range(r + 1)) {
					const int j = r - _;
					if (dp[j]>=0) {
						if (j >= l)chmax(ret, dp[j] + 1);
						chmax(dp[j + a[id]], dp[j] + 1);
					}
				}
			}
		}
#ifdef VS
		cout << ret << endl;
#else
		printf("%d\n", ret);
#endif // VS
	}
	return 0;
}
