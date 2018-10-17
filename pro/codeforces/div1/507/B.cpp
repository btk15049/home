//http://codeforces.com/contest/1039/problem/B
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#ifdef BTK
#define DEBUG if(1)
#else
#define CIN_ONLY if(0)
struct cww {cww() {CIN_ONLY{ios::sync_with_stdio(false); cin.tie(0);}}}star;
#define DEBUG if(0)
#endif
#define ALL(v) (v).begin(),(v).end()
#define REC(ret, ...) std::function<ret (__VA_ARGS__)>
template <typename T>inline bool chmin(T &l, T r){bool a = l>r; if (a)l = r; return a;}
template <typename T>inline bool chmax(T &l, T r){bool a = l<r; if (a)l = r; return a;}
template <typename T>istream& operator>>(istream &is, vector<T> &v){for (auto &it : v)is >> it;return is;}
class range {private: struct I { int x; int operator*() { return x; }bool operator!=(I& lhs) { return x<lhs.x; }void operator++() { ++x; } }; I i, n;public:range(int n) :i({ 0 }), n({ n }) {}range(int i, int n) :i({ i }), n({ n }) {}I& begin() { return i; }I& end() { return n; }};

namespace xorshift{
    unsigned yy=1145141919;
    inline unsigned rand(){yy=yy^(yy<<13);yy=yy^(yy>>17);return yy=yy^(yy<<5);}
    constexpr int MASK  = 65535;
    inline int randInt(){return (int) (rand()&MASK);}
    inline double randDouble(){return (rand()&MASK) /(double)MASK;}
}
int q=0;
bool query(LL l,LL r){
    q++;if(q>4500)exit(-1);
    cout<<l+1<<" "<<r<<endl;cout.flush();
    string ret;
    cin>>ret;
    if(ret=="Yes"){
        return true;
    }
    else{
        return false;
    }
}
int main(){
    LL n,k;
    cin>>n>>k;
    LL lb = 0;
    LL ub = n;
    while(1){
        if(ub-lb<=45){
            int r = xorshift::randInt()%(ub-lb);
            if(query(lb+r,lb+r+1))return 0;
            else {
                lb=max(lb-k,0ll);
                ub=min(ub+k,n);
            }
        }
        else{
            const LL mid = (lb+ub)/2;
            //lb+((ub-lb)/4)*(xorshift::randInt()%3+1);
            if(query(lb,mid)){
                lb=max(lb-k,0ll);
                ub=min(mid+k,n);
            }
            else{
                lb=max(mid-k,0ll);
                ub=min(ub+k,n);
            }
        }
    }
    return 0;
}