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

typedef vector<int> V;
void test() {
	constexpr int N = 21;
	V g(N, 1);
	for (int i : range(N)) {
		V l;
		for (int m : range(i+1)) {
			int sum = 0;
			for (int j : range(i - m, i)) {
				sum ^= g[j];
			}
			l.push_back(sum);
		}
		l.push_back(114514);
		sort(ALL(l));
		unique(ALL(l));
		for (int j : range(1, l.size())) {
			if (l[j - 1] + 1 != l[j]) {
				g[i] = l[j - 1] + 1;
				break;
			}
		}
		cout << i<<" "<<g[i] << endl;
	}
}
LL L;
namespace trie{
	constexpr int K = 2;
	constexpr int EMPTY = -1;
	constexpr char base = '0';
	struct node{
		int nxt[K];
		bool is_leaf() {
			for (int i : range(K)) {
				if (nxt[i] != EMPTY) {
					return false;
				}
			}
			return true;
		}
	}v[112345];
	
	namespace manager {
		int id = 0;
		int get() {
			for (int i : range(K))
				v[id].nxt[i] = EMPTY;
			return id++;
		}
		void reset(){
			id = 0;
		}
	}
	int root;
	void init() {
		manager::reset();
		root = manager::get();
	}
	void insert(string s) {
		int now = root;
		for (char c : s) {
			c -= base;
			int &nxt = v[now].nxt[c];
			if (nxt == EMPTY)nxt = manager::get();
			now = nxt;
		}
	}
	LL get_empty_tree_grundy(LL h) {
		LL ret = 1;
		h++;
		while ((h & 1) == 0) {
			ret <<= 1;
			h >>= 1;
		}
		return ret;
	}
	void dfs(int t,int d, LL &ret) {
		if (v[t].is_leaf()) {
			return;
		}
		else {
			for (int i : range(K)) {
				if (v[t].nxt[i] != EMPTY) {
					dfs(v[t].nxt[i], d + 1, ret);
				}
				else {
					ret ^= get_empty_tree_grundy(L - d - 1);
				}
			}
		}
	}
	LL solve() {
		LL ret = 0;
		dfs(root, 0, ret);
		return ret;
	}
}

int main() {
	int N;
	while (cin >> N >> L) {
		trie::init();
		for (int i : range(N)) {
			string s;
			cin >> s;
			trie::insert(s);
		}
		if (trie::solve()) {
			cout << "Alice" << endl;
		}
		else cout << "Bob" << endl;
	}
	return 0;
}
