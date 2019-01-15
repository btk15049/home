//https://atcoder.jp/contests/arc070/tasks/arc070_b
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

constexpr int mod=(int)1e9+7;
using V=vector<LL>;
inline void chadd(LL& a,const LL b){
    a+=b;
    if(a>=mod)a-=mod;
}

LL dp[5123];
LL pr[5123];
int main(){
    int N,K;
    cin>>N>>K;
    vector<int> A(N);
    cin>>A;
    int ret=N;
    dp[0]=1;
    for(int i:range(N)){
        const int a= min(A[i],K);
        for(int j=K-1;j>=a;j--){
            chadd(dp[j],dp[j-a]);
        }
    }
    //for(int i:range(K))cout<<dp[i]<<" ";cout<<endl;
    for(int i:range(N)){
        const int a= min(A[i],K);
        for(int j:range(K)){
            pr[j]=dp[j];
            if(j>=a)chadd(pr[j],mod-pr[j-a]);
        }
        for(int j:range(K-a,K)){
            if(pr[j]){
                ret--;break;
            }
        }
    }
    cout<<ret<<endl;
    return 0;
}