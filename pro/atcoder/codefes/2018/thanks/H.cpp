//https://beta.atcoder.jp/contests/code-thanks-festival-2018-open/tasks/code_thanks_festival_2018_h
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

int N;
LL a[1123];
LL as[1123];
bool vis[2][1123];
LL dp[2][1123];
LL threshold;
inline LL sum(int i,int j){
    return as[j]-as[i];
}
inline LL cost(int i,int j){
    return sum(i,j)>=threshold?1:-1;
}
void g(int turn,int k){
    if(vis[turn][k])return;
    vis[turn][k]=true;
    if(k==N){
        dp[turn][k]=0;
        return;
    }
    if(turn==0){
        LL &ret=dp[turn][k];
        ret=-1e15;
        for(int l:range(k+1,N+1)){
            g(1-turn,l);
            chmax(ret,cost(k,l)+dp[1-turn][l]);
        }
    }
    else{
        LL &ret=dp[turn][k];
        ret=1e15;
        for(int l:range(k+1,N+1)){
            g(1-turn,l);
            chmin(ret,cost(k,l)+dp[1-turn][l]);
        }
    }
}
bool f(){
    for(int i:range(2))for(int j:range(1123))vis[i][j]=false;
    g(0,0);
    return dp[0][0]>=0;
}
int main(){
    cin>>N;
    for(int i:range(N)){
        cin>>a[i];
        as[i+1]=as[i]+a[i];
    }
    LL ng=1e13;
    LL ok=-1e13;
    while(ng-ok>1){
        //cout<<ng<<" "<<ok<<endl;
        threshold=(ok+ng)/2;
        if(f())ok=threshold;
        else ng=threshold;
    }
    cout<<ok<<endl;
    return 0;
}