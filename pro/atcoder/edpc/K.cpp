//https://atcoder.jp/contests/dp/tasks/dp_k
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

int dp[112345][2];
int a[1123];
int main(){
    int N,K;
    cin>>N>>K;
    for(int i:range(N)){
        cin>>a[i];
    }
    for(int k:range(K+1)){
        for(int p:range(2)){
            for(int i:range(N)){
                if(k>=a[i]&&dp[k-a[i]][1-p]==0){
                    dp[k][p]=1;
                }
            }
        }
    }
    if(dp[K][0])cout<<"First"<<endl;
    else cout<<"Second"<<endl;
    return 0;
}