#include<bits/stdc++.h>
using namespace std;
typedef long long LL;

#define CIN_ONLY if(1)
struct cww{cww(){
    CIN_ONLY{
        ios::sync_with_stdio(false);cin.tie(0);
    }
}}star;
#define fin "\n"
#define FOR(i,bg,ed) for(int i=(bg);i<(ed);i++)
#define REP(i,n) FOR(i,0,n)
#define ALL(v) (v).begin(),(v).end()
#define fi first
#define se second
#define pb push_back
#define DEBUG if(0)
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
int main(){
    int n,m;
    cin>>n>>m;
    
    V x(4*m,0);
    V y(4*m,0);
    V a(n);
    cin>>a;
    LL sum=0;
    REP(i,n)a[i]--;
    REP(i,n-1){
        int l=a[i];
        int r=a[i+1];
        if(r<l)r+=m;
        sum+=r-l;
        x[l+1]++;
        x[r+1]--;
        y[l+1]+=l;
        y[r+1]-=l;
        l+=m;
        r+=m;
        x[l+1]++;
        x[r+1]--;
        y[l+1]+=l;
        y[r+1]-=l;
    }
    REP(i,4*m-1){
        x[i+1]+=x[i];
        y[i+1]+=y[i];
    }
    LL res=sum;
    FOR(i,m,2*m){
        LL cnt=x[i];
        LL st=y[i];
        cout<<i-m<<" "<<sum-(i-1)*cnt+st<<endl;
        chmin(res,sum-(i-1)*cnt+st);

    }
    cout<<res<<endl;
    return 0;
}
