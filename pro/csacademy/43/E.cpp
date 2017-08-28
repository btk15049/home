#include<bits/stdc++.h>
using namespace std;
typedef long long LL;

#define CIN_ONLY if(1)
struct cww{cww(){
    CIN_ONLY{
        ios::sync_with_stdio(false);cin.tie(0);
    }
}}star;
#ifdef BTK
#define DEBUG if(1)
#else
#define DEBUG if(0)
#endif

#define fin "\n"
#define FOR(i,bg,ed) for(int i=(bg);i<(ed);i++)
#define REP(i,n) FOR(i,0,n)
#define ALL(v) (v).begin(),(v).end()
#define fi first
#define se second
#define pb push_back
#define REC(ret, ...) std::function<ret (__VA_ARGS__)>
template <typename T>inline bool chmin(T &l,T r)
{bool a=l>r;if(a)l=r;return a;}
template <typename T>inline bool chmax(T &l,T r)
{bool a=l<r;if(a)l=r;return a;}
template <typename T>
istream& operator>>(istream &is,vector<T> &v){
    for(auto &it:v)is>>it;
    return is;
}

typedef vector<LL> V;
V prime;
constexpr int X=1000000;
struct latte{
    latte(){
        V p(X,1);
        p[0]=p[1]=0;
        REP(i,X)if(p[i]){
            prime.pb(i);
            for(int j=i;j<X;j+=i)
                p[j]=false;
        }
    }
}malta;


int main(){
    LL N,K;
    cin>>N>>K;
    int id=2;
    int p=N-1;
    V ret;
    while(K>=p&&p>=0){
        K-=p;
        ret.pb(prime[id]);
        id++;
        p--;
    }
    if(K>=0){
        ret.pb(2);
        REP(i,K)ret.pb(3*prime[id++]);
    }
    while(ret.size()<N)ret.pb(6*prime[id++]);
    REP(i,N)cout<<" "+(!i)<<ret[i];
    cout<<endl;
    return 0;
}
