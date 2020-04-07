//http://codeforces.com/contest/1036/problem/F
#include<bits/stdc++.h>

using namespace std;
typedef long long LL;

#ifdef BTK
#define DEBUG if(1)
#else
#define CIN_ONLY if(0)
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


int a[312345];
int b[312345];
LL p[100];
LL ub[100];
LL safe_pow(LL a,LL n){
    LL ret=1;
    while(n){
        if(n%2==1){
            LL nxt = ret*a;
            if(nxt!=0&&nxt%ret==0&&nxt/ret==a)ret=nxt;
            else return -1;
        }
        n/=2;
        LL b=a*a;
        if(n==0)break;
        else{
            if(b!=0&&b%a==0&&b/a==a)a=b;
            else return -1;
        }
    }
    return ret;
}
LL num(LL n,LL s){
    if(p[s]==0)return 0;
    if(s==1)return n-1;
    LL ng=1e9+2;
    if(s>=5)ng=1e4;
    if(s>=10)ng=70;
    if(s>=20)ng=10;
    chmin(ng,n+1);
    LL ok=1;
    while(ng-ok>1){
        const LL m = (ok+ng)/2;
        LL x=safe_pow(m,s);

        if(x>0&&x<=n){
            ok=m;
        }
        else {
            ng=m;
        }
    }
    return ok-1;
}
int main() {
    for(int i:range(1,70)){
        LL &k=p[i];
        bool t=false;
        for(int s:range(2,70)){
            if(i%(s*s)==0)t=true;
            while(i%s==0){
                k++;
                i/=s;
            }
        }
        if(t)k=0;
        else
        if(k%2==0)k=1;
        else k=-1;
    }
    int T;
    scanf("%d",&T);
    while(T--){
        LL n;
        scanf("%lld",&n);
        LL ret=0;
        for(int i:range(1,62)){
            LL v=p[i];
            LL u=num(n,i);
            ret+=v*u;
        }
        printf("%lld\n",ret);
    }

    return 0;
}