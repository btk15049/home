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
typedef unsigned long long INT;
INT a, b;

INT A(LL i) {
	if (i < a)return i;
	else return i + 1;
}
INT B(LL i) {
	if (i < b)return i;
	else return i + 1;
}

bool check(INT x) {
	if (x < 110) {
		for (int i : range(1,x+1)) {
			int j = x - i + 1;
			if (A(i)*B(j) >= a*b)return false;
		}
	}
	else {
		for (int d : range(-50, 51)) {
			LL i = x / 2 + d;
			LL j = x - i + 1;
			if (A(i)*B(j) >= a*b)return false;
		}
	}
	return true;
}
int main() {
	int Q;
	cin >> Q;
	while (Q--) {
		cin >> a >> b;
		check(1);
		INT lb = 0;
		INT ub = (4 * 1e9)+10;
		while (ub - lb > 1) {
			const INT mid = (lb + ub) / 2;
			(check(mid)? lb : ub) = mid;
		}
		cout << lb << endl;
	}

	return 0;
}
