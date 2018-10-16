//http://codeforces.com/contest/1066/problem/E
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

LL A[212345];
LL B[212345];
constexpr int mod = 998244353;
int main() {
    int n,m;
    cin>>n>>m;
    string a,b;
    cin>>a>>b;
    int len = max(n,m);
    int la = len-n,lb = len-m;
    for(int i:range(la,len))A[i]=a[i-la]-'0';
    for(int i:range(lb,len))B[i]=b[i-lb]-'0';
    for(int i:range(1,len))B[i]+=B[i-1];
    for(int i:range(len))A[i]=(A[i]*B[i])%mod;
    LL ret = 0;
    LL po = 1;
    reverse(A,A+len);
    for(int i:range(len)){
        ret+=A[i]*po%mod;
        po=po*2%mod;
    }
    cout<<ret%mod<<endl;
    return 0;
}
