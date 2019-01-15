//https://atcoder.jp/contests/arc066/tasks/arc066_b
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
map<LL,LL> ret;
LL f(LL k){
    if(k==0)return 0;
    if(k==1)return 1;
    if(ret.count(k))return ret[k];
    if(k%2==1){
        return ret[k]=(f(k/2)*2%mod+f(k/2+1))%mod;
    }
    else{
        return ret[k]=(f(k/2)*2%mod+f(k/2-1))%mod;
    }
}
int main(){
    LL k;
    cin>>k;
    cout<<f(k+1)<<endl;
    return 0;
}
