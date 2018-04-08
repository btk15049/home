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
	int W, B;
	cin >> W >> B;
	W--; B--;
	vector<string> x(45, string(99, '.'));
	vector<string> y(45, string(99, '#'));
	for (int i = 1; i < 45; i += 2) {
		for (int j = 1; j < 99; j += 2) {
			if (B > 0) {
				x[i][j] = '#'; B--;
			}
		}
	}
	for (int i = 1; i < 45; i += 2) {
		for (int j = 1; j < 99; j += 2) {
			if (W > 0) {
				y[i][j] = '.'; W--;
			}
		}
	}
	cout << 90 << " " << 99 << endl;
	for (auto it : x)cout << it << endl;
	for (auto it : y)cout << it << endl;

}
