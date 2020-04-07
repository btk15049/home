//http://codeforces.com/contest/1055/problem/C
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#ifdef BTK
#define DEBUG if(1)
#else
#define CIN_ONLY if(1)
struct cww {cww() {CIN_ONLY{ios::sync_with_stdio(false); cin.tie(0);}}}star;
#define DEBUG if(0)
#endif
#define ALL(v) (v).begin(),(v).end()
#define REC(ret, ...) std::function<ret (__VA_ARGS__)>
template <typename T>inline bool chmin(T &l, T r){bool a = l>r; if (a)l = r; return a;}
template <typename T>inline bool chmax(T &l, T r){bool a = l<r; if (a)l = r; return a;}
template <typename T>istream& operator>>(istream &is, vector<T> &v){for (auto &it : v)is >> it;return is;}
class range {private: struct I { int x; int operator*() { return x; }bool operator!=(I& lhs) { return x<lhs.x; }void operator++() { ++x; } }; I i, n;public:range(int n) :i({ 0 }), n({ n }) {}range(int i, int n) :i({ i }), n({ n }) {}I& begin() { return i; }I& end() { return n; }};

LL gcd(LL a,LL b){
    return (b==0)?a:gcd(b,a%b);
}
int main(){
    LL la,ra,ta;
    LL lb,rb,tb;
    cin>>la>>ra>>ta>>lb>>rb>>tb;
    LL g = gcd(ta,tb);
    LL diff = la-lb;
    diff%=g;
    LL d = rb-lb;
    LL ret=0;
    for(int i:range(-1,2)){
        LL lc=la-diff+i*g;
        LL rc=d+lc;
        LL l=max(la,lc);
        LL r=min(ra,rc);
        chmax(ret,r-l+1);
    }
    cout<<ret<<endl;
    return 0;
}