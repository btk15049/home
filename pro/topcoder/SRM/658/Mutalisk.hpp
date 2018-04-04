#include<bits/stdc++.h>
using namespace std;

typedef long long LL;

#ifdef BTK
#define DEBUG if(1)
#else
#define DEBUG if(0)
#endif

#define ALL(v) (v).begin(),(v).end()
#define REC(ret, ...) std::function<ret (__VA_ARGS__)>
template <typename T>inline bool chmin(T &l, T r){bool a = l>r; if (a)l = r; return a;}
template <typename T>inline bool chmax(T &l, T r){bool a = l<r; if (a)l = r; return a;}
template <typename T>istream& operator>>(istream &is, vector<T> &v){for (auto &it : v)is >> it;return is;}

class range {private: struct I { int x; int operator*() { return x; }bool operator!=(I& lhs) { return x<lhs.x; }void operator++() { ++x; } }; I i, n;public:range(int n) :i({ 0 }), n({ n }) {}range(int i, int n) :i({ i }), n({ n }) {}I& begin() { return i; }I& end() { return n; }};


class Mutalisk {
public:
	int minimalAttacks(vector <int>);
};

typedef tuple<int, int, int> T;
namespace pre {
	vector<T> edge[70];
	bool ok[8][21][61];
	struct ini {
		ini() {
			for (int n : range(1, 70)) {
				for (int i : range(8)) {
					for (int j : range(21)) {
						for (int k : range(61)) {
							ok[i][j][k] = (i * 9 + j * 3 + k >= n);
						}
					}
				}
				for (int ii : range(8)) {
					const int i = 7 - ii;
					for (int jj : range(21)) {
						const int j = 20 - jj;
						for (int kk : range(61)) {
							const int k = 60 - kk;
							if (ok[i][j][k]) {
								if (i < 7)ok[i + 1][j][k] = false;
								if (j < 20)ok[i][j + 1][k] = false;
								if (k < 60)ok[i][j][k + 1] = false;
							}
						}
					}
				}
				for (int i : range(8)) {
					for (int j : range(21)) {
						for (int k : range(61)) {
							if (ok[i][j][k])edge[n].push_back(T(i, j, k));
						}
					}
				}
			}
		}
	}t;
}
constexpr int INF = 1e6;
int dp[112][112];
int nxt[112][112];
inline bool check(int n, vector<int> & x) {
	n++;
	for (int i : range(n))for (int j : range(n))dp[i][j] = -INF;
	dp[n - 1][n - 1] = n - 1;
	for (int hp : x) {
		for (int i : range(n))for (int j : range(n))nxt[i][j] = -INF;
		for (int i : range(n))for (int j : range(n)) {
			for (auto &e : pre::edge[hp]) {
				int a, b, c; tie(a, b, c) = e;
				if (a+b+c<n && i >= a && j >= b && dp[i][j] >= c) {
					chmax(nxt[i - a][j - b], dp[i][j] - c);
				}
			}
		}
		for (int i : range(n))for (int j : range(n))dp[i][j] = nxt[i][j];
	}
	for (int i : range(n))for (int j : range(n))if (dp[i][j] >= 0)return true;
	return false;
}

int Mutalisk::minimalAttacks(vector <int> x) {
	int ub = 110;
	int lb = 0;
	while (ub - lb > 1) {
		const int mid = (lb + ub) / 2;
		(check(mid, x) ? ub : lb) = mid;
	}
	return ub;
}


double test0() {
	int t0[] = {12,10,4};
	vector <int> p0(t0, t0+sizeof(t0)/sizeof(int));
	Mutalisk * obj = new Mutalisk();
	clock_t start = clock();
	int my_answer = obj->minimalAttacks(p0);
	clock_t end = clock();
	delete obj;
	cout <<"Time: " <<(double)(end-start)/CLOCKS_PER_SEC <<" seconds" <<endl;
	int p1 = 2;
	cout <<"Desired answer: " <<endl;
	cout <<"\t" << p1 <<endl;
	cout <<"Your answer: " <<endl;
	cout <<"\t" << my_answer <<endl;
	if (p1 != my_answer) {
		cout <<"DOESN'T MATCH!!!!" <<endl <<endl;
		return -1;
	}
	else {
		cout <<"Match :-)" <<endl <<endl;
		return (double)(end-start)/CLOCKS_PER_SEC;
	}
}
double test1() {
	int t0[] = {54,18,6};
	vector <int> p0(t0, t0+sizeof(t0)/sizeof(int));
	Mutalisk * obj = new Mutalisk();
	clock_t start = clock();
	int my_answer = obj->minimalAttacks(p0);
	clock_t end = clock();
	delete obj;
	cout <<"Time: " <<(double)(end-start)/CLOCKS_PER_SEC <<" seconds" <<endl;
	int p1 = 6;
	cout <<"Desired answer: " <<endl;
	cout <<"\t" << p1 <<endl;
	cout <<"Your answer: " <<endl;
	cout <<"\t" << my_answer <<endl;
	if (p1 != my_answer) {
		cout <<"DOESN'T MATCH!!!!" <<endl <<endl;
		return -1;
	}
	else {
		cout <<"Match :-)" <<endl <<endl;
		return (double)(end-start)/CLOCKS_PER_SEC;
	}
}
double test2() {
	int t0[] = {1,1,1,1,1,1,1,1,1,1};
	vector <int> p0(t0, t0+sizeof(t0)/sizeof(int));
	Mutalisk * obj = new Mutalisk();
	clock_t start = clock();
	int my_answer = obj->minimalAttacks(p0);
	clock_t end = clock();
	delete obj;
	cout <<"Time: " <<(double)(end-start)/CLOCKS_PER_SEC <<" seconds" <<endl;
	int p1 = 4;
	cout <<"Desired answer: " <<endl;
	cout <<"\t" << p1 <<endl;
	cout <<"Your answer: " <<endl;
	cout <<"\t" << my_answer <<endl;
	if (p1 != my_answer) {
		cout <<"DOESN'T MATCH!!!!" <<endl <<endl;
		return -1;
	}
	else {
		cout <<"Match :-)" <<endl <<endl;
		return (double)(end-start)/CLOCKS_PER_SEC;
	}
}
double test3() {
	int t0[] = {55,60,53};
	vector <int> p0(t0, t0+sizeof(t0)/sizeof(int));
	Mutalisk * obj = new Mutalisk();
	clock_t start = clock();
	int my_answer = obj->minimalAttacks(p0);
	clock_t end = clock();
	delete obj;
	cout <<"Time: " <<(double)(end-start)/CLOCKS_PER_SEC <<" seconds" <<endl;
	int p1 = 13;
	cout <<"Desired answer: " <<endl;
	cout <<"\t" << p1 <<endl;
	cout <<"Your answer: " <<endl;
	cout <<"\t" << my_answer <<endl;
	if (p1 != my_answer) {
		cout <<"DOESN'T MATCH!!!!" <<endl <<endl;
		return -1;
	}
	else {
		cout <<"Match :-)" <<endl <<endl;
		return (double)(end-start)/CLOCKS_PER_SEC;
	}
}
double test4() {
	int t0[] = {60};
	vector <int> p0(t0, t0+sizeof(t0)/sizeof(int));
	Mutalisk * obj = new Mutalisk();
	clock_t start = clock();
	int my_answer = obj->minimalAttacks(p0);
	clock_t end = clock();
	delete obj;
	cout <<"Time: " <<(double)(end-start)/CLOCKS_PER_SEC <<" seconds" <<endl;
	int p1 = 7;
	cout <<"Desired answer: " <<endl;
	cout <<"\t" << p1 <<endl;
	cout <<"Your answer: " <<endl;
	cout <<"\t" << my_answer <<endl;
	if (p1 != my_answer) {
		cout <<"DOESN'T MATCH!!!!" <<endl <<endl;
		return -1;
	}
	else {
		cout <<"Match :-)" <<endl <<endl;
		return (double)(end-start)/CLOCKS_PER_SEC;
	}
}
double test5() {
	int t0[] = {60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60};
	vector <int> p0(t0, t0+sizeof(t0)/sizeof(int));
	Mutalisk * obj = new Mutalisk();
	clock_t start = clock();
	int my_answer = obj->minimalAttacks(p0);
	clock_t end = clock();
	delete obj;
	cout <<"Time: " <<(double)(end-start)/CLOCKS_PER_SEC <<" seconds" <<endl;
	int p1 = 93;
	cout <<"Desired answer: " <<endl;
	cout <<"\t" << p1 <<endl;
	cout <<"Your answer: " <<endl;
	cout <<"\t" << my_answer <<endl;
	if (p1 != my_answer) {
		cout <<"DOESN'T MATCH!!!!" <<endl <<endl;
		return -1;
	}
	else {
		cout <<"Match :-)" <<endl <<endl;
		return (double)(end-start)/CLOCKS_PER_SEC;
	}
}

int main() {
	int time;
	bool errors = false;
	
	time = test0();
	if (time < 0)
		errors = true;
	
	time = test1();
	if (time < 0)
		errors = true;
	
	time = test2();
	if (time < 0)
		errors = true;
	
	time = test3();
	if (time < 0)
		errors = true;
	
	time = test4();
	if (time < 0)
		errors = true;
	
	time = test5();
	if (time < 0)
		errors = true;
	
	if (!errors)
		cout <<"You're a stud (at least on the example cases)!" <<endl;
	else
		cout <<"Some of the test cases had errors." <<endl;
}

//Powered by [KawigiEdit] 2.0!
