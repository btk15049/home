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

int main() {
	int N;
	while (cin >> N) {
		vector<int> x(N),h(N, 0);
		for (int i : range(N)) {
			cin >> x[i];
			chmax(h[i], x[i] + 1);
		}
		for (int _ : range(1 , N)) {
			int i = N - 1 - _;
			chmax(h[i], h[i + 1] - 1);
		}
		for (int i : range(1,N)) {
			chmax(h[i], h[i - 1]);
		}

		LL ret = 0;
		for (int i : range(N)) {
			ret += h[i] - 1 - x[i];
		}
		cout << ret << endl;
	}

	return 0;
}
