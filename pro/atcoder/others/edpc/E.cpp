//https://atcoder.jp/contests/dp/tasks/dp_e
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


int main(){
    int N,W;
    cin>>N>>W;
    int X=N*1000+10;
    using V=vector<LL>;
    V dp(X,1e10);
    dp[0]=0;
    for(int i:range(N)){
        V nxt=dp;
        int w,v;
        cin>>w>>v;
        for(int j:range(v,X+1)){
            chmin(nxt[j],dp[j-v]+w);
        }
        swap(dp,nxt);
    }
    int ret=0;
    for(int i:range(X)){
        if(dp[i]<=W)chmax(ret,i);
    }
    cout<<ret<<endl;
    return 0;
}