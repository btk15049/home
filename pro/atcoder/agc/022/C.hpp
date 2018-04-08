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
int N;
int a[100];
int b[100];
typedef bitset<64> B;
bool check(B mask) {
	bool ret = true;
	for (int i : range(N)) {
		B bit(0);
		bit[a[i]] = true;
		queue<int> que;
		que.push(a[i]);
		while (que.size()) {
			int v = que.front(); que.pop();
			for (int j : range(1, 51))if(mask[j]) {
				int u = v % j;
				if (bit[u] == false) {
					bit[u] = true;
					que.push(u);
				}
			}
		}
		ret &= bit[b[i]];
	}
	return ret;
}

int main() {
	cin >> N;
	for (int i : range(N))cin >> a[i];
	for (int i : range(N))cin >> b[i];
	B mask((1ll << 51) - 2);
	for (int i = 50; i > 0; i--) {
		mask[i] = false;
		if (check(mask) == false)mask[i] = true;
	}
	if (check(mask))cout << mask.to_ullong() << endl;
	else cout << -1 << endl;
	return 0;
}
