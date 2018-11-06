//https://beta.atcoder.jp/contests/abc113/tasks/abc113_b
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

int h[11234];
int main(){
    int n,t,a;
    cin>>n>>t>>a;
    a*=1000;
    t*=1000;
    int ret = 0;
    for(int i:range(n)){
        cin>>h[i];
    }
    for(int i:range(n)){
        int x = t-h[ret]*6;
        int y = t-h[i]*6;
        if(abs(x-a)>abs(y-a)){
            ret=i;
        }
    }
    cout<<ret+1<<endl;
    return 0;
}