//http://codeforces.com/contest/1043/problem/F
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

// mを法とするaの逆元
// O(log a)
inline LL invMod(LL a, LL m){
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
void fact_init(int mod){
    fact[0]=1;
    for(int i=1;i<SZ;i++)
        fact[i]=fact[i-1]*i%mod;
    rfact[SZ-1]=invMod(fact[SZ-1],mod);
    for(int i=SZ-1;i>0;i--){
        rfact[i-1]=rfact[i]*i%mod;
    }
}


// 組み合わせnCk (mod mod)
// O(1)
LL Comb(LL n,LL k,int mod){
    LL u=fact[n];
    LL d=(rfact[k]*rfact[n-k])%mod;
    return u*d%mod;
}

int n;
int cnt[312345];
int k[312345];
LL dp[312345];
int solve(const int mod){
    fact_init(mod);
    for(int c:range(1,7)){
        for(int i=300000;i>0;i--){
            dp[i]=0;
            if(k[i]<c)continue;
            dp[i]=Comb(k[i],c,mod);
            for(int j=i+i;j<312345;j+=i){
                dp[i]+=mod-dp[j];
            }
            dp[i]%=mod;
            //if(c==3&&i<20)cout<<dp[i]<<endl;
        }
        if(dp[1]!=0){
            return c;
        }
    }
    return 7;
}
LL gcd(LL a,LL b){
    return (b==0)?a:gcd(b,a%b);
}

int main(){
    cin>>n;
    LL all_gcd = 0;
    for(int i:range(n)){
        int a;
        cin>>a;
        cnt[a]++;
        all_gcd=gcd(all_gcd,a);
    }
    if(all_gcd!=1){
        cout<<-1<<endl;
        return 0;
    }
    if(cnt[1]>0){
        cout<<1<<endl;
        return 0;
    }
    for(int i:range(1,312345)){
        for(int j=i;j<312345;j+=i){
            k[i]+=cnt[j];
        }
    }
    cout<<min(solve(1e9+7),solve(1e9+9))<<endl;

    return 0;
}