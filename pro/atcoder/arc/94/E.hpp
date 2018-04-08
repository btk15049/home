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

int main() {
	int N;
	cin >> N;
	vector<LL> a(N), b(N);
	int id = -1;
	LL ret = 0;
	for (int i : range(N)) {
		cin >> a[i] >> b[i];
		if (a[i] > b[i])id = i;
	}
	if (id == -1) {
		cout << 0 << endl;
	}
	else {
		LL sum = 0;
		for (int i : range(N)) {
			sum += a[i];
		}
		for (int i : range(N)) {
			if(a[i]>b[i])chmax(ret,sum-a[i]+a[i]-b[i]);
		}
		cout << ret << endl;
	}

	return 0;
}
