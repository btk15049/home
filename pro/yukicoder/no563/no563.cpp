#include<bits/stdc++.h>
using namespace std;
typedef long long LL;

#define CIN_ONLY if(1)
struct cww{cww(){
    CIN_ONLY{
        ios::sync_with_stdio(false);cin.tie(0);
    }
}}star;
#ifdef BTK
#define DEBUG if(1)
#else
#define DEBUG if(0)
#endif

#define fin "\n"
#define FOR(i,bg,ed) for(int i=(bg);i<(ed);i++)
#define REP(i,n) FOR(i,0,n)
#define ALL(v) (v).begin(),(v).end()
#define fi first
#define se second
#define pb push_back
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
const int mod=1e9+7;
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
    if (extgcd(a, mod, x, y) == 1)return (x + mod) % mod;
    else return 0; // unsolvable
}

// äKèÊ
// O(n)
constexpr int SZ=11234;
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


// ëgÇ›çáÇÌÇπnCk (mod mod)
// O(1)
inline LL Comb(LL n,LL k){
    LL u=fact[n];
    LL d=(rfact[k]*rfact[n-k])%mod;
    return u*d%mod;
}



typedef vector<LL> V;
namespace trie{
    constexpr int NONE=-1;
    constexpr int root=0;
    
    int size=1;
    struct node{
        int count;
        int nxt[26];
        node(){
            count=0;
            REP(i,27)nxt[i]=NONE;
        }
    }g[312345];

    void push(string s){
        int v=root;
        for(auto& c:s){
            c-='a';
            if(g[v].nxt[c]==NONE){
                g[v].nxt[c]=size++;
            }
            v=g[v].nxt[c];
            g[v].count++;
        }
    }
    V get_table(int n){
        V ret(n+1,0);
        REP(i,size)ret[g[i].count]++;
        return ret;
    }
}
int main(){
    int n;
    cin>>n;
    REP(i,n){
        string s;
        cin>>s;
        trie::push(s);
    }
    auto t=trie::get_table(n);
    V res(n+1,0);
    FOR(m,1,n+1){
        FOR(k,1,n+1){
            if(t[k]==0)continue;
            REP(l,min(m+1,k+1)){
                LL o_all =n-k;
                LL o_need=m-l;
                if(o_all<o_need)continue;
                LL other_choose=Comb(o_all,o_need);
                LL my_choose  =Comb(k,l);
                LL choose=other_choose*my_choose%mod;
                LL cost=min(l,k-1);
                res[m]+=choose*t[k]*cost%mod;
                res[m]%=mod;
            }
        }
        res[m]+=m*Comb(n,m)%mod;
        res[m]%=mod;
        res[m]=res[m]*fact[m]%mod;
    }
    REP(i,n)cout<<res[i+1]<<fin;
    return 0;
}
