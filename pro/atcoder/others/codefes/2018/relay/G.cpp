//https://atcoder.jp/contests/cf18-relay-open/tasks/relay2018_g
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
class reverse_range {private:struct I {int x;int operator*() {return x-1;}bool operator!=(I& lhs) {return x>lhs.x;}void operator++() {--x;}};I i, n;public:reverse_range(int n) :i({ 0 }), n({ n }){}reverse_range(int i, int n) :i({ i }), n({ n }){}I& begin() {return n;}I& end() {return i;}};
class range {private: struct I { int x; int operator*() { return x; }bool operator!=(I& lhs) { return x<lhs.x; }void operator++() { ++x; } }; I i, n;public:range(int n) :i({ 0 }), n({ n }) {}range(int i, int n) :i({ i }), n({ n }) {}I& begin() { return i; }I& end() { return n; }reverse_range operator!(){return reverse_range(*i,*n);}};

int N;
LL x[4123];
LL y[4123];
double r[4123];
double rr[4123];
int o[4123];
constexpr int mod = 1e9+7;
const double pi=acos(-1);
LL pow_mod(LL a,LL n,int M=mod){
    LL res=1;
    a%=M;
    while(n){
        if(n&1)
            res=(res*a)%M;
        a=(a*a)%M;
        n>>=1;
    }
    return res;
}
int main(){
    cin>>N;
    for(int i:range(N)){
        cin>>x[i]>>y[i];
        x[i]+=10000;
        y[i]+=10000;
    }
    LL ret=0;
    for(int i:range(N)){
        int k=0;
        for(int j:range(N)){
            if(i!=j){
                o[k++]=j;
                o[k++]=j+N;
                r[j]=atan2(x[j]-x[i],y[j]-y[i]);
                if(r[j]<0)r[j]+=2*pi;
                r[j+N]=r[j]+2*pi;
            }
        }
        sort(o,o+k,[&](int i,int j){return r[i]<r[j];});
        for(int j:range(k))rr[j]=r[o[j]];
        for(int j:range(k/2)){
            LL area = (-x[i]*y[o[j]]%mod+x[o[j]]*y[i]%mod+mod)%mod;
            int cnt = lower_bound(rr,rr+k,rr[j]+pi)-upper_bound(rr,rr+k,rr[j]);

            ret+=area*(pow_mod(2,cnt)+mod-1)%mod;
        }
    }
    cout<<ret%mod<<endl;
    return 0;
}

/*

    3
     12
    4
*/