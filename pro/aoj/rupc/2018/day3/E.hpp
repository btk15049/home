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
int n, q;

string ret[2] = { "broccoli","cauliflower" };
typedef vector<int> V;
typedef vector<V> VV;
typedef pair<int, int> P;
void euler_tour(int v, VV &g, vector<P> &seg, int& cnt) {
	int l = cnt++;
	for (auto &u : g[v])
		euler_tour(u, g, seg, cnt);
	int r = cnt;
	seg[v] = { l,r };
}
constexpr int b = 300;

int latte[112345];
namespace ike {
	int flag[1000];
	int num[1000][2];
	void init() {
		for (int i : range(1000)) {
			flag[i] = 0;
			num[i][0] = num[i][1] = 0;
		}
	}
	void update(int l, int r) {
		while (l < r) {
			if (l%b == 0 && l + b <= r) {
				flag[l / b] = 1 - flag[l / b];
				l += b;
			}
			else {
				num[l / b][latte[l]]--;
				latte[l] = 1 - latte[l];
				num[l / b][latte[l]]++;
				l++;
			}
		}
	}
	int get() {
		int i = 0;
		int ret = 0;
		while (i < n) {
			int id = i / b;
			ret += num[id][flag[id]];
			i += b;
		}
		return ret;
	}
}

int main() {
	while (cin >> n >> q) {
		VV g(n);
		V l(n);
		for (int i : range(n - 1)) {
			int par; cin >> par;
			g[par - 1].push_back(i + 1);
		}
		for (int i : range(n)) {
			char x; cin >> x;
			l[i] = (x == 'G');
		}
		vector<P> seg(n);
		{
			int id = 0;
			euler_tour(0, g, seg, id);
		}
		ike::init();
		for (int i : range(n)) {
			int pos = seg[i].first;
			latte[pos] = l[i];
			ike::num[pos / b][l[i]]++;
		}
		for (int _ : range(q)) {
			int v;
			cin >> v;
			v--;
			ike::update(seg[v].first, seg[v].second);
			int malta = ike::get();
			cout << ret[malta > n - malta] << endl;
		}
	}

	return 0;
}
