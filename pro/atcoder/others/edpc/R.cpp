//https://atcoder.jp/contests/dp/tasks/dp_r
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

typedef LL D;
#define REP4(i,n) for(int i=0;i<n;i+=4)

constexpr int S = 64;
struct M{
    D v[S][S];
    D& operator()(int i,int j){
        return v[i][j];
    }
}mat[64];
constexpr int mod = 1e9+7;
void mat_mul(M &a,M& b,M &c){
    for(int i:range(S))for(int j:range(S))c(i,j)=0;
    D sum[4],tmp;
    for(int k:range(S)){
        REP4(i,S){
            sum[0]=a(i,k);
            sum[1]=a(i+1,k);
            sum[2]=a(i+2,k);
            sum[3]=a(i+3,k);
            for(int j:range(S)){
                tmp=b(k,j);
                c(i,j)+=sum[0]*tmp%mod;
                c(i+1,j)+=sum[1]*tmp%mod;
                c(i+2,j)+=sum[2]*tmp%mod;
                c(i+3,j)+=sum[3]*tmp%mod;
            }
        }
    }
    for(int i:range(S)){
        for(int j:range(S))c(i,j)%=mod;
    }
}

int main(){
    int N;
    cin>>N;
    LL K;
    cin>>K;
    for(int i:range(N)){
        for(int j:range(N)){
            cin>>mat[0](i,j);
        }
    }
    for(int i:range(62))mat_mul(mat[i],mat[i],mat[i+1]);
    vector<LL> dp(N,1);
    for(int i:range(62)){
        if(K&1){
            vector<LL> nxt(N,0);
            for(int a:range(N))for(int b:range(N)){
                nxt[b]+=dp[a]*mat[i](a,b)%mod;
            }
            for(int a:range(N))nxt[a]%=mod;
            swap(dp,nxt);
        }
        K>>=1;
    }
    LL ret=0;
    for(int i:range(N))ret+=dp[i];
    cout<<ret%mod<<endl;
    return 0;
}