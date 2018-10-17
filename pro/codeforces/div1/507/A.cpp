//http://codeforces.com/contest/1039/problem/A
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
LL a[212345];
LL x[212345];
LL b[212345];

int main(){
    int n;
    LL t;
    cin>>n>>t;
    for(int i:range(n))cin>>a[i];
    for(int i:range(n))cin>>x[i];
    for(int i:range(1,n))if(x[i-1]>x[i]){cout<<"No"<<endl;return 0;}
    for(int i:range(0,n))if(x[i]-1<i){cout<<"No"<<endl;return 0;}
    for(int i:range(0,n))if(upper_bound(x,x+n,x[i])-x!=x[i]){cout<<"No"<<endl;return 0;}
    for(int i:range(n+1))b[i]=3e18;
    for(int i:range(n)){
        int pos = lower_bound(x,x+n,x[i])-x;
        chmin(b[pos],a[i]+t-1);
    }
    for(int ri:range(n)){
        const int i=n-1-ri;
        chmin(b[i],b[i+1]-1);
    }
    for(int i:range(n)){
        int u = upper_bound(x,x+n,x[i])-x;
        int l = lower_bound(x,x+n,x[i])-x;
        if(u-l>1&&l!=i){
            if(b[i]<a[i]+t){cout<<"No"<<endl;DEBUG ; else return 0;}
        }
        else {
            if(b[i+1]<a[i]+t){cout<<"No"<<endl;DEBUG ; else return 0;}
        }
    }

    cout<<"Yes"<<endl;
    string sp(n+1,' ');sp.back()='\n';
    for(int i:range(1,n+1)){
        cout<<b[i]<<sp[i];
    }
    return 0;
}