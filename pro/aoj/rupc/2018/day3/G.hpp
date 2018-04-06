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

#define REP(i,n) for(int i=0;i<n;i++)
namespace roll {
	using H = unsigned long long;
	//0123456789
	constexpr H p[] = { 1000000009,
		1000000007,
		90001 };
	constexpr int MX = 1123456;
	H hs[3][MX];
	H rh[3][MX];
	template<int m = 1>
	void build(const string s) {
		const int n = s.size();
		REP(i, m) {
			hs[i][0] = 0;
			rh[i][0] = 1;
			REP(i, m)REP(j, n) {
				hs[i][j + 1] = hs[i][j] * p[i] + s[j];
				rh[i][j + 1] = rh[i][j] * p[i];
			}
		}
	}
	template<int m = 1>
	H get(const int l, const int r) {
		H ret = 0;
		REP(i, m) {
			ret ^= hs[i][r] - hs[i][l] * rh[i][r - l];
		}
		return ret;
	}
}

int id[112345];
int latte[112345];
priority_queue<int> que;
int main() {
	string s; int n;
	while (cin >> s >> n) {
		int len = s.size();
		string all = s;
		vector<string> p(n);
		cin >> p;
		for (int i : range(n)) {
			id[i] = all.size();
			all += p[i];
		}
		id[n] = all.size();
		roll::build(all);
		vector<set<int>> h(len+1);
		int k = 0;
		for (int i : range(n)) {
			if (p[i].size() <= len) {
				h[p[i].size()].insert(roll::get(id[i], id[i + 1]));
				latte[k++] = p[i].size();
			}
		}
		sort(latte, latte + k);
		k = unique(latte, latte + k) - latte;
		int ret = 0;
		for (int i : range(len)) {
			if (que.empty() == false && -que.top() == i) {
				ret++;
				while (que.empty()==false)que.pop();
			}
			for (int j : range(k)) {
				if (i + latte[j] <= len) {
					if (h[latte[j]].count(roll::get(i, i + latte[j])))
						que.push(-(i + latte[j]));
				}
			}
		}
		if (que.empty() == false)ret++;
		while (que.empty() == false)que.pop();
		cout << ret << endl;
	}
	
	return 0;
}
