//http://codeforces.com/contest/1073/problem/D
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#ifdef BTK
#define DEBUG if(1)
#else
#define CIN_ONLY if(0)
struct cww {cww() {CIN_ONLY{ios::sync_with_stdio(false); cin.tie(0);}}}star;
#define DEBUG if(0)
#endif
#define ALL(v) (v).begin(),(v).end()
#define REC(ret, ...) std::function<ret (__VA_ARGS__)>
template <typename T>inline bool chmin(T &l, T r){bool a = l>r; if (a)l = r; return a;}
template <typename T>inline bool chmax(T &l, T r){bool a = l<r; if (a)l = r; return a;}
template <typename T>istream& operator>>(istream &is, vector<T> &v){for (auto &it : v)is >> it;return is;}
class range {private: struct I { int x; int operator*() { return x; }bool operator!=(I& lhs) { return x<lhs.x; }void operator++() { ++x; } }; I i, n;public:range(int n) :i({ 0 }), n({ n }) {}range(int i, int n) :i({ i }), n({ n }) {}I& begin() { return i; }I& end() { return n; }};

int n;
LL T;
LL a[212345];
pair<LL,int> b[212345];

namespace BIT_{
    using RET = LL;
    constexpr int BUF = 1123456;
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
};

int main(){
    scanf("%d%lld",&n,&T);
    LL tot = 0;
    BIT bit(n+10);
    BIT cnt(n+10);
    for(int i:range(n)){
        scanf("%lld",a+i);
        b[i]={a[i],i+1};
        tot+=a[i];
        bit.add(b[i].second,b[i].first);
        cnt.add(b[i].second,1);
    }
    sort(b,b+n);
    reverse(b,b+n);

    LL ret = 0;
    int pos = 0;
    for(int i:range(n)){
        LL cycle = T/tot;
        T-=cycle*tot;
        ret+=cycle*(n-i);

        LL latte = bit.sum(pos+1,n);
        if(latte<=T){
            T-=latte;
            ret+=cnt.sum(pos+1,n);
            pos = 0;
        }
        int ng = n;
        int ok = pos;
        while(ng-ok>1){
            const int mid = (ok+ng)/2;
            if(bit.sum(pos+1,mid)<=T)ok=mid;
            else ng=mid;
        }
        //cout<<ng<<"  "<<ok<<endl;
        T-=bit.sum(pos+1,ok);
        ret+=cnt.sum(pos+1,ok);
        pos = ok;
        bit.add(b[i].second,-b[i].first);
        cnt.add(b[i].second,-1);
        tot-=b[i].first;
        //cout<<ret<<" "<<T<<" "<<pos<<endl;
    }

    printf("%lld\n",ret);
    return 0;
}