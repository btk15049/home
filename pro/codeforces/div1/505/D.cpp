//http://codeforces.com/contest/1025/problem/D
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
bool lm[704][704];
bool rm[704][704];
using B=bitset<704>;
B dp[704][704];
B uni[704];
LL gcd(LL a,LL b){
    return (b==0)?a:gcd(b,a%b);
}
LL a[712];
int main(){
    int n;
    cin>>n;
    for(int i:range(n))cin>>a[i];
    for(int i:range(n))for(int j:range(n)){
        if(gcd(a[i],a[j])>1)uni[i][j]=true;
    }
    for(int i:range(n))lm[i][i+1]=rm[i][i+1]=dp[i][i+1][i]=true;
    for(int len:range(2,n+1)){
        for(int i:range(n))if(i+len<=n){
            lm[i][i+len] = (uni[i] & dp[i+1][i+len]).any();
            rm[i][i+len] = (uni[i+len-1] & dp[i][i+len-1]).any();
            for(int j:range(i,i+len)){
                dp[i][i+len][j]=rm[i][j+1]&lm[j][i+len];
            }
        }
    }
    if(dp[0][n].any())cout<<"Yes"<<endl;
    else cout<<"No"<<endl;
    return 0;
}