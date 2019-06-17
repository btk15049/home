//https://beta.atcoder.jp/contests/code-festival-2018-final/tasks/code_festival_2018_final_c
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
int N,M;
LL A[112345];
LL B[112345];
LL C[112345];

LL latte[1123456];
int malta=0;
LL val[1123456];
constexpr LL INF =1e18;
int main(){
    cin>>N;
    for(int i:range(N)){
        cin>>A[i]>>B[i];
        latte[malta++]=A[i];
    }
    cin>>M;
    for(int i:range(M)){
        cin>>C[i];
        latte[malta++]=C[i];
    }
    latte[malta++]=0;
    sort(latte,latte+malta);
    malta=unique(latte,latte+malta)-latte;
    for(int i:range(1123456))val[i]=INF;
    for(int i:range(N)){
        const int pos = lower_bound(latte,latte+malta,A[i])-latte;
        chmin(val[pos],B[i]);
    }
    for(int ri:range(1123450)){
        const int i=1123450-ri;
        chmin(val[i-1],val[i]);
    }
    for(int i:range(malta-1)){
        chmin(val[i+1],val[i]+latte[i+1]-latte[i]);
    }
    for(int i:range(M)){
        const int pos = lower_bound(latte,latte+malta,C[i])-latte;
        cout<<val[pos]<<endl;
    }
    return 0;
}