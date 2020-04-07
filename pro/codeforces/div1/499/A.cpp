//http://codeforces.com/contest/1010/problem/A
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

double a[1123];
double b[1123];
void upd(double& s,double &t,double p){
    s=s-s/p;
    t=t-(t+1)/p;

}
int main() {
    int n;
    cin>>n;
    double w;
    cin>>w;
    double s=1;
    double t=0;
    double bot = 0;
    for(int i:range(n)){
        cin>>a[i]>>b[i];
        upd(s,t,a[i]);
        if(t<0&&s==0){cout<<-1<<endl;return 0;}
        if(t<0)chmax(bot,-w*t/s);
        upd(s,t,b[i]);
        if(t<0&&s==0){cout<<-1<<endl;return 0;}
        if(t<0)chmax(bot,-w*t/s);
        //cout<<s<<" "<<t<<endl;
    }
    cout<<fixed;
    cout<<setprecision(10);
    cout<<bot<<endl;
    return 0;
}
