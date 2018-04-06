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


// ŠKæ
// O(n)
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


// ‘g‚Ý‡‚í‚¹nCk (mod mod)
// O(1)
LL Comb(LL n, LL k) {
	LL u = fact[n];
	LL d = (rfact[k] * rfact[n - k]) % mod;
	return u * d%mod;
}

//O(1)
LL Perm(LL n, LL k) {
	LL u = fact[n];
	LL d = rfact[n - k] % mod;
	return u * d%mod;
}


LL Pow(LL a, LL n, int M = mod) {
	LL res = 1;
	a %= M;
	while (n) {
		if (n & 1)
			res = (res*a) % M;
		a = (a*a) % M;
		n >>= 1;
	}
	return res;
}

LL f(int n, int k) {
	LL ret = 0;
	for (int i : range(k)) {
		ret += (Pow(mod - 1, i)*Comb(k, i) % mod) * Pow(k - i, n) % mod;
	}
	ret %= mod;
	ret *= rfact[k];
	return ret%mod;
}

int main() {
	int n, k;
	cin >> n >> k;
	LL sum = 0;
	for (int i : range(n)) {
		int a; cin >> a;
		sum += a;
	}
	sum %= mod;
	cout << sum * ((f(n, k)+(n-1)*f(n-1,k))%mod) % mod << endl;
	return 0;
}
