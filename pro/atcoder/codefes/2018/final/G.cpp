//https://beta.atcoder.jp/contests/code-festival-2018-final/tasks/code_festival_2018_final_g
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

LL dp[2123][2123];
constexpr LL INF =1e17;
int N,M;
LL A[2123];
LL B[2123];
int main(){
    for(int i:range(2123))for(int j:range(2123))dp[i][j]=INF;
    dp[0][0]=0;
    cin>>N>>M;
    for(int i:range(N))cin>>A[i];
    sort(A,A+N);
    for(int i:range(N))B[i+1]=A[i]+B[i];
    for(int i:range(M)){
        for(int j:range(N)){
            int k=0;
            while(k<j&&dp[i][k]+(B[j+1]-B[k])*(j+1-k)>=dp[i][k+1]+(B[j+1]-B[k+1])*(j+1-k-1))k++;
            dp[i+1][j+1]=dp[i][k]+(B[j+1]-B[k])*(j+1-k);
        }
    }
    cout<<dp[M][N]<<endl;
    return 0;
}