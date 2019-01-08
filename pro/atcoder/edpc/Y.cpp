//https://atcoder.jp/contests/dp/tasks/dp_y
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
int R,C,N;
int r[3123];
int c[3123];
// mを法とするaの逆元
// O(log a)
inline LL invMod(LL a, LL m=mod){
  LL b = m, u = 1, v = 0;
  while (b) {
    LL t = a / b;
    swap(a -= t * b, b);
    swap(u -= t * v, v);
  }
  return (u % m + m) % m;
}


// 階乗
// O(n)
constexpr int SZ = 1123456;
LL fact[SZ];
LL rfact[SZ];
struct fact_{
    fact_(){
        fact[0]=1;
        for(int i=1;i<SZ;i++)
            fact[i]=fact[i-1]*i%mod;
        rfact[SZ-1]=invMod(fact[SZ-1]);
        for(int i=SZ-1;i>0;i--){
            rfact[i-1]=rfact[i]*i%mod;
        }
    }
}fact_init;


// 組み合わせnCk (mod mod)
// O(1)
LL Comb(LL n,LL k){
    LL u=fact[n];
    LL d=(rfact[k]*rfact[n-k])%mod;
    return u*d%mod;
}
pair<int,int> a[3123];
LL dp[3123][2];
LL calc(LL dr,LL dc){
    return Comb(dr+dc,dr);
}
int main(){
    cin>>R>>C>>N;
    for(int i:range(N)){
        cin>>r[i+1]>>c[i+1];
        a[i+1]={r[i+1]+c[i+1],i+1};
    }
    r[0]=1;c[0]=1;
    r[N+1]=R;c[N+1]=C;
    a[0]={2,0};
    a[N+1]={R+C,N+1};
    sort(a,a+N+2);
    dp[0][0]=1;
    for(int e:range(1,N+2)){
        int i = a[e].second;
        for(int j:range(N+2)){
            if(i!=j&&r[i]>=r[j]&&c[i]>=c[j]){
                dp[i][1]+=dp[j][0]*calc(r[i]-r[j],c[i]-c[j])%mod;
                dp[i][0]+=dp[j][1]*calc(r[i]-r[j],c[i]-c[j])%mod;
            }
        }
        dp[i][0]%=mod;
        dp[i][1]%=mod;
    }
    cout<<(mod+dp[N+1][1]-dp[N+1][0])%mod<<endl;
    return 0;
}