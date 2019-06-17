//https://cf18-relay-e.contest.atcoder.jp/tasks/relay2018_j
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
LL A[3123],B[3123];
LL AtoL[3123][3123];
LL AtoR[3123][3123];
LL BtoL[3123][3123];
LL BtoR[3123][3123];
LL AS[3123];
LL BS[3123];

LL Asum(int lb,int ub){
    return AS[ub]-AS[lb];
}
LL Bsum(int lb,int ub){
    return BS[ub]-BS[lb];
}

LL dp[3123][3123];
constexpr LL INF  =1e17;
int main(){
    cin>>N;
    for(int i:range(N)){
        cin>>A[i]>>B[i];
    }
    for(int i:range(N)){
        AS[i+1]=A[i]+AS[i];
        BS[i+1]=B[i]+BS[i];
    }
    for(int i:range(N)){
        AtoR[i][i+1]=0;
        BtoR[i][i+1]=0;
        for(int j:range(i+1,N)){
            //[i,j)をjに移す
            AtoR[i][j+1]=AtoR[i][j]+Asum(i,j);
            BtoR[i][j+1]=BtoR[i][j]+Bsum(i,j);
        }
        AtoL[i][i+1]=0;
        BtoL[i][i+1]=0;
        for(int j=i-1;j>=0;j--){
            //[j+1,i+1)をjに移す
            AtoL[j][i+1]=AtoL[j+1][i+1]+Asum(j+1,i+1);
            BtoL[j][i+1]=BtoL[j+1][i+1]+Bsum(j+1,i+1);
        }
    }
    for(int i:range(3123))for(int j:range(3123))dp[i][j]=INF;
    dp[0][0]=0;


    for(int i:range(N))for(int j:range(N)){
        const int k = max(i,j)+1;
        if(i==0){
            chmin(dp[k][j],dp[i][j]+AtoR[0][k]);
        }else{
            chmin(dp[k][j],dp[i][j]+AtoL[i-1][(i+k)/2]+AtoR[(i+k)/2][k]);
        }
        if(j==0){
            chmin(dp[i][k],dp[i][j]+BtoR[j][k]);
        }
        else{
            chmin(dp[i][k],dp[i][j]+BtoL[j-1][(j+k)/2]+BtoR[(j+k)/2][k]);
        }
        //printf("dp[%d][%d]=%lld\n",i,j,dp[i][j]);
    }
    LL ret=INF;
    for(int i:range(1,N)){
        chmin(ret,dp[i][N]+AtoL[i-1][N]);
        chmin(ret,dp[N][i]+BtoL[i-1][N]);
        //printf("dp[%d][%d]=%lld\n",i,j,dp[i][N]);
        //printf("dp[%d][%d]=%lld\n",i,j,dp[N][i]);
    }
    cout<<ret<<endl;
    return 0;
}