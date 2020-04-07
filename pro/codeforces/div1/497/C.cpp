//http://codeforces.com/contest/1007/problem/C
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

int query(LL x,LL y){
    cout<<x<<" "<<y<<endl;
    fflush(stdout);
    int ret;
    cin>>ret;
    return ret;
}
int main(){
    LL n;
    cin>>n;
    LL x_lb=0,y_lb=0;
    LL x_ub=n+1,y_ub=n+1;
    while(1){
        {
            int ans = query(x_lb+1,y_lb+1);
            if(ans==1)x_lb++;
            if(ans==2)y_lb++;
            if(ans==0)return 0;
        }
        while(1){
        LL xm = (x_lb+x_ub)/2;
        LL ym = (y_lb+y_ub)/2;
        if(xm==x_lb)xm++;
        if(ym==y_lb)ym++;
        int ans=query(xm,ym);
        if(ans==1){
            x_ub = n+1;
            x_lb = xm;
            break;
        }
        if(ans==2){
            y_ub = n+1;
            y_lb = ym;
            break;
        }
        if(ans==3){
            x_ub=xm;
            y_ub=ym;
        }
        if(ans==0)return 0;
        }
    }
    return 0;
}