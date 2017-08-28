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

const double eps=1e-8;
int main(){
    LL D,L;
    cin>>D>>L;
    int N;
    cin>>N;
    vector<LL> d(N+2);
    d[N]=0;
    d[N+1]=D;
    REP(i,N){
        cin>>d[i];
    }
    sort(ALL(d));
    double ret=0;
    REP(i,N+1)if(d[i+1]-d[i]>L){
        double k=d[i+1]-d[i]-L;
        k/=2;
        ret+=k*k/D;
    }
    cout<<fixed;
    cout<<setprecision(7);
    cout<<ret+eps<<endl;
    return 0;
}
