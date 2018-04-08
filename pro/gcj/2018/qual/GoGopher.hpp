#include<bits/stdc++.h>

using namespace std;
typedef long long LL;

#ifdef BTK
#define DEBUG if(1)
#else
#define DEBUG if(0)
#endif

#define ALL(v) (v).begin(),(v).end()
#define REC(ret, ...) std::function<ret (__VA_ARGS__)>
template <typename T>inline bool chmin(T &l, T r){bool a = l>r; if (a)l = r; return a;}
template <typename T>inline bool chmax(T &l, T r){bool a = l<r; if (a)l = r; return a;}
template <typename T>istream& operator>>(istream &is, vector<T> &v){for (auto &it : v)is >> it;return is;}

class range {private: struct I { int x; int operator*() { return x; }bool operator!=(I& lhs) { return x<lhs.x; }void operator++() { ++x; } }; I i, n;public:range(int n) :i({ 0 }), n({ n }) {}range(int i, int n) :i({ i }), n({ n }) {}I& begin() { return i; }I& end() { return n; }};

int cell[100];
bool check(int c) {
	return cell[c - 1] == 7 && cell[c] == 7 && cell[c + 1] == 7;
}
void solve() {
	int a;
	cin >> a;
	//ofstream err("err.txt");
	//err << a << endl;
	for (int i : range(1, 100)) {
		cell[i] = 0;
	}
	int ub;
	if (a == 20) {
		ub = 6;
	}
	else {
		ub = 66;
	}
	int lb = 2;
	while (true) {
		cout << "2 " << lb << endl; cout.flush();
		int a, b;
		int x, y;
		cin >> x >> y;
		//err << "2 " << lb << " " << x << " " << y << endl;
		if (x == 0 && y == 0)return;
		cell[y] |= 1 << (x - 1);
		while (lb < ub&&cell[lb - 1] == 7)lb++;
	}
	//err.close();
}
int main() {
	int T;
	cin >> T;
	for (int i : range(1, T + 1)) {
		solve();
	}


	return 0;
}
