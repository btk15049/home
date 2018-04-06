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

int N;
LL x[112345];
LL y[112345];
LL gcd(LL a, LL b) {
	return (b == 0) ? a : gcd(b, a%b);
}
pair<LL,LL> reduce(LL a, LL b) {
	if (a < 0) {
		a *= -1;b *= -1;
	}
	if (a == 0 && b < 0) {
		b *= -1;
	}
	LL g = gcd(abs(a), abs(b));
	return { a / g,b / g };
}
bool used[112345];
void markline(int i,int j) {
	//assert(x[j] - x[i] != 0 || y[j] - y[i] != 0);

	auto l = reduce(x[i] - x[j], y[i] - y[j]);
	used[i] = true;
	for (int k : range(N))if (i != k) {
		//assert(x[k]-x[i]!=0|| y[k] - y[i] != 0);
		if (reduce(x[k] - x[i], y[k] - y[i]) == l)used[k] = true;
	}
}
bool solve(int a, int b, int c) {
	for (int i : range(N))used[i] = false;
	markline(0, a); markline(b, c);
	for (int i : range(N)) {
		if (used[i] == false)return false;
	}
	return true;
}
int main() {
	cin >> N;
	for (int i : range(N)) {
		cin >> x[i] >> y[i];
	}
	map<pair<LL,LL>, vector<int>> cnt;
	for (int i : range(1, N)) {
		cnt[reduce(x[i] - x[0], y[i] - y[0])].push_back(i);
	}
	string ret = "NO";
	if (cnt.size() <= 2) {
		ret = "YES";
	}
	else {
		vector<int> v, u;
		for (auto &it : cnt) {
			v.push_back(it.second.front());
		}
		if (solve(v[0], v[1], v[2]))ret = "YES";
		if (solve(v[1], v[0], v[2]))ret = "YES";
		if (solve(v[2], v[0], v[1]))ret = "YES";
		if (ret != "YES") {
			for (int i : range(N))used[i] = false;
			markline(v[0], v[1]);
			for (int i : range(1,N))if (used[i] == false)u.push_back(i);
			if (solve(u.front(), v[0], v[1]))ret = "YES";
		}
	}
	cout << ret << endl;
	return 0;
}
