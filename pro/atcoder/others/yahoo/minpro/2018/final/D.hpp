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

const string ok = "Yes";
const string ng = "No";

template<typename T>
vector<int> Zalgorithm(T S) {
	int sz = S.size();
	vector<int> ret(sz);
	ret[0] = sz;
	int i = 1, j = 0;
	while (i < sz) {
		while (i + j < sz && S[j] == S[i + j]) ++j;
		ret[i] = j;
		if (j == 0) { ++i; continue; }
		int k = 1;
		while (i + k < sz && k + ret[k] < j) ret[i + k] = ret[k], ++k;
		i += k; j -= k;
	}
	return ret;
}
namespace _DSU {
	constexpr int BUF = 312345 * 2;
	int ptr = 0;
	int mem[BUF];
	int* get(int size) {
		ptr += size;
		return mem + ptr - size;
	}
	void reset() {
		ptr = 0;
	}
}
class UF {
public:
	int *par, *rank;
	int find(int x) {
		if (par[x] == x) return x;
		else return par[x] = find(par[x]);
	}
	UF(int n) :par(_DSU::get(n + 10)), rank(_DSU::get(n + 10)) {
		for (int i : range(n)) {
			par[i] = i, rank[i] = 0;
		}
	}
	bool unite(int x, int y) {
		x = find(x); y = find(y);
		if (x == y)return false;
		if (rank[x] < rank[y])swap(x, y);
		par[y] = x;
		if (rank[x] == rank[y])rank[x]++;
		return true;
	}
	bool same(int x, int y) {
		return find(x) == find(y);
	}
};

int main() {
	int N; cin >> N;
	vector<int> l(N),A(N);
	cin >> l;
	reverse(ALL(l));
	UF uf(N);
	auto check = [&](){
		if(l[0] != N)return false;
		int i = 1, j = 0;
		while (i < N) {
			while (j < l[i]) {
				uf.unite(j, i + j);
				j++;
			}
			if (j == 0) { ++i; continue; }
			int k = 1;
			while (i + k < N && k + l[k] < j){
				if (l[i + k] != l[k]) {
					return false;
				}
				++k;
			}
			i += k; j -= k;
		}
		return true;
	};
	if (check()) {
		for (int i : range(N)) {
			A[i] = uf.find(i);
		}
		auto B = Zalgorithm(A);
		DEBUG {
			for (auto &it : A)cout << it << ",";
			cout << endl;
		}
		if (B == l) {
			cout << ok << endl;
		}
		else {
			cout << ng << endl;
		}
	}
	else {
		cout << ng << endl;
		return 0;
	}

	return 0;
}
