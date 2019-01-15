//https://atcoder.jp/contests/abc025/tasks/abc025_d
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

int A[25][25];
int R[26];
int C[26];
inline bool check(int bit,int r,int c){
    const int pos = r*5+c;
    if(c!=0&&c!=4){
        int side=0;
        side|=((bit>>(pos-1))&1);
        side|=(((bit>>(pos+1))&1)<<1);
        if(side==1||side==2)return false;
    }
    if(r!=0&&r!=4){
        int side=0;
        side|=(bit>>(pos-5))&1;
        side|=((bit>>(pos+5))&1)<<1;
        if(side==1||side==2)return false;
    }
    return true;
}
constexpr int mod = 1e9+7;
LL dp[1<<25];
int main(){
    for(int i:range(1,26))R[i]=-1;
    for(int i:range(5)){
        for(int j:range(5)){
            cin>>A[i][j];
            R[A[i][j]]=i;
            C[A[i][j]]=j;
        }
    }
    dp[0]=1;
    for(int b:range((1<<25)-1)){
        if(dp[b]==0)continue;
        dp[b]%=mod;
        const int num = __builtin_popcount(b)+1;
        if(R[num]==-1){
            for(int i:range(5)){
                for(int j:range(5)){
                    const int pos = (i*5+j);
                    if(A[i][j]==0&&(b&(1<<pos))==0&&check(b,i,j)){
                        dp[b|(1<<pos)]+=dp[b];
                    }
                }
            }
        }
        else{
            const int pos = (R[num]*5+C[num]);
            if(check(b,R[num],C[num])){
                dp[b|(1<<pos)]+=dp[b];
            }
        }
    }
    cout<<dp[(1<<25)-1]%mod<<endl;
    return 0;
}