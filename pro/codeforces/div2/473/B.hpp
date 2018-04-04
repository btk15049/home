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
	int n, k, m;
	cin >> n >> k >> m;
	vector<string> s(n);
	cin >> s;
	vector<LL> cost(n);
	cin >> cost;
	vector<LL> mincost(k, 1e15);
	map<string, int> group;
	for (int i : range(k)) {
		int sz; cin >> sz;
		for (int j : range(sz)) {
			int id;
			cin >> id;
			chmin(mincost[i], cost[id - 1]);
			group[s[id - 1]] = i;
		}
	}
	vector<string> t(m);
	cin >> t;
	LL ret = 0;
	for (int i : range(m))ret += mincost[group[t[i]]];
	cout << ret << endl;
	return 0;
}
