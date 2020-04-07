//http://codeforces.com/contest/1027/problem/B
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
    LL n;
    int q;
    cin>>n>>q;
    while(q--){
        int r,c;
        cin>>r>>c;
        r--;c--;
        LL ret = 0;
        if((r+c)%2==1)ret+=(n*n+1)/2;
        if(n%2==0){
            ret+=(n/2)*r;
            ret+=c/2;
        }
        else{
            ret+=n*(r/2);
            if(r%2==1&&(r+c)%2==0)ret+=(n+1)/2;
            if(r%2==1&&(r+c)%2==1)ret+=(n)/2;
            ret+=c/2;
        }
        cout<<ret+1<<endl;
    }
    return 0;
}