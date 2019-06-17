//https://atcoder.jp/contests/dp/tasks/dp_i
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


int main(){
    int N;
    cin>>N;
    vector<double> dp(N+1);
    dp[0]=1;
    for(int i:range(N)){
        vector<double> nxt(N+1);

        double p;
        cin>>p;
        for(int j:range(i+1)){
            nxt[j+1]+=dp[j]*p;
            nxt[j]+=dp[j]*(1-p);
        }
        swap(dp,nxt);
    }
    double ret=0;
    for(int i:range(N/2+1,N+1))ret+=dp[i];
    cout<<fixed;
    cout<<setprecision(10);
    cout<<ret<<endl;
    return 0;
}