//https://atcoder.jp/contests/cf18-relay-open/tasks/relay2018_f
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

int N,K;
LL t[112345];
double dp[2][2][312];
double ds[312];
void solve(int n){
    double *cur_arr = dp[n%2][0];
    double *cur_dep = dp[n%2][1];
    double *nxt_arr = dp[1-n%2][0];
    double *nxt_dep = dp[1-n%2][1];

    if(n==N){
        for(int i:range(K)){
            cur_arr[i]=0;
        }
        return;
    }
    else{
        solve(n+1);
    }

    for(int i:range(K)){
        cur_dep[i]=t[n]+nxt_arr[(i+t[n])%K];
    }
    for(int i:range(K)){
        ds[i+1]=ds[i]+cur_dep[i];
    }
    cur_arr[0]=((K-1)*K/2.0)/K + ds[K]/K;
    for(int i:range(1,K)){
        cur_arr[i]=((K-i-1)*(K-i)/2.0)/K + (ds[K]-ds[i])/K + (i*1.0/K)*((K-i)+cur_arr[0]);
    }
}
int main(){
    cout<<fixed;
    cout<<setprecision(10);
    cin>>N>>K;
    for(int i:range(N))cin>>t[i];
    solve(0);
    cout<<dp[0][0][0]<<endl;
    return 0;
}