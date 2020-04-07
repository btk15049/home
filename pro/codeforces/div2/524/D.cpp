//http://codeforces.com/contest/1080/problem/D
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
LL n,k;
LL ff[70];
constexpr LL INF = 1e18;
LL f(LL m){
    if(m>=70)return k;
    else return min(ff[m],k);
}
LL mulmul(LL a,LL b){
    LL ret=0;
    while(b){
        if(b&1){
            ret+=a;
        }
        if(ret>INF)return INF;
        a*=2;
        if(a>INF)a=INF;
        b/=2;
    }
    return ret;
}
int main(){
    ff[0]=0;
    for(int i:range(69)){
        ff[i+1]+=mulmul(ff[i],4)+1;
        if(ff[i+1]>=INF)ff[i+1]=INF;
        //cout<<ff[i+1]<<" ";
    }
    int t;
    cin>>t;
    while(t--){
        cin>>n>>k;
        LL x=3;
        LL z=n-1;
        LL lb=1;
        LL ub=lb+f(z);
        cout<<x<<" ";cout<<z<<" ";cout<<lb<<" ";cout<<ub<<endl;

        while(z>=1&&ub<k){
            z--;
            ub+=mulmul(f(z),mulmul(x,2)-1);
            lb+=x;
            ub+=x;
            x=mulmul(x,2)+1;
            cout<<x<<" ";cout<<z<<" ";cout<<lb<<" ";cout<<ub<<endl;
        }
        if(lb<=k&&k<=ub){
            cout<<"YES "<<z<<endl;
        }
        else{
            cout<<"NO"<<endl;
        }
    }
    return 0;
}