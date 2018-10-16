//http://codeforces.com/contest/1063/problem/C
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

void solve(int n,LL &x, LL y){
    LL lb = 0;
    LL ub = 2e8;
    for(int i:range(n)){
        const int mid = (lb+ub)/2;
        cout<<mid<<" "<<y<<endl;fflush(stdout);
        string s;
        cin>>s;
        if(s[0]=='b'){
            lb = mid;
        }
        else ub = mid;
    }
    x=(lb+ub)/2;
}
int main() {
    int n;
    cin>>n;
    if(n<=20){
        LL x;
        solve(n,x,0);
        cout<<x<<" "<<0<<" ";fflush(stdout);
        cout<<x<<" "<<1<<endl;fflush(stdout);
    }
    else{
        LL a=n/2;
        LL b=n-a;
        LL c,d;
        const LL inf =1e8;
        solve(a,c,inf);
        solve(b,d,0);
        cout<<c<<" "<<inf<<" ";fflush(stdout);
        cout<<d<<" "<<0<<endl;fflush(stdout);

    }
    return 0;
}
