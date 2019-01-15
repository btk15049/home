//https://beta.atcoder.jp/contests/dwacon5th-prelims/tasks/dwacon5th_prelims_b
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

int N,K;
LL a[1123];
LL as[1123];
LL b[1123456];
int M=0;
int f(LL bit){
    int ret=0;
    for(int i:range(M)){
        if((b[i]&bit)==bit)ret++;
    }
    return ret;
}
int main(){
    cin>>N>>K;
    for(int i:range(N)){
        cin>>a[i];
        as[i+1]=a[i]+as[i];
    }
    for(int i:range(N)){
        for(int j:range(i+1,N+1)){
            b[M++]=as[j]-as[i];
            //cout<<b[M-1]<<endl;
        }
    }
    LL ret=0;
    for(int i=60;i>=0;i--){
        LL tes=(1ll<<i);
        if(f(ret|tes)>=K)ret|=tes;
    }
    cout<<ret<<endl;
    return 0;
}