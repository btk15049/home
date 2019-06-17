//https://atcoder.jp/contests/cf18-relay-open/tasks/relay2018_d
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
class reverse_range {private:struct I {int x;int operator*() {return x-1;}bool operator!=(I& lhs) {return x>lhs.x;}void operator++() {--x;}};I i, n;public:reverse_range(int n) :i({ 0 }), n({ n }){}reverse_range(int i, int n) :i({ i }), n({ n }){}I& begin() {return n;}I& end() {return i;}};
class range {private: struct I { int x; int operator*() { return x; }bool operator!=(I& lhs) { return x<lhs.x; }void operator++() { ++x; } }; I i, n;public:range(int n) :i({ 0 }), n({ n }) {}range(int i, int n) :i({ i }), n({ n }) {}I& begin() { return i; }I& end() { return n; }reverse_range operator!(){return reverse_range(*i,*n);}};

double x[112345],w[112345];
int N;
bool ok;
double f(double m){
    double lb = -1e7;
    double ub = 1e7;
    for(int i:range(N)){
        const double len = m/w[i];
        chmax(lb,x[i]-len);
        chmin(ub,x[i]+len);
    }
    ok=(lb<=ub);
    return lb;
}
int main(){
    cin>>N;
    for(int i:range(N)){
        cin>>x[i]>>w[i];
    }
    double lb=0,ub=1e18;
    for(int _:range(300)){
        const double mid = (lb+ub)/2;
        f(mid);
        (ok?ub:lb)=mid;
    }
    cout<<fixed;
    cout<<setprecision(10);
    cout<<f(ub)<<endl;
    return 0;
}