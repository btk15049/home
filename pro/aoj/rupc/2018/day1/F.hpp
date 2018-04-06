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
constexpr int MAX_LEN = 25;

LL dp_N[MAX_LEN][1000][2]; bool vis_N[MAX_LEN];
LL dp_all[MAX_LEN][1000][2]; bool vis_all[MAX_LEN];
void f(int d);
void g(int d);

vector<int> in;
int len;
bool usa[10000];
void f(int d) {
	if (vis_N[d])return;
	vis_N[d] = true;
	for (int i : range(1000)) {
		dp_N[d][i][0] = dp_N[d][i][1] = 0;
	}
	if (d == 0) {
		dp_N[d][0][0] = 1; return;
	}
	f(d - 1); g(d - 1);
	{
		int p = in[d - 1];
		for (int i : range(1000)) {
			int nxt = p * 1000 + i;
			dp_N[d][nxt / 10][1] += dp_N[d - 1][i][1];
			if (usa[nxt]) {
				dp_N[d][nxt / 10][1] += dp_N[d - 1][i][0];
			}
			else {
				dp_N[d][nxt / 10][0] += dp_N[d - 1][i][0];
			}
		}
	}
	for(int p:range(in[d-1])){
		for (int i : range(1000)) {
			int nxt = p * 1000 + i;
			dp_N[d][nxt / 10][1] += dp_all[d - 1][i][1];
			if (usa[nxt]) {
				dp_N[d][nxt / 10][1] += dp_all[d - 1][i][0];
			}
			else {
				dp_N[d][nxt / 10][0] += dp_all[d - 1][i][0];
			}
		}
	}
}
void g(int d) {
	if (vis_all[d])return;
	vis_all[d] = true;
	for (int i : range(1000)) {
		dp_all[d][i][0] = dp_all[d][i][1] = 0;
	}
	if (d == 0) {
		dp_all[d][0][0] = 1; return;
	}
	f(d - 1); g(d - 1);
	for (int p : range(10)) {
		for (int i : range(1000)) {
			int nxt = p * 1000 + i;
			dp_all[d][nxt / 10][1] += dp_all[d - 1][i][1];
			if (usa[nxt]) {
				dp_all[d][nxt / 10][1] += dp_all[d - 1][i][0];
			}
			else {
				dp_all[d][nxt / 10][0] += dp_all[d - 1][i][0];
			}
		}
	}
}

int main() {
	for (int i : range(10000))usa[i] = false;
	for (int i : range(10))usa[5103 + i * 10] = true;
	string s;
	cin >> s;
	reverse(ALL(s));
	for (auto &it : s)in.push_back(it - '0');
	for(int i:range(3))in.push_back(0);
	len = in.size();
	f(len);
	LL ret = 0;
	ret+=dp_N[len][0][1];
	cout << ret << endl;
	return 0;
}
