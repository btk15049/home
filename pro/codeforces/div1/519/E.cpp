//http://codeforces.com/contest/1043/problem/E
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

int n,m;
using V=vector<int>;
V g[312345];
LL a[312345];
LL b[312345];
LL Dab[312345];
LL Dba[312345];
LL s[312345];
LL t[312345];
int main(){
    scanf("%d%d",&n,&m);
    LL as=0,bs=0;
    for(int i:range(n)){
        scanf("%lld%lld",a+i,b+i);
        Dab[i]=b[i]-a[i];
        s[i]=Dba[i]=a[i]-b[i];
        as+=a[i];
        bs+=b[i];
    }
    sort(s,s+n);
    for(int i:range(n))t[i+1]=t[i]+s[i];
    for(int i:range(m)){
        int u,v;
        scanf("%d%d",&u,&v);
        u--;v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for(int i:range(n))g[i].push_back(i);
    string sp(n,' ');sp.back()='\n';
    for(int i:range(n)){
        LL ret = bs+n*a[i];
        //printf("(%lld)",ret);

        int ok=-1,ng=n;
        while(ng-ok>1){
            const int mid = (ok+ng)/2;
            if(Dab[i]+s[mid]<0)ok=mid;
            else ng =mid;
        }
        ret+=ng*Dab[i];
        ret+=t[ng];
        //printf("%d(%lld)",ng,ret);
        for(int j:g[i]){
            if(Dab[i]+Dba[j]<0){
                ret-=b[i];
                ret-=a[j];
            }
            else{
                ret-=a[i];
                ret-=b[j];
            }
        }
        printf("%lld%c",ret,sp[i]);
    }
    return 0;
}