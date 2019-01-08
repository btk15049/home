//https://atcoder.jp/contests/dp/tasks/dp_s
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

string s;
vector<int> S;
int D;
constexpr int mod=1e9+7;
bool vis[11234][2];
LL dp[11234][2][112];
void calc(int i,int ver){
    if(vis[i][ver])return;
    vis[i][ver]=true;
    if(i==S.size()){
        dp[i][ver][0]=1;
        return;
    }

    int p = ver?9:S[i];
    calc(i+1,0);
    calc(i+1,1);
    for(int x:range(D)){
        for(int y:range(p)){
            dp[i][ver][(x+y)%D]+=dp[i+1][1][x];
        }
    }
    for(int x:range(D)){
        for(int y:range(p,p+1)){
            dp[i][ver][(x+y)%D]+=dp[i+1][ver][x];
        }
    }
    for(int x:range(D)){
        dp[i][ver][x]%=mod;
        //cout<<i<<" "<<ver<<" "<<x<<" "<<dp[i][ver][x]<<endl;
    }

}
void latte(){
    for(int i:range(11234)){
        vis[i][0]=vis[i][1]=false;
        for(int j:range(112))dp[i][0][j]=dp[i][1][j]=0;
    }
}
int main(){
    cin>>s>>D;
    S.resize(s.size());
    for(int i:range(s.size()))S[i]=s[i]-'0';
    LL ret=0;
    latte();
    calc(0,0);
    ret+=dp[0][0][0];
    int p=s.size()-1;
    /*
    while(S[p]==0){
        S[p]=9;
        p--;
    }
    S[p]--;
    latte();
    calc(0,0);
    ret+=mod-dp[0][0][0];
    */
    cout<<(ret+mod-1)%mod<<endl;
    return 0;
}