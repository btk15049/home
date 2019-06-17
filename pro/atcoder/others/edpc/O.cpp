//https://atcoder.jp/contests/dp/tasks/dp_o
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

int a[21][21];
LL dp[1<<21];
constexpr int mod =1e9+7;
int main(){
    int N;
    cin>>N;
    dp[0]=1;
    for(int i:range(N))for(int j:range(N))cin>>a[i][j];
    for(int b:range(1<<N)){
        bitset<21> bit(b);
        dp[b]%=mod;
        int i = __builtin_popcount(b);
        for(int j:range(N)){
            if(bit[j]==false&&a[i][j]){
                dp[b|(1<<j)]+=dp[b];
            }
        }
    }
    cout<<dp[(1<<N)-1]<<endl;
    return 0;
}