//http://codeforces.com/contest/1042/problem/D
#include<bits/stdc++.h>

using namespace std;
typedef long long LL;

#ifdef BTK
#define DEBUG if(1)
#else
#define CIN_ONLY if(1)
struct cww {cww() {CIN_ONLY{ios::sync_with_stdio(false); cin.tie(0);}}
}star;
#define DEBUG if(0)
#endif

#define ALL(v) (v).begin(),(v).end()
#define REC(ret, ...) std::function<ret (__VA_ARGS__)>
template <typename T>inline bool chmin(T &l, T r){bool a = l>r; if (a)l = r; return a;}
template <typename T>inline bool chmax(T &l, T r){bool a = l<r; if (a)l = r; return a;}
template <typename T>istream& operator>>(istream &is, vector<T> &v){for (auto &it : v)is >> it;return is;}

class range {private: struct I { int x; int operator*() { return x; }bool operator!=(I& lhs) { return x<lhs.x; }void operator++() { ++x; } }; I i, n;public:range(int n) :i({ 0 }), n({ n }) {}range(int i, int n) :i({ i }), n({ n }) {}I& begin() { return i; }I& end() { return n; }};

namespace BIT_{
    using RET = int;
    constexpr int BUF = 2123456;
    int ptr = 0;
    RET t[BUF];
    inline RET* get(const int size){
        ptr+=size;
        return t+ptr-size;
    }
}
//[1,n],0は扱えない!
struct BIT{
    using T=BIT_::RET;
    T* bit;
    int sz;
    BIT(int n):bit(BIT_::get(n+10)),sz(n){
        fill(bit,bit+n+10,0);
    }
    T sum(int i){
        T s=0;
        while(i>0){
            s+=bit[i];
            i-=i&-i;
        }
        return s;
    }
    T sum(int lb,int ub){
        return sum(ub)-sum(lb-1);
    }
    void add(int i,T x){
        while(i<=sz){
            bit[i]+=x;i+=i&-i;
        }
    }
    //v[1]+v[2]+...+v[x]>=wとなる最小のxを求める
    int lowerbound(T w){
        if(w<=0)return 0;
        int x=0;
        for(int k = (1<<(31-__builtin_clz(sz)));k >0 ;k>>=1)
            if(x+k<=sz&&bit[x+k]<w){
                w-=bit[x+k];
                x+=k;
            }
        return x+1;
    }
};   

int n;LL t;
LL a[212345];
LL latte[512345];
int malta=0;
int id(LL x){
    return lower_bound(latte,latte+malta,x)-latte;
}
int main() {
    cin>>n>>t;
    for(int i:range(n))cin>>a[i];
    for(int i:range(1,n))a[i]+=a[i-1];
    for(int i:range(n)){
        latte[malta++]=a[i];
        latte[malta++]=a[i]-t;
    }
    latte[malta++]=0;
    latte[malta++]=t;
    sort(latte,latte+malta);
    malta=unique(latte,latte+malta)-latte;
    BIT bit(malta+10);
    bit.add(id(0)+1,1);
    LL ret = 0;
    for(int i:range(n)){
        ret+=bit.sum(id(a[i]-t)+2,malta+5);
        bit.add(id(a[i])+1,1);
    }
    cout<<ret<<endl;
    return 0;
}
