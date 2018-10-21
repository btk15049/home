//http://codeforces.com/contest/1015/problem/F
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

constexpr int mod = 1e9+7;
using V = vector<LL>;
using VV = vector<V>;
int link[300][2];
LL dp[300][300];
LL nx[300][300];
int main(){
    int n;
    cin>>n;
    string s;
    cin>>s;int m =s.size();
    dp[0][0]=1;
    for(int i:range(m)){
        for(int j:range(i+1)){
            string t=s.substr(j,i-j);
            string p=s.substr(0,i-j+1);
            string x=t+"(";
            string y=t+")";
            if(x==p)chmax(link[i][0],i-j+1);
            if(y==p)chmax(link[i][1],i-j+1);
        }
    }
    for(int i:range(2*n)){
        for(int a:range(300))for(int b:range(300))nx[a][b]=0;

        for(int con:range(m+1)){
            for(int dep:range(2*n+1)){
                dp[con][dep]%=mod;
                if(dp[con][dep]==0)continue;
                if(con==m){
                    nx[con][dep+1]+=dp[con][dep];
                    if(dep>0)nx[con][dep-1]+=dp[con][dep];
                }
                else{
                    int op = link[con][0];
                    int cl = link[con][1];
                    nx[op][dep+1]+=dp[con][dep];
                    if(dep>0)nx[cl][dep-1]+=dp[con][dep];
                }
            }
        }
        DEBUG {
            int tmp=1;
        }
        for(int a:range(300))for(int b:range(300))dp[a][b]=nx[a][b];
    }
    cout<<dp[m][0]%mod<<endl;
    return 0;
}