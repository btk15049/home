//https://atcoder.jp/contests/nikkei2019-final/tasks/nikkei2019_final_e
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
constexpr int mod = 1e9+7;
//O(log a)
LL pow_mod(LL a,LL n,int M=mod){
    LL res=1;
    a%=M;
    while(n){
        if(n&1)
            res=(res*a)%M;
        a=(a*a)%M;
        n>>=1;
    }
    return res;
}
LL dp[5123][2];
LL cnt[5123];
LL CNT(LL len){
    if(len<K)return 1;
    return cnt[len];
}
int main(){
    cin>>N>>K;
    dp[0][0]=1;
    for(int i:range(K,N+10)){
        LL x = (i-K)*(i-K+1)/2;
        cnt[i]=pow_mod(2,x);
    }
    for(int i:range(1,N+2)){
        for(int j:range(i)){
            dp[i][1]+=dp[j][0]*CNT(i-j-1)%mod;
            dp[i][0]+=dp[j][1]*CNT(i-j-1)%mod;
        }
        //if(N<=10){cerr<<i<<" "<<dp[i][0]<<" "<<dp[i][1]<<endl;}
        dp[i][0]%=mod;
        dp[i][1]%=mod;
    }
    LL ret=(dp[N+1][1]-dp[N+1][0]+mod)%mod;
    cout<<ret<<endl;
    return 0;
}