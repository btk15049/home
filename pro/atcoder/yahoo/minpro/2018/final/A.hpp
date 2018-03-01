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
const int K = 1e5;
int main() {
	int N, M;
	cin >> N >> M;
	vector<int> a(N);
	cin >> a;
	vector<int> A(K + 1, 0);
	for (int it : a)A[it]++;
	vector<int> m(M + 1);
	for (int i : range(1, M + 1)) {
		for (int j = i; j < K + 1; j += i) {
			m[i] += A[j];
		}
	}
	vector<int> p(M + 1), q(M + 1);
	for (int i : range(1, M + 1)) {
		p[i] = i;
		int num = 1;
		for (int j = 2; j*j <= p[i]; j++) {
			if (p[i] % j == 0) {
				q[i]++;
				num *= j;
				while (p[i] % j == 0)p[i] /= j;
			}
		}
		if (p[i] != 1) {
			q[i]++;
		}
		p[i] *= num;
	}

	vector<int> ret(M + 1, 0);
	for (int i : range(1, M + 1)) {
		if (p[i] != i)ret[i] = ret[p[i]];
		else {
			for (int j = 1; j*j <= i; j++) if(i%j==0){
				int a = j;
				int b = i / j;
				{
					if ((q[a]) % 2 == 0)ret[i] += m[a];
					else ret[i] -= m[a];
				}
				if (a != b) {
					a = b;
					if ((q[a]) % 2 == 0)ret[i] += m[a];
					else ret[i] -= m[a];
				}
			}
		}
	}
	for (int i : range(1, M + 1)) {
		cout << ret[i] << endl;
	}
	return 0;
}
