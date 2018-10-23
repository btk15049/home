//http://codeforces.com/contest/1029/problem/C
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


struct seg{LL l,r;};
seg f(seg l,seg r){
    return seg{max(l.l,r.l),min(l.r,r.r)};
}
seg s[312345];
seg t[312345];
const LL INF = 1e10;
int main(){
    int n;
    cin>>n;
    s[0]=t[n+1]=seg{-INF,INF};
    for(int i:range(n)){
        LL a,b;
        cin>>a>>b;
        s[i+1]=t[i+1]=seg{a,b};
    }
    for(int i=0;i<n;i++)s[i+1]=f(s[i],s[i+1]);
    for(int i=n;i>0;i--)t[i]=f(t[i],t[i+1]);
    LL ret = 0;
    for(int i:range(1,n+1)){
        //cout<<s[i-1].l<<s[i-1].r<<endl;
        auto p = f(s[i-1],t[i+1]);
        chmax(ret,p.r-p.l);
    }
    cout<<ret<<endl;
    return 0;
}