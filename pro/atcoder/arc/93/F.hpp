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

constexpr int mod = 1e9 + 7;

inline LL invMod(LL a, LL m = mod) {
	LL b = m, u = 1, v = 0;
	while (b) {
		LL t = a / b;
		swap(a -= t * b, b);
		swap(u -= t * v, v);
	}
	return (u % m + m) % m;
}

constexpr int SZ = 1123456;
LL fact[SZ];
LL rfact[SZ];
struct fact_ {
	fact_() {
		fact[0] = 1;
		for (int i = 1; i<SZ; i++)
			fact[i] = fact[i - 1] * i%mod;
		rfact[SZ - 1] = invMod(fact[SZ - 1]);
		for (int i = SZ - 1; i>0; i--) {
			rfact[i - 1] = rfact[i] * i%mod;
		}
	}
}fact_init;

//O(1)
LL Perm(LL n, LL k) {
	LL u = fact[n];
	LL d = rfact[n - k] % mod;
	return u * d%mod;
}

//O(1)
LL Comb(LL n, LL k) {
	LL u = fact[n];
	LL d = (rfact[k] * rfact[n - k]) % mod;
	return u * d%mod;
}


int main() {
	int N, M;
	while (cin >> N >> M) {
		vector<int> A(M);
		cin >> A;
		reverse(ALL(A));
		vector<LL> dp(1 << N, 0);
		dp[0] = 1;
		for (int a : A) {
			auto nxt = dp;
			for (int i : range(1 << N)) {
				nxt[i] %= mod;
				bitset<32> b(i);
				for (int j : range(N)) {
					if (b[j])continue;
					if ((1 << N) - a + 1 < i + (1 << j))continue;
					LL cnt = Comb((1 << N) - a - i, (1 << j) - 1) * fact[1 << j] % mod;
					nxt[i | (1 << j)] += dp[i] * cnt% mod;
				}
			}
			
			swap(dp, nxt);
		}
		LL ret = 0;
		for (int i : range(1 << N)) {
			bitset<32> b(i);
			int rest = 0;
			for (int j : range(N)) {
				if (b[j])continue;
				rest += 1 << j;
			}
			LL cnt = fact[rest] * dp[i] % mod;
			if (__builtin_popcount(i) % 2) {
				ret += mod - cnt;
			}
			else {
				ret += cnt;
			}
		}
		ret %= mod;
		for (int i : range(N)) {
			ret *= 2;
			ret %= mod;
		}
		cout << ret << endl;
	}
	return 0;
}
