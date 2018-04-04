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
typedef vector<int > V;
typedef vector<V> VV;

template <typename ITR>
bool next_value(int base, ITR bg, ITR ed) {
	int c = 1;
	for (; bg != ed && c == 1; ++bg) {
		(*bg) += c;
		if ((c = ((*bg) == base)))(*bg) = 0;
	}
	return !c;
}

int main() {
	int N;
	cin >> N;
	map<V, int> f;
	VV ei(6);
	{
		V latte = { 0,1,2 };
		int id = 0;
		do {
			f[latte] = id;
			ei[id] = latte;
			id++;
		} while (next_permutation(ALL(latte)));
	}
	V g(6);
	for (int i : range(N)) {
		int w;
		cin >> w;
		V x = { 0,1,2 };
		for (int j : range(w)) {
			int a;
			cin >> a;
			if (a == 0) {
				swap(x[0], x[1]);
			}
			else {
				swap(x[1], x[2]);
			}
		}
		g[f[x]]++;
	}
	V o(6, 0);
	do {
		V  malta = g;
		V beet = { 0,1,2 };
		for (int i : range(6)) {
			if (malta[o[i]] == 0)break;
			malta[o[i]]--;
			V nxt(3);
			for (int j : range(3)) {
				nxt[ei[o[i]][j]] = beet[j];
			}
			swap(beet, nxt);
			if (beet == V{0, 1, 2}) {
				cout << "yes" << endl;
				return 0;
			}
		}
	} while (next_value(6,ALL(o)));
	cout << "no" << endl;
	return 0;
}
