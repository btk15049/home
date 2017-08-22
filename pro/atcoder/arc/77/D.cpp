#include<bits/stdc++.h>
using namespace std;
typedef long long LL;

#define CIN_ONLY if(1)
struct cww{cww(){
    CIN_ONLY{
        ios::sync_with_stdio(false);cin.tie(0);
    }
}}star;
#define fin "\n"
#define FOR(i,bg,ed) for(int i=(bg);i<(ed);i++)
#define REP(i,n) FOR(i,0,n)
#define ALL(v) (v).begin(),(v).end()
#define fi first
#define se second
#define pb push_back
#define DEBUG if(0)
#define REC(ret, ...) std::function<ret (__VA_ARGS__)>
template <typename T>inline bool chmin(T &l,T r)
{bool a=l>r;if(a)l=r;return a;}
template <typename T>inline bool chmax(T &l,T r)
{bool a=l<r;if(a)l=r;return a;}
template <typename T>
istream& operator>>(istream &is,vector<T> &v){
    for(auto &it:v)is>>it;
    return is;
}
typedef vector<int> V;
const int MOD=1e9+7;
// a x + b y = gcd(a, b)
// O(log (a+b) )
LL extgcd(LL a, LL b, LL &x, LL &y) {
    LL g = a; x = 1; y = 0;
    if (b != 0) g = extgcd(b, a % b, y, x), y -= (a / b) * x;
    return g;
}

// mÇñ@Ç∆Ç∑ÇÈaÇÃãtå≥
// O(log a)
LL invMod(LL a) {
    LL x, y;
    if (extgcd(a, MOD, x, y) == 1)return (x + MOD) % MOD;
    else return 0; // unsolvable
}
// äKèÊ
// O(n)
#define SZ 1000010
LL fact[SZ];
struct fact_{
    fact_(){
        fact[0]=1;
        for(int i=1;i<SZ;i++)
            fact[i]=fact[i-1]*i%MOD;
    }
}fact_init;


// ëgÇ›çáÇÌÇπnCk (mod MOD)
// O(log n)
LL Comb(LL n,LL k){
    LL u=fact[n];
    LL d=(fact[k]*fact[n-k])%MOD;
    return (u*invMod(d))%MOD;
}


int main(){
    int n;cin>>n;
    V a(n+1);
    cin>>a;
    V cnt(n);
    V pos;
    REP(i,n+1){
        a[i]--;
        cnt[a[i]]++;
    }
    REP(i,n+1)if(cnt[a[i]]==2)pos.pb(i);
    int x=pos.front();
    int y=pos.back()-pos.front()-1;
    int z=n-pos.back();
    FOR(k,1,n+2){
        LL res=0;
        if(k>=2)res+=Comb(n-1,k-2);
        if(k<n)res+=Comb(n-1,k);
        if(k>=1&&k<=n){
            if(x+z>=k-1)res+=Comb(x+z,k-1);
            if(y>0){
                res+=2*Comb(n-1,k-1);
                if(x+z>=k-1)res+=2*MOD-2*Comb(x+z,k-1);
            }
        }
        cout<<res%MOD<<endl;
    }
    return 0;
}
