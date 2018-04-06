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
typedef vector<V> VV;
namespace el {
	//s[ed]=bg;
	map<int, int> s;
	void init(int N) {
		for (int i : range(N)) {
			s[i] = i;
		}
	}
	int get(int a) {
		return s.lower_bound(a)->first;
	}
	//[s,t]
	void update(int a, int b) {
		auto it = s.lower_bound(a);
		int bg = it->second;
		vector<int> erase_list;
		erase_list.push_back(it->first);
		++it;
		while (it != s.end()&&it->second<=b) {
			erase_list.push_back(it->first);
			++it;
		}
		int sz = erase_list.size();
		for (int i : range(sz - 1)) {
			s.erase(erase_list[i]);
		}
		s[erase_list.back()] = bg;
	}
}

constexpr int INF = 1123456;
int main() {
	int N,M,Q;
	cin >> N >> M >> Q;
	VV query;
	el::init(N);
	vector<string> ret(Q);
	for (int i : range(M)) {
		int d, a, b;
		cin >> d >> a >> b;
		a--; b--;
		query.push_back({ d,INF,a,b });
	}
	for (int i : range(Q)) {
		int e, s, t;
		cin >> e >> s >> t;
		s--; t--;
		query.push_back({ e,i,s,t });
	}
	sort(ALL(query));
	for (auto q : query) {
		int type = q[1];
		if (type == INF) {
			int a = q[2];
			int b = q[3];
			el::update(a, b);
		}
		else {
			int a = q[2];
			int b = q[3];
			if (a < b) {
				if (el::get(a) >= b) {
					ret[type] = "Yes";
				}
				else {
					ret[type] = "No";
				}
			}
			else {
				ret[type] = "Yes";
			}
		}

	}

	for (int i : range(Q)) {
		cout << ret[i] << endl;
	}
	return 0;
}
