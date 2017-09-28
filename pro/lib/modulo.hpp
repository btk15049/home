#include <bits/stdc++.h>

using namespace std;
typedef long long LL;
typedef vector<LL> VLL;
typedef vector<VLL> VVLL;
const int MOD=(int)(1e9+7);
// aとbの最大公約数
// O(log (a+b) )
LL gcd(LL a,LL b){
    return (b==0)?a:gcd(b,a%b);
}

// aとbの最小公倍数
// O(log (a+b) )
LL lcm(LL a,LL b){
    return (a/gcd(a,b))*b;
}

// a x + b y = gcd(a, b)
// O(log (a+b) )
LL extgcd(LL a, LL b, LL &x, LL &y) {
    LL g = a; x = 1; y = 0;
    if (b != 0) g = extgcd(b, a % b, y, x), y -= (a / b) * x;
    return g;
}

// mを法とするaの逆元
// O(log a)
LL invMod(LL a) {
    LL x, y;
    if (extgcd(a, mod, x, y) == 1)return (x + mod) % mod;
    else return 0; // unsolvable
}

// iCjの組み合わせを全列挙してvectorに格納
// (0<=j<=i<=n)
// O(n^2)
VVLL init_comb(int n){
    n++;
    VVLL res(n,VLL(n,0));
    for(int i=0;i<n;i++)res[i][0]=1;
    for(int i=1;i<n;i++)
        for(int j=1;j<=i;j++)
            res[i][j]=(res[i-1][j]+res[i-1][j-1])%mod;
    return res;
}

// 階乗
// O(n)
#define SZ 1000010
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
LL Parm(LL n,LL k){
    LL u=fact[n];
    LL d=rfact[n-k]%mod;
    return u*d%mod;
}

//O(k)
LL Parm_fast(LL n,LL k){
    LL res=1;
    for(LL i = n; i > n-k; i--)res=(res*i)%mod;
       return res;
}

//完全順列
LL ParfectPerm(LL n){
    LL m0=1,m1=0;
    for(LL i = 2; i <= n; i++){
        LL m2=((i-1)*(m0+m1))%mod;
        m0=m1;
        m1=m2;
    }
    return m1;
}

// 1~nの逆元を求める(mod mod)
// O(n)で列挙
VLL list_mod_inverse(LL n){
    VLL inv(n + 1);
    inv[1] = 1;
    for (int i = 2; i <= n; ++i)
        inv[i] = inv[mod % i] * (mod - mod / i) % mod;
    return inv;
}

//a^n (mod mod)
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



LL POW(LL a,LL n){
    LL ret=1;
    REP(i,n)ret*=a;
    return ret;
}

typedef pair<LL,LL> P;

/*
  n! mod pp : pp=p^n
*/
P calc(LL n,LL p,LL pp){
    if(n<p)return {fact[n],0};
    auto nxt=calc(n/p,p,pp);
    LL numpp=n/pp;
    LL x=pow_mod(fact[pp-1],numpp,pp);
    x*=fact[n%pp];
    return {x*nxt.first%pp,n/p+nxt.second};
}


/*
  nCk mod p^cnt
*/
LL comb(LL n,LL k,LL p,int cnt){
    LL pp=POW(p,cnt);
    set_fact(p,pp);
    auto u = calc(n,p,pp);
    auto d1= calc(k,p,pp);
    auto d2= calc(n-k,p,pp);
    P d={d1.first*d2.first%pp,d1.second+d2.second};
    LL ret=u.first*inv(d.first,pp)%pp;
    REP(i,u.second-d.second){
	ret*=p;
	ret%=pp;
    }
    return ret;
}
