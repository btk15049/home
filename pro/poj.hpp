#ifndef VS
#include<iostream>
#include<vector>
#include<algorithm>
#include<stack>
#include<queue>
#include<map>
#include<set>
#include<iomanip>
#include<string>
#include<assert.h>
#include<math.h>
#include<stdio.h>
#include<ctype.h>
#endif
using namespace std;
typedef long long LL;

#ifdef BTK
#define DEBUG if(1)
#else
#define DEBUG if(0)
#endif

#define FOR(i,bg,ed) for(int i=(bg);i<(ed);i++)
#define REP(i,n) FOR(i,0,n)
#define ALL(v) (v).begin(),(v).end()
#define REC(ret, ...) std::function<ret (__VA_ARGS__)>
template <typename T>inline bool chmin(T &l, T r) { bool a = l>r; if (a)l = r; return a; }
template <typename T>inline bool chmax(T &l, T r) { bool a = l<r; if (a)l = r; return a; }

struct input {
	bool success;
	input(){success = true;}
#ifdef BTK
	template<typename T>inline input& operator>>(T& x) {success = !!(cin >> x);return *this;}
#else
	inline input& operator>>(LL& x) {success = (scanf("%lld", &x) != EOF);return *this;}
	inline input& operator>>(int& x) {success = (scanf("%d", &x) != EOF);return *this;}
	inline input& operator>>(char* x) {success = (scanf("%s", x) != EOF);return *this;}
	inline input& operator>>(double& x) {success = (scanf("%llf", &x) != EOF);return *this;}
#endif
}in;

const char space = ' ';
const char ln = '\n';
struct output {
#ifdef BTK
	template<typename T>inline output& operator<<(T x) {cout << x; return (*this);}
	inline void fp(const double x, const char* s) { char buf[20];sprintf(buf, s, x); cout << buf;}
#else
	inline output& operator<<(const string& x) { printf("%s", x.c_str()); return *this; }
	inline output& operator<<(const int x) { printf("%d", x); return *this;}
	inline output& operator<<(const char x) { putchar(x); return *this;}
	inline output& operator<<(const LL x) { printf("%lld", x); return *this;}
	inline output& operator<<(const double x) { printf("%lf", x); return *this;}
	inline void fp(const double x, const char* s) {printf(s, x);}
#endif
}out;

int main() {
	
	return 0;
}
