//https://atcoder.jp/contests/dp/tasks/dp_l
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

LL dp[3233][3123];
bool vis[3123][3123];
LL a[3123];
LL solve(int l,int r,int p){
    if(r<l)return 0;
    if(vis[l][r])return dp[l][r];
    vis[l][r]=true;
    if(p==0){
        dp[l][r]=solve(l+1,r,1-p)+a[l];
        chmax(dp[l][r],solve(l,r-1,1-p)+a[r]);
    }
    else{
        dp[l][r]=solve(l+1,r,1-p)-a[l];
        chmin(dp[l][r],solve(l,r-1,1-p)-a[r]);
    }
    return dp[l][r];
}
int main(){
    int N;
    cin>>N;
    for(int i:range(N))cin>>a[i];
    cout<<solve(0,N-1,0)<<endl;
    return 0;
}