//https://atcoder.jp/contests/dp/tasks/dp_x
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
int w[2123];
int s[2123];
LL v[2123];
LL dp[21234];
pair<int,int> a[2123];
int main(){
    cin>>N;
    for(int i:range(N)){
        cin>>w[i]>>s[i]>>v[i];
        a[i]={w[i]+s[i],i};
    }
    sort(a,a+N);
    for(int _i:range(N)){
        int i=a[_i].second;
        for(int j=w[i]+s[i];j>=w[i];j--){
            chmax(dp[j],dp[j-w[i]]+v[i]);
        }
    }
    cout<<*max_element(dp,dp+21234)<<endl;
    return 0;
}