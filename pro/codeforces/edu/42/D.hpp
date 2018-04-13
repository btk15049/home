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



LL a[212345];
LL b[212345];
int main() {
	int n;
	cin >> n;
	for (int i : range(n))cin >> a[i];
	for (int i : range(n))b[i]=a[i];
	sort(b, b + n);
	int m = unique(b, b + n) - b;
	map<LL, vector<int>> x;
	for (int i : range(n)) {
		x[a[i]].push_back(i);
	}
	priority_queue<LL> que;
	for (int i : range(m))que.push(-b[i]);
	while(que.size()){
		LL val = -que.top(); que.pop();
		auto v = x[val];
		sort(ALL(v)); reverse(ALL(v));
		if (v.size() >= 2)que.push(-val * 2);
		while (v.size() >= 2) {
			v.pop_back();
			x[val * 2].push_back(v.back());
			a[v.back()] = val * 2;
			v.pop_back();
		}
		x[val] = v;
	}
	m = 0;
	for (auto &it : x) {
		if (it.second.size() > 0)b[m++] = it.second[0];
	}
	sort(b, b + m);
	cout << m << endl;
	for (int i : range(m-1)) {
		cout << a[b[i]] << " ";
	}
	cout << a[b[m - 1]] << endl;
	return 0;
}
