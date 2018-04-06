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


constexpr double INF = 1e18;
int main() {
	int N,M;
	cin >> N >> M;
	vector<double> a(N);
	cin >> a;
	vector<vector<double>> dp(N + 1, vector<double>(M + 1, -INF));
	dp[0][0] = 0;
	for (int i : range(N + 1)) {
		for(int c:range(M)){
			double hsum = 0;
			double len = 0;
			for (int j : range(i + 1, N + 1)) {
				hsum += a[j - 1];
				len += 1.0;
				chmax(dp[j][c + 1], dp[i][c] + hsum / len);
			}
		}
	}
	cout << fixed;
	cout << setprecision(10);
	double ret = -INF;
	for (int i : range(M + 1))chmax(ret, dp.back()[i]);
	cout << ret << endl;
	return 0;
}
