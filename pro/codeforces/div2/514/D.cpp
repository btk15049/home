#include<bits/stdc++.h>

using namespace std;
typedef long long LL;

#ifdef BTK
#define DEBUG if(1)
#else
#define CIN_ONLY if(1)
struct cww {cww() {CIN_ONLY{ios::sync_with_stdio(false); cin.tie(0);}}
}star;
#define DEBUG if(0)
#endif

#define ALL(v) (v).begin(),(v).end()
#define REC(ret, ...) std::function<ret (__VA_ARGS__)>
template <typename T>inline bool chmin(T &l, T r){bool a = l>r; if (a)l = r; return a;}
template <typename T>inline bool chmax(T &l, T r){bool a = l<r; if (a)l = r; return a;}
template <typename T>istream& operator>>(istream &is, vector<T> &v){for (auto &it : v)is >> it;return is;}

class range {private: struct I { int x; int operator*() { return x; }bool operator!=(I& lhs) { return x<lhs.x; }void operator++() { ++x; } }; I i, n;public:range(int n) :i({ 0 }), n({ n }) {}range(int i, int n) :i({ i }), n({ n }) {}I& begin() { return i; }I& end() { return n; }};

int n;
using D = long double;
constexpr D EPS = 1e-20;
D x[112345];
D y[112345];
using F = __float128;
F abs(F a){
    if(a<0)return -a;
    else return a;
}
F sqrt(F a){
    F ng = a+1.0;
    F ok=0;
    for(int _:range(100)){
        F m = (ok+ng)/2.0;
        if(m*m<=a)ok=m;
        else ng=m;
    }
    DEBUG cout<<(double)a<<" "<<(double)ok<<endl;
    return ok;
}
int main() {
    cout<<fixed<<setprecision(20);
    cin>>n;
    for(int i:range(n)){
        double a,b;
        cin>>a>>b;
        x[i]=a;
        y[i]=b;
    }
    D top=0,bot=0;
    for(int i:range(n)){
        chmax(top,y[i]);
        chmin(bot,y[i]);
    }
    if(top*bot<0){
        cout<<-1<<endl;return 0;
    }
    if(top<EPS){
        for(int i:range(n))y[i]*=-1;
    }
    
    D ok=1e16;
    D ng =0;
    for(int _:range(100)){
        const D mid = (ok+ng)/2.0;
        const D r = mid/2.0;
        D lb = -1e30;
        D ub = 1e30;
        for(int i:range(n)){
            const D h = abs(r-y[i]);
            const D w = sqrtl(r*r-h*h);
            if(y[i]>mid)ub=-1e18,lb=1e18;
            chmax(lb,x[i]-w);
            chmin(ub,x[i]+w);
            DEBUG cout<<(double)h<<" "<<(double)w<<endl;
        }
        DEBUG cout<<(double)mid<<" "<<(double)lb<<" "<<(double)ub<<endl;
        if(ub-lb>-EPS)ok=mid;
        else ng=mid;
    }
    cout<<(double)ok/2.0<<endl;

    return 0;
}
