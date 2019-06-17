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

vector<string> b(100,string(100,'#'));
int main() {
	LL K;
	cin >> K;
	vector<int> p;
	if (K == 0) {
		cout << "1 3 .#." << endl;
	}
	else {
		cout << "100 100" << endl;
		while (K) {
			p.push_back(K % 3);
			K /= 3;
		}
		int M = p.size();
		//reverse(ALL(p));
		int R = 0;
		int C = 0;
		int dr = 2;
		int dc = 3;
		for (int i : range(M)) {
			for (int r : range(R, R + dr)) {
				for (int c : range(C, C + dc)) {
					b[r][c] = '.';
				}
			}
			if(p[i]!=0){
				if (dc == 3) {
					if (p[i] == 1) {
						for (int r : range(R, 100)) {
							b[r][C] = '.';
						}
					}
					else {
						for (int r : range(R, 95)) {
							b[r][C] = '.';
						}
						for (int r : range(95 - 2, 100)) {
							b[r][C + 1] = '.';
						}
					}
				}
				else {
					if (p[i] == 1) {
						for (int c : range(C, 100)) {
							b[R][c] = '.';
						}
					}
					else {
						for (int c : range(C, 95)) {
							b[R][c] = '.';
						}
						for (int c : range(95 - 2, 100)) {
							b[R+1][c] = '.';
						}
					}
				}
			}
			R += dr-1;
			C += dc-1;
			swap(dr, dc);
		}
		for (int i : range(100))b[i][99] = '.';
		for (int i : range(100))b[99][i] = '.';
		for (int i : range(100))cout << b[i] << endl;
	}
	return 0;
}
