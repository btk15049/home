//http://codeforces.com/contest/1029/problem/F
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

LL all[1123456];
int S = 0;
LL A[1123456];
LL B[1123456];
int solve(LL a,LL b){
    int M = 0;
    int AA=0,BB=0;
    LL area = a;
    for(LL x=1;x*x<=area;x++){
        if(area%x==0){
            A[AA++]=x;
            if(x*x!=area)B[BB++]=area/x;
        }
    }
    while(BB>0){
        A[AA++]=B[--BB];
    }
    int j = 0;
    for(int i:range(S)){
        while(j+1<AA&&A[j+1]<=all[i])j++;
        if(a/A[j]<=(a+b)/all[i]){
            LL pv = all[M]+(a+b)/all[M];
            LL nv = all[i]+(a+b)/all[i];
            if(pv>nv){
                M=i;
            }
        }
    }
    return M;
}
int main(){
    LL a,b;
    cin>>a>>b;
    LL ret = 0;
    LL area = a+b;
    int BB=0;
    for(LL x=1;x*x<=area;x++){
        if(area%x==0){
            all[S++]=x;
            if(x*x!=area)B[BB++]=area/x;
        }
    }
    while(BB>0){
        all[S++]=B[--BB];
    }
    auto p = solve(a,b);
    auto q = solve(b,a);

    int M = max(p,q);
    cout<<all[M]*2+((a+b)/all[M])*2<<endl;
    return 0;
}