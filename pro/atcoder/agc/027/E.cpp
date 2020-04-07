//https://beta.atcoder.jp/contests/agc027/tasks/agc027_e
#include<bits/stdc++.h>

using namespace std;
typedef long long LL;

#ifdef BTK
#define DEBUG if(1)
#else
#define CIN_ONLY if(1)
struct cww {cww() {CIN_ONLY{ios::sync_with_stdio(false); cin.tie(0);}}
}star;
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

LL dp[112345];
V li[3];
LL S[112345];
LL db[112345];
int main() {
    string s;
    cin>>s;
    const int n=s.size();
    for(int i:range(n)){
        S[i+1]=1;
        if(s[i]=='b')S[i+1]++;
        S[i+1]+=S[i];
        S[i+1]%=3;
        li[S[i+1]].push_back(i+1);
        if(i>0&&s[i-1]==s[i])db[i+1]++;
        db[i+1]+=db[i];
    }
    dp[0]=1;
    for(int i:range(n)){
        dp[i]%=mod;
        dp[i+1]+=dp[i];
        if(n-i>=2&&(3+S[n]-S[i])%3!=0&&db[n]-db[i+1]>=1){
            dp[n]+=dp[i];
        }
        int nx = ((s[i]=='a'?2:1)+S[i])%3;
        int ok = li[nx].size();ok--;
        int ng = -1;
        if(ok==-1||db[li[nx][ok]]<=db[i+1])continue;
        while(ok-ng>1){
            const int mid = (ng+ok)/2;
            int t = li[nx][mid];

            if(t-i>=2&&db[t]-db[i+1]>=1){
                ok=mid;
            }
            else{
             ng=mid;
            }
        }
        int p = li[nx][ok];
        if(p<n){
            dp[p]+=dp[i];
        }
    }
    cout<<dp[n]%mod<<endl;
    return 0;
}

