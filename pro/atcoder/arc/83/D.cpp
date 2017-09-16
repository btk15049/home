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
#include<dvector.h>
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
typedef pair<int,int> P;
typedef vector<LL> V;
typedef vector<V> VV;
int main(){
    int N;
    cin>>N;
    VV A(N,V(N));
    cin>>A;
    VV d(N,V(N,1e15));
    REP(i,N)d[i][i]=0;
    vector<pair<LL,P>> e;
    
    REP(i,N)REP(j,i)e.pb({A[i][j],{i,j}});
    sort(ALL(e));
    cout<<
        [&](){
        LL ret=0;
        for(auto &it:e){
            int a=it.se.fi;
            int b=it.se.se;
            if(d[a][b]>A[a][b]){
                ret+=it.fi;
                d[a][b]=d[b][a]=it.fi;
                DEBUG cout<<" "<<it.fi<<endl;
                REP(i,N)REP(j,N)
                    chmin(d[i][j],d[i][a]+d[a][b]+d[b][j]);
                REP(i,N)REP(j,N)
                    chmin(d[i][j],d[i][b]+d[a][b]+d[a][j]);
                REP(i,N)REP(j,N)if(d[i][j]<A[i][j])return -1ll;
            }
        }
        REP(i,N)REP(j,N)if(d[i][j]!=A[i][j])return -1ll;
        return ret;
    }() <<endl;
    return 0;
}
