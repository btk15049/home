//http://codeforces.com/contest/1060/problem/C
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
constexpr LL INF=1e10;

int main() {
    int r,c;
    cin>>r>>c;
    vector<LL> a(r);
    vector<LL> b(c);
    vector<LL> A(r+1,INF);
    vector<LL> B(c+1,INF);
    A[0]=B[0]=0;
    cin>>a>>b;
    LL x;
    cin>>x;
    for(int i:range(r)){
        LL sum=0;
        for(int j:range(i,r)){
            sum+=a[j];
            chmin(A[j-i+1],sum);
        }
    }
    for(int i:range(c)){
        LL sum=0;
        for(int j:range(i,c)){
            sum+=b[j];
            chmin(B[j-i+1],sum);
        }
    }
    int ret=0;
    for(int i:range(r+1)){
        for(int j:range(c+1)){
            if(A[i]==INF&&B[j]==INF)continue;
            if(A[i]*B[j]>x)continue;
            chmax(ret,i*j);
        }
    }
    cout<<ret<<endl;
    return 0;
}
