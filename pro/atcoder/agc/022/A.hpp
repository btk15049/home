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
	string inf;
	for (int i : range(26))inf += string(1, 'a' + i);
	reverse(ALL(inf));
	string s;
	while (cin >> s) {
		if (s == inf) {
			cout << -1 << endl;
		}
		else {
			if (s.size() < 26) {
				set<char> x;
				for (auto &it : s)x.insert(it);
				for (int i : range(26))if (x.count('a' + i) == 0) {
					cout << s << string(1, 'a' + i) << endl;
					break;
				}
			}
			else {
				set<char> x;
				char last;
				while (s.size()) {
					last = s.back();
					s.pop_back();
					x.insert(last);
					if (s.back() < last)break;
				}
				last = s.back(); s.pop_back();
				cout << s << *x.upper_bound(last) << endl;
			}
		}
	}
	
	return 0;
}
