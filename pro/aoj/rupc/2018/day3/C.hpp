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

const int SZ = 'Z' + 1;
int d[SZ][SZ];
const int dr[4] = { 1,0,-1,0 };
const int dc[4] = { 0,1,0,-1 };
string ike = "|-|-";
vector<string> wrap(vector<string> x, char c) {
	int R = x.size();
	int C = x[0].size();
	vector<string> ret(R + 2, string(C + 2, c));
	for (int i : range(R)) {
		for (int j : range(C)) {
			ret[i + 1][j + 1] = x[i][j];
		}
	}
	return ret;
}
int main() {
	int R, C;
	while (cin >> R >> C) {
		char S, T;
		cin >> S >> T;
		vector<string> s(R);
		for (int i : range(R))cin >> s[i];
		for (int i : range(SZ))for (int j : range(SZ))d[i][j] = 1000;
		for (int i : range(SZ))for (int j : range(i,i+1))d[i][j] = 0;
		s = wrap(s, '.');
		R += 2;
		C += 2;
		for (int i : range(R)) {
			for (int j : range(C)) {
				if (isupper(s[i][j])) {
					for (int k : range(4)) {
						int r = i + dr[k];
						int c = j + dc[k];
						while (s[r][c] == 'o'||s[r][c] == ike[k]) {
							r += dr[k];
							c += dc[k];
						}
						if (isupper(s[r][c])) {
							d[s[i][j]][s[r][c]] = 1;
						}
					}
				}
			}
		}
		for (int k : range(SZ))for (int i : range(SZ))for (int j : range(SZ))
			chmin(d[i][j], d[i][k] + d[k][j]);
		cout << d[S][T] << endl;
	}

	return 0;
}
