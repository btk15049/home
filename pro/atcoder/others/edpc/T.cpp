//https://atcoder.jp/contests/dp/tasks/dp_t
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
string s;
using V=vector<LL>;
LL sum[3123];
LL dp[3123];
LL nxt[3123];
constexpr int mod = 1e9+7;
int main(){
    cin>>N>>s;
    for(int i:range(N))dp[i]=1;
    for(int i:range(1,N)){
        char c=s[i-1];
        for(int j:range(3123))sum[j]=nxt[j]=0;
        for(int j:range(3122))sum[j+1]=(sum[j]+dp[j])%mod;

        for(int j:range(N-i)){
            if(c=='<'){
                nxt[j]+=(sum[j+1]-sum[0]+mod);
            }
            else{
                nxt[j]+=(sum[3100]-sum[j+1]+mod);
            }
        }
        //cout<<sum[3100]<<":";
        /*
        12
        13
        23
        14
        24
        34
        132 2
        142 3
        231 2
        241 3
        341 3
        342 
        */
        
        for(int j:range(3123)){
            dp[j]=nxt[j]%mod;
            //cout<<dp[j]<<" ";
        }
        //cout<<endl;
    }
    cout<<dp[0]<<endl;
    return 0;
}