//http://codeforces.com/contest/1076/problem/F
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

int n,k;
int x[312345];
int y[312345];
int main(){
    scanf("%d%d",&n,&k);
    for(int i:range(n))scanf("%d",x+i);
    for(int i:range(n))scanf("%d",y+i);
    LL A=0;
    LL B=0;
    for(int i:range(n)){
        LL a=x[i];
        LL b=y[i];
        LL nA=k+1;
        LL nB=k+1;
        if(A<=k){
            //A||BABABA
            LL len = min(a,b);
            LL capa = (k-A)+k*(len-1);
            LL capb = k*len;
            if(b<=capb){
                chmin(nA,max(1ll,a-capa));
            }
        }
        if(B<=k){
            //B||ABABAB
            LL len = min(a,b);
            LL capb = (k-B)+k*(len-1);
            LL capa = k*len;
            if(a<=capa){
                chmin(nB,max(1ll,b-capb));
            }
        }
        if(A<=k){
            //A||BABAB
            LL len = min(a,b-1);
            LL capa = (k-A)+k*len;
            LL capb = k*len;
            if(a<=capa){
                chmin(nB,max(1ll,b-capb));
            }
        }
        if(B<=k){
            //B||ABABA
            LL len = min(a-1,b);
            LL capb = (k-B)+k*len;
            LL capa = k*len;
            if(b<=capb){
                chmin(nA,max(1ll,a-capa));
            }
        }
        swap(A,nA);
        swap(B,nB);
        //printf("%lld %lld\n",A,B);
    }
    if(A<=k||B<=k)printf("YES\n");
    else printf("NO\n");

    return 0;
}