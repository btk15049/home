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
    
int main(){
    int H,W,N,M;
    cin>>H>>W>>N>>M;
    vector<int> x={0,H};
    vector<int> y={0,W};
    REP(i,N){
        int t;cin>>t;x.pb(t);
    }
    REP(i,M){
        int t;cin>>t;y.pb(t);
    }
    sort(ALL(x));
    sort(ALL(y));
    LL ret=0;
    map<int,LL> X,Y;
    REP(i,N+1)X[x[i+1]-x[i]]++;
    REP(i,M+1)Y[y[i+1]-y[i]]++;
    for(auto &it:X){
        ret+=it.se*Y[it.fi];
    }
    cout<<ret<<endl;
    return 0;
}
