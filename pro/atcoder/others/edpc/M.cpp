//https://atcoder.jp/contests/dp/tasks/dp_m
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

LL as[1123456];
int N,K;
int a[1123];
constexpr int mod = 1e9+7;
inline LL sum(int l,int r){
    return (as[r]+mod-as[l])%mod;
}
int main(){
    cin>>N>>K;
    for(int i:range(N))cin>>a[i];
    vector<LL> dp(K+1);
    dp[0]=1;
    for(int i:range(N)){
        vector<LL> nxt(K+1);
        for(int k:range(K+1)){
            as[k+1]=as[k]+dp[k];
            nxt[k]=sum(max(0,k-a[i]),k+1);
        }

        swap(dp,nxt);
    }
    cout<<dp.back()<<endl;
    return 0;
}