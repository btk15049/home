//http://codeforces.com/contest/1038/problem/D
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

int main() {
    int n;
    cin>>n;
    vector<LL> a(n);
    cin>>a;
    if(n==1){
        cout<<a[0]<<endl;
        return 0;
    }
    sort(ALL(a));
    LL sum = 0;
    LL ret = -1e18;
    for(int i:range(n))sum+=a[i];
    LL tum = 0;
    for(int i:range(n-1)){
        tum+=a[i];
        chmax(ret,sum-tum-tum);
    }
    cout<<ret<<endl;
    return 0;
}

