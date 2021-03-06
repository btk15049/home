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

int main() {
	int N;
	cin >> N;
	vector<int> A(N);
	cin >> A;
	auto B = A;
	reverse(ALL(B));
	map<int, int> cnt;
	int diff = 0;
	vector<int> ret;
	for (int i : range(N)) {
		if (cnt[A[i]] == 0)diff++;
		cnt[A[i]]++;
		if (cnt[A[i]] == 0)diff--;
		if (cnt[B[i]] == 0)diff++;
		cnt[B[i]]--;
		if (cnt[B[i]] == 0)diff--;
		if (diff == 0)ret.push_back(i + 1);
	}
	int K = ret.size();
	for (int i : range(K)) {
		cout << " " + (!i) << ret[i];
	}
	cout << endl;
	return 0;
}
