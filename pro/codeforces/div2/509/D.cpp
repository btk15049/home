//http://codeforces.com/contest/1041/problem/D
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
    LL h;
    cin>>h;
    vector<LL> x1(n+1),x2(n+1);
    for(int i:range(n)){
        cin>>x1[i]>>x2[i];
    }
    int ub=0;
    LL di = x2[ub]-x1[ub];
    LL pr = di;
    LL ret=0;
    for(int i:range(n)){
        while(ub<n-1&&di-pr-(x2[ub+1]-x1[ub+1])+(x2[ub+1]-x2[ub])<h){
            pr+=x2[ub+1]-x1[ub+1];
            di+=x2[ub+1]-x2[ub];
            ub++;
        }
        LL nh = h-(di-pr);
        chmax(ret,di+nh);
        //cout<<nh<<endl;
        pr-=x2[i]-x1[i];
        di-=x1[i+1]-x1[i];
    }
    cout<<ret<<endl;
    return 0;
}
