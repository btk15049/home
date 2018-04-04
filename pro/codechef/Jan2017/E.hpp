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

int N;
string S;
int M, X, Y;
typedef bitset<64 * 5> B;
bool check(LL d) {
	vector<B> dp(N + 1);
	dp[0][0] = true;
	for (int i : range(N)) {
		LL p = 0;
		for (int j : range(M)) {
			if (i + j >= N)break;
			p *= 10;
			p += S[i + j] - '0';
			if (p%d == 0) {
				dp[i + j + 1] |= dp[i] << 1;
			}
		}
	}
	for (int i : range(X,Y+1)) {
		if(dp.back()[i])return true;
	}
	return false;
}
inline void solve() {
	X++;
	Y++;
	vector<LL> divisor;
	int lz = 0;
	for (int i : range(N)) {
		if (S[i] == '0')lz++;
		else break;
	}
	LL x = 0;
	for (int i : range(M)) {
		if (i + lz >= N)break;
		x *= 10;
		x += S[i+lz] - '0';
		for(LL d=1;d*d<=x;d++){
			if (x%d == 0) {
				divisor.push_back(d);
				divisor.push_back(x / d);
			}
		}
	}
	sort(ALL(divisor));
	divisor.erase(unique(ALL(divisor)), divisor.end());
	LL ret = 0;
	reverse(ALL(divisor));
	for(LL d:divisor){
		if (check(d)) {
			ret = d;
			break;
		}
	}
	cout << ret << endl;
}
int main() {
	int T;
	cin >> T;
	while (T--) {
		cin >> N >> S >> M >> X >> Y;
		solve();
	}
	return 0;
}
