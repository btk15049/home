//https://atcoder.jp/contests/dp/tasks/dp_h
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

int R,C;
LL dp[1123][1123];
constexpr int mod = 1e9+7;
int main(){
    cin>>R>>C;
    dp[0][0]=1;
    for(int i:range(R)){
        string s;
        cin>>s;
        for(int j:range(C)){
            if(s[j]=='#')dp[i][j]=0;
            else{
                (dp[i+1][j]+=dp[i][j])%=mod;
                (dp[i][j+1]+=dp[i][j])%=mod;
            }
        }
    }
    cout<<dp[R-1][C-1]<<endl;
    return 0;
}