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

typedef vector<int> V;
typedef vector<V> VV;
int main() {
	int T;
	cin >> T;
	while (T--) {
		int N;
		cin >> N;
		VV g(N);
		V P(N);
		V ret(N);
		cin >> P;
		for (int i : range(N - 1)) {
			int a, b;
			cin >> a >> b;
			a--;
			b--;
			g[a].push_back(b);
			g[b].push_back(a);
		}
		map<int, int> x;
		auto latte = [&](int v) {x.erase(P[v]); };
		auto malta = [&](int v) {x[P[v]] = v; };
		for (int i : range(N))malta(i);
		for (int i : range(N)) {
			latte(i);
			for (int j : g[i]) {
				latte(j);
			}
			ret[i] = x.rbegin()->second + 1;
			malta(i);
			for (int j : g[i]) {
				malta(j);
			}
		}
		for (int i : range(N)) {
			cout << " " + (!i) << ret[i];
		}
		cout << endl;
	}

	return 0;
}
