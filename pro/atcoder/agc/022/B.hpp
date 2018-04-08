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

constexpr int X = 30001;
int main() {
	VV num(3);
	for (int i : range(1,X)) {
		if (i % 6 == 0);
		else if (i % 3 == 0)num[1].push_back(i);
		if (i % 2 == 0)num[0].push_back(i);
	}
	vector<pair<int, int>> ok(X, {0,0});
	for (int i = 2; i <= num[1].size();i+=2) {
		int j = 2,k=1;
		while (j <= num[0].size()) {
			ok[i + j] = { j,i };
			j += k;
			k = 3 - k;
		}
	}
	int N;
	cin >> N;
	if (N == 3) {
		cout << "2 5 63" << endl;
	}
	else if (N == 4) {
		cout << "2 5 20 63" << endl;
	}
	else {
		for (int i : range(ok[N].first)) {
			cout << num[0][i] << " ";
		}
		for (int i : range(ok[N].second)) {
			cout << num[1][i] << " ";
		}
		cout << endl;

	}
	return 0;
}
