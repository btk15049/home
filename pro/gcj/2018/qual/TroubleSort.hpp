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

void solve() {
	int N;
	cin >> N;
	vector<int> v(N),u(N);
	cin >> v;
	vector<vector<int>> oe(2);
	for (int i : range(N)) {
		oe[i % 2].push_back(v[i]);
	}
	sort(ALL(v));
	for (int i : range(2))sort(ALL(oe[i]));
	for (int i : range(oe[0].size()))u[i * 2] = oe[0][i];
	for (int i : range(oe[1].size()))u[i * 2 + 1] = oe[1][i];
	if (v == u)cout << "OK" << endl;
	else {
		for (int i : range(N)) {
			if (v[i] != u[i]) {
				cout << i << endl; break;
			}
		}
	}
}
int main() {
	int T;
	cin >> T;
	cout << fixed;
	cout << setprecision(10);
	for (int i : range(1, T + 1)) {
		cout << "Case #" << i << ": ";
		solve();
	}

	return 0;
}
