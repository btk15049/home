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
    LL Q,H,S,D,N;
    cin>>Q>>H>>S>>D>>N;
    N*=4;
    H=min({H,Q*2});
    S=min({S,H*2,Q*4});
    D=min({D,S*2,H*4,Q*8});
    LL ret=0;
    ret+=(N/8)*D;N-=(N/8)*8;
    ret+=(N/4)*S;N-=(N/4)*4;
    ret+=(N/2)*H;N-=(N/2)*2;
    ret+=(N/1)*Q;N-=(N/1)*1;
    cout<<ret<<endl;
    return 0;
}
