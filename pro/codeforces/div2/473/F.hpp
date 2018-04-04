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

int a[1123456];
int b[30];
int l[1123456];
int x[1123456];
LL out[1123456];
vector<int> query[1123456];
constexpr int mod = 1e9 + 7;
int main() {
	int n, q;
	cin >> n >> q;
	for (int i : range(n))cin >> a[i];
	for (int i : range(q)) {
		cin >> l[i] >> x[i];
		query[l[i]-1].push_back(i);
	}
	int m = 0;
	LL ret = 1;
	for (int i : range(n)) {
		for (int j : range(m)) {
			if (a[i] > (a[i] ^ b[j]))a[i] ^= b[j];
		}
		if (a[i]) {
			b[m++] = a[i];
			sort(b, b + m, [](int l, int r) {return l > r; });
		}
		else ret = ret * 2 % mod;
		for (auto id : query[i]) {
			for (int j : range(m)) {
				if (x[id] > (x[id]^b[j]))
					x[id] ^= b[j];
			}
			if (x[id])out[id] = 0;
			else out[id] = ret;
		}
	}

	for (int i : range(q))cout << out[i] << endl;
	return 0;
}
