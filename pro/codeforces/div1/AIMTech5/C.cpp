//http://codeforces.com/contest/1028/problem/C
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

int a[142345];
int b[142345];
int c[142345];
int d[142345];
int lxb[142345];
int lxe[142345];
int lyb[142345];
int lye[142345];
int rxb[142345];
int rxe[142345];
int ryb[142345];
int rye[142345];
int main(){
    int n;
    cin>>n;
    for(int i:range(n)){
        cin>>a[i]>>c[i]>>b[i]>>d[i];
    }
    lxb[0]=lyb[0]=-1e9;
    lxe[0]=lye[0]=+1e9;
    rxb[n]=ryb[n]=-1e9;
    rxe[n]=rye[n]=+1e9;
    for(int i:range(n)){
        lxb[i+1] = max(lxb[i],a[i]);
        lyb[i+1] = max(lyb[i],c[i]);
        lxe[i+1] = min(lxe[i],b[i]);
        lye[i+1] = min(lye[i],d[i]);
    }
    for(int ri:range(n)){
        const int i = n-ri;
        rxb[i-1] = max(rxb[i],a[i-1]);
        ryb[i-1] = max(ryb[i],c[i-1]);
        rxe[i-1] = min(rxe[i],b[i-1]);
        rye[i-1] = min(rye[i],d[i-1]);
    }
    for(int i:range(n)){
        int xb = max(lxb[i],rxb[i+1]);
        int xe = min(lxe[i],rxe[i+1]);
        int yb = max(lyb[i],ryb[i+1]);
        int ye = min(lye[i],rye[i+1]);
        //cout<<lxb[i]<<" "<<lxe[i]<<endl;
        if(xb<=xe&&yb<=ye){
            cout<<xb<<" "<<yb<<endl;
            return 0;
        }
    }

    return 0;
}