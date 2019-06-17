//https://beta.atcoder.jp/contests/code-thanks-festival-2018-open/tasks/code_thanks_festival_2018_e
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

int T;
int a[700];
using V=vector<LL>;
using VV=vector<V>;
constexpr int mod = 1e9+7;
int main(){
    cin>>T;
    for(int i:range(T))cin>>a[i];
    V dp(612,0);
    dp[0]=1;
    LL ret=0;
    for(int i:range(600)){
        V nxt(612,0);
        for(int j:range(612))if(j%2==0){
            for(int k:range(a[i]+1)){
                nxt[j/2+k]+=dp[j];
            }
        }
        for(auto &it:nxt)it%=mod;
        ret+=nxt[1];
        swap(dp,nxt);
    }
    cout<<ret%mod<<endl;
    return 0;
}