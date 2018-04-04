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

string s, t;
bool ok;
void f(int depth, string &ret) {
	if (depth == 0)return;
	f(depth - 1, ret);
	for (auto &it : t) {
		ret += it;
		if (ret.size() > s.size()) {
			ok = false;
			return;
		}
		f(depth - 1,ret);
	}
}
string g(int depth) {
	ok = true;
	string ret = "";
	f(depth, ret);
	if(ok)return ret;
	else return "";
}
bool check(string x) {
	if (x.size() == 0)return false;
	int n = s.size();
	int m = x.size();
	int j = 0;
	for (int i : range(n)) {
		if (s[i] == x[j])j++;
		if (j == m)return true;
	}
	return false;
}
int main() {
	while (cin >> s >> t) {
		int ub = s.size() + 1;
		int lb = 0;
		while (ub - lb > 1) {
			const int mid = (lb + ub) / 2;
			string x = g(mid);
			(check(x) ? lb : ub) = mid;
		}
		cout << lb << endl;
	}
	return 0;
}
