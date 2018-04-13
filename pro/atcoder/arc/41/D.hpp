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

int N, M;
using V = vector<int>;
using VV = vector<V>;
VV g;
int a[2123];
int b[2123];
int c[2123];

int color[2123];
bool used[2123];
bool solve(int e, int ce) {
	for (int i : range(N))color[i] = -1;
	for (int i : range(M))used[i] = false;
	color[e] = ce;
	stack<int> st;
	st.push(e);
	while (!st.empty()) {
		int v = st.top(); st.pop();
		for (int e : g[v]) {
			int u = a[e] ^ b[e] ^ v;
			if (c[e] != color[v])continue;
			used[e] = true;
			if (color[u] == -1) {
				st.push(u);
				color[u] = 1 - color[v];
			}
			else if (color[u] != 1 - color[v]) {
				return true;
			}
		}
	}
	for (int i : range(M))if (used[i] == false)return false;
	return true;
}

int main() {
	cin >> N >> M;
	g = VV(N);
	for (int i : range(M)) {
		char x;
		cin >> a[i] >> b[i] >> x;
		a[i]--;
		b[i]--;
		c[i] = (x == 'r');
		g[a[i]].push_back(i);
		g[b[i]].push_back(i);
	}
	for (int v : range(N))for (int col : range(2)) {
		if (solve(v, col)) {
			cout << "Yes" << endl; 
			return 0;
		}
	}
	cout << "No" << endl; return 0;
	return 0;
}
