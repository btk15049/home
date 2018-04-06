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

int p[6][4] = { {0,0,1,1},{ 0,1,0,1 },{ 0,1,1,0 },{ 1,1,0,0 },{ 1,0,1,0 },{ 1,0,0,1 } };
int t[4][112][112];
int main() {
	int n;
	cin >> n;
	for (int i : range(4)) {
		for (int j : range(n)) {
			string s;
			cin >> s;
			for (int k : range(n))t[i][j][k] = s[k] - '0';
		}
	}
	int ret = 1e6;
	for (int a : range(6)) {
		int sub = 0;
		for (int i : range(4)) {
			for (int j : range(n)) {
				for (int k : range(n)) {
					int expected = (p[a][i] + j + k) % 2;
					sub += abs(expected - t[i][j][k]);
				}
			}
		}
		chmin(ret, sub);
	}
	cout << ret << endl;
	return 0;
}
