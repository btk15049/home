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

typedef complex<double> P;
int N, M;
P p[14];

constexpr double EPS = 1e-8;
int dp[1 << 14];
constexpr int INF = 100;
bool check(double r) {

	vector<int> b;
	for (int i : range(N)) {
		int bit = 0;
		for (int j : range(N)) {
			double d = abs(p[i] - p[j]);
			if (d < EPS)bit|=(1<<j);
		}
		b.push_back(bit);
	}
	for (int i : range(N)) {
		for (int j : range(N)){
			P v = p[i] - p[j];
			double d = abs(v);
			if (d < EPS || d>2*r + EPS)continue;
			P u(v.imag(),-v.real());
			u /= d;
			d /= 2;
			double dd = sqrt(r*r - d * d);
			u *= dd;
			P c = (p[i] + p[j]) / 2.0 + u;
			int bit = 0;
			for (int k : range(N)) {
				if (r - abs(p[k] - c) >= -EPS)bit |= (1 << k);
			}
			b.push_back(bit);
		}
	}
	for (int i : range(1 << N))dp[i] = INF;
	dp[0] = 0;
	for (int i : range(1 << N)) {
		for (auto &it : b) {
			chmin(dp[i | it], dp[i] + 1);
		}
	}
	return dp[(1 << N) - 1] <= M;
}
int main() {
	cout << fixed;
	cout << setprecision(10);
	cin >> N >> M;
	for (int i : range(N)) {
		double x, y;
		cin >> x >> y;
		p[i] = P(x, y);
	}
	double lb = EPS;
	double ub = 1e6;
	for (int i : range(100)) {
		const double mid = (lb + ub) / 2;
		(check(mid) ? ub : lb) = mid;
	}
	cout << ub << endl;
	return 0;
}
