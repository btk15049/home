//https://atcoder.jp/contests/cf18-relay-open/tasks/relay2018_e
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


int x[2123456];
int A,B;
constexpr int mod = 1e9+7;
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

int num[3];
int cnt[3][3];
int main(){
    map<char,int> ch={
        {'?',0},
        {'W',1},
        {'F',2}
    };
    string s;
    cin>>s>>A;
    int N=s.size();
    B=N-A;
    for(int i:range(N+2))x[i]=ch[s[i%N]];
    for(int i:range(N)){
        cnt[x[i]][x[i+1]]++;
        num[x[i]]++;
    }
    //for(auto &it:ch)cout<<it.first<<":"<<it.second<<endl;
    //cout<<num[0]<<" "<<num[1]<<" "<<num[2]<<endl;
    A-=num[1];
    B-=num[2];
    LL ret = 0;
    ret+=(cnt[1][2]+cnt[2][1])*Comb(A+B,A)%mod;
    if(A>0&&B>0)ret+=cnt[0][0]*2*Comb(A+B-2,A-1)%mod;
    if(A>0)ret+=(cnt[0][2]+cnt[2][0])*Comb(A+B-1,A-1)%mod;
    if(B>0)ret+=(cnt[0][1]+cnt[1][0])*Comb(A+B-1,A)%mod;
    cout<<ret%mod<<endl;
    return 0;
}