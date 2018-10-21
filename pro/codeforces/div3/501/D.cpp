//http://codeforces.com/contest/1015/problem/D
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
    LL n,k,s;
    cin>>n>>k>>s;
    if(s<k||k*(n-1)<s){
        cout<<"NO"<<endl;
    }
    else{
        cout<<"YES"<<endl;
        LL d = s-k;
        vector<LL> ret(k);
        LL p = 1;
        for(int i:range(k)){
            LL x=min(n-2,d);
            LL mv = x+1;
            if(p+mv<=n){
                ret[i]=p+mv;
            }
            else{
                ret[i]=p-mv;
            }
            p=ret[i];
            d-=x;
        }

        string sp(ret.size(),' ');
        sp.back()='\n';
        for(int i:range(ret.size()))cout<<ret[i]<<sp[i];
    }
    return 0;
}