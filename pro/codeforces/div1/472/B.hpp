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
	cout << fixed;
	cout << setprecision(10);
	int N; LL U;
	while (cin >> N >> U) {
		vector<LL> v(N);
		cin >> v;
		double ret = -1;
		int ub = 0;
		for (int i : range(N-2)) {
			while (ub + 1 < N&&v[ub + 1] - v[i] <= U)ub++;
			if (ub - i >= 2) {
				double e = v[ub] - v[i + 1]; e /= (v[ub] - v[i]);
				chmax(ret, e);
			}
		}

		if (ret < 0)cout << -1 << endl;
		else cout << ret << endl;
	}

	return 0;
}
