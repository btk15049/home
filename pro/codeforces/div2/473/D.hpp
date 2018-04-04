#include<bits/stdc++.h>

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

constexpr int MAX_N = 3123456;
namespace pomae {
	constexpr int U = MAX_N;
	vector<int> primes[U];
	bool isp[U];
	int cnt = 0;
	struct pre {
		pre(){
			for (int i : range(U))isp[i] = true;
			isp[0] = isp[1] = false;
			for (int i : range(U))if (isp[i]) {
				cnt++;
				primes[i].push_back(i);
				for (int j = i + i; j < U; j += i) {
					isp[j] = false;
					primes[j].push_back(i);
				}
			}
		}
	}init;
}
bool used[MAX_N];
int a[212345];
bool check(int t) {
	for (int p : pomae::primes[t]) {
		if (used[p]) {
			return false;
		}
	}
	return true;
}
int main() {
	int N; cin >> N;
	for (int i : range(N))cin >> a[i];
	for (int i : range(MAX_N))used[i] = false;
	string spaces(N, ' '); spaces.back() = '\n';
	int id = -1;
	for (int i : range(N)) {
		if (check(a[i])) {
			for (int p : pomae::primes[a[i]])used[p] = true;
		}
		else {
			id = i;break;
		}
	}
	if (id != -1) {
		while (check(a[id]) == false) {
			a[id]++;
		}
		for (int p : pomae::primes[a[id]])used[p] = true;
		id++;
		int pid = 0;
		while (id < N) {
			while (pomae::isp[pid] == false || used[pid])pid++;
			a[id++] = pid++;
		}
	}
	for (int i : range(N)) {
		cout << a[i] << spaces[i];
	}
	return 0;
}
