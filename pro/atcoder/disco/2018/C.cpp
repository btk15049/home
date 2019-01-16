//https://beta.atcoder.jp/contests/ddcc2019-qual/tasks/ddcc2018_qual_c
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

constexpr int mod = 1e9+7;
int main(){
    int N;
    cin>>N;
    vector<LL> dp(N+1);
    vector<LL> sum(N+1,0);
    dp[1]=1;
    sum[1]=1;
    for(int i:range(2,N+1)){
        LL p = 1;
        for(int j:range(10))p=p*i%mod;
        sum[i]=p;
        dp[i]=p-sum[i-1]+mod;
        dp[i]%=mod;
    }
    LL ret=0;
    for(int i:range(1,N+1)){
        ret+=dp[i]*sum[N/i]%mod;
    }
    ret%=mod;
    cout<<ret<<endl;

    return 0;
}