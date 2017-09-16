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
    
int main(){
    int A,B,C,D,E,F;
    cin>>A>>B>>C>>D>>E>>F;
    vector<int> w(40,0);
    vector<int> s(4000,0);
    w[0]=1;
    s[0]=1;
    FOR(i,A,40)w[i]|=w[i-A];
    FOR(i,B,40)w[i]|=w[i-B];
    FOR(i,C,4000)s[i]|=s[i-C];
    FOR(i,D,4000)s[i]|=s[i-D];
    int a=A,b=0;
    FOR(aa,1,40)REP(bb,4000)if(w[aa]&&s[bb]){
        if(bb>E*aa)continue;
        if(aa*100+bb>F)continue;
        if((a*100+b)*bb>(aa*100+bb)*b){
            a=aa;
            b=bb;
        }
    }
    cout<<a*100+b<<" "<<b<<endl;
    
    
    return 0;
}
