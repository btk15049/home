//https://beta.atcoder.jp/contests/code-festival-2018-final/tasks/code_festival_2018_final_b
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

double lf[112345];
double lc(int n,int r){
    return lf[n]-lf[r]-lf[n-r];
}
int main(){
    lf[0]=0;
    for(int i:range(1,112345)){
        lf[i]=log10(i)+lf[i-1];
    }
    int N,M;
    cin>>N>>M;
    if(M==1){
        cout<<0<<endl;
        return 0;
    }
    double lp=-log10(M)*N;
    for(int i:range(M)){
        int ri;cin>>ri;
        lp+=lc(N,ri);
        N-=ri;
    }
    LL ub=1e18;
    LL lb=0;
    while(ub-lb>1){
        const LL mid=(lb+ub)/2;
        if(-mid<=lp)ub=mid;else lb=mid;
    }
    //cout<<lp<<endl;
    cout<<ub<<endl;
    return 0;
}