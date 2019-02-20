//https://atcoder.jp/contests/cf18-relay-open/tasks/relay2018_h
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

int N,M,K;
constexpr int mod = 1e9+7;
LL dp[1<<20];

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

//O(1)
LL Perm(LL n,LL k){
    LL u=fact[n];
    LL d=rfact[n-k]%mod;
    return u*d%mod;
}

int main(){
    cin>>N>>M>>K;
    chmin(K,N);
    LL ret = 0;
    int win = (1<<N)-M;
    int los = M-1;
    for(int i:range(1<<N)){
        bitset<22> b(i);
        if(b.count()>K)continue;
        if(i<los)continue;
        dp[i]=Comb(win,i-los);
        dp[i]=dp[i]*fact[i]%mod;
        dp[i]=dp[i]*fact[win-(i-los)]%mod;
        //cerr<<i<<" "<<fact[i]<<" "<<fact[win-(i-los)]<<endl;
    }
    for(int i:range(N)){
        for(int j:range(1<<N)){
            bitset<22> b(j);
            if(b.count()>K)continue;
            if(b[i]){
                dp[j]+=mod-dp[j^(1<<i)];
                dp[j]%=mod;
            }
        }
    }
    for(int i:range(1<<N)){
        bitset<22> b(i);
        if(b.count()>K)continue;
        ret+=dp[i];
        //cout<<i<<" "<<dp[i]<<endl;
    }
    ret%=mod;
    ret<<=N;
    ret%=mod;
    cout<<ret<<endl;
    return 0;
}