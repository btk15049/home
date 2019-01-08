//https://atcoder.jp/contests/dp/tasks/dp_n
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
LL dp[412][412];
LL a[412];
LL as[412];
int main(){
    cin>>N;
    for(int i:range(N)){
        cin>>a[i];
        as[i+1]=a[i]+as[i];
    }
    for(int i:range(412))for(int j:range(412))dp[i][j]=1e17;
    for(int i:range(N))dp[i][i+1]=0;
    for(int len:range(1,N+1)){
        for(int i:range(N)){
            int j = i+len;
            if(j>N)continue;
            for(int k:range(i+1,j)){
                chmin(dp[i][j],dp[i][k]+dp[k][j]+as[j]-as[i]);
            }
        }
    }
    cout<<dp[0][N]<<endl;
    return 0;
}