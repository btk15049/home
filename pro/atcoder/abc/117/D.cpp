//https://atcoder.jp/contests/abc117/tasks/abc117_d
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
class reverse_range {private:struct I {int x;int operator*() {return x-1;}bool operator!=(I& lhs) {return x>lhs.x;}void operator++() {--x;}};I i, n;public:reverse_range(int n) :i({ 0 }), n({ n }){}reverse_range(int i, int n) :i({ i }), n({ n }){}I& begin() {return n;}I& end() {return i;}};
class range {private: struct I { int x; int operator*() { return x; }bool operator!=(I& lhs) { return x<lhs.x; }void operator++() { ++x; } }; I i, n;public:range(int n) :i({ 0 }), n({ n }) {}range(int i, int n) :i({ i }), n({ n }) {}I& begin() { return i; }I& end() { return n; }reverse_range operator!(){return reverse_range(*i,*n);}};

bool vis[64][2];
LL dp[64][2];
LL s[64];
LL t[112345][64];
int N;
LL K;

void ch(LL x,LL y[64]){
    bitset<64> b(x);
    for(int i:range(64)){
        y[i]=b[i]?1:0;
    }
}

void dfs(int n,int r){
    if(vis[n][r])return;
    vis[n][r]=true;
    LL& ret=dp[n][r];
    ret=0;
    if(n==0)return;
    n--;
    dfs(n,0);
    dfs(n,1);
    int p=1;
    if(r==0&&s[n]==0){
        p=0;
    }
    for(int i:range(p)){
        LL c=0;
        for(int j:range(N)){
            c+=(i^t[j][n])<<n;
        }
        chmax(ret,c+dp[n][1]);
    }
    for(int i:range(p,p+1)){
        LL c=0;
        for(int j:range(N)){
            c+=(i^t[j][n])<<n;
        }
        chmax(ret,c+dp[n][r]);
    }
}
int main(){
    cin>>N>>K;
    ch(K,s);
    for(int i:range(N)){
        LL a;
        cin>>a;
        ch(a,t[i]);
    }
    dfs(63,0);
    cout<<dp[63][0]<<endl;
    return 0;
}