//https://beta.atcoder.jp/contests/abc113/tasks/abc113_d
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
using V=vector<LL>;
int main(){
    int r,c,k;
    cin>>r>>c>>k;
    V dp(c,0);
    dp[0]=1;
    if(c==1){
        cout<<1<<endl;return 0;
    }
    vector<bitset<8>> B;
    for(int bit:range(1<<(c-1))){
        bitset<8> b(bit);
        bool ok = true;
        for(int i:range(c-2)){
            if(b[i]&&b[i+1])ok=false;
        }
        if(ok){
            B.push_back(b);
            //cout<<bit<<endl;
        }
    }

    for(int i:range(r)){
        V nxt(c,0);
        for(int now:range(c)){
            dp[now]%=mod;
            for(auto &b:B){
                if(now>0&&b[now-1]){
                    nxt[now-1]+=dp[now];
                }
                else if(now<c-1&&b[now]){
                    nxt[now+1]+=dp[now];
                }
                else{
                    nxt[now]+=dp[now];
                }
            }
        }
        swap(dp,nxt);
    }
    cout<<dp[k-1]%mod<<endl;
    return 0;
}