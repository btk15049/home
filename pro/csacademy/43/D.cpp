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

typedef vector<int> V;
typedef vector<V> VV;
typedef pair<int,int> P;
int main(){
    int N,M;
    cin>>N>>M;
    set<P> s;
    VV g(N+1);
    REP(i,M){
        int a,b;
        cin>>a>>b;
        g[a].pb(b);
        g[b].pb(a);
        s.insert(minmax(a,b));
    }
    FOR(i,1,N+1){
        if(g[i].size()>=3){
            int a=g[i][0];
            int b=g[i][1];
            int c=g[i][2];
            if(s.count(minmax(a,b))){
                cout<<i<<" "<<a<<" "<<b<<endl;
                return 0;
            }
            if(s.count(minmax(b,c))){
                cout<<i<<" "<<b<<" "<<c<<endl;
                return 0;
            }
            if(s.count(minmax(c,a))){
                cout<<i<<" "<<c<<" "<<a<<endl;
                return 0;
            }
            cout<<a<<" "<<b<<" "<<c<<endl;
            return 0;
        }
    }
    if(N%3!=0||M==N-1){
        cout<<-1<<endl;
        return 0;
    }
    else{
        int s=1;
        int t=g[s][0];
        vector<int> path;
        path.pb(s);
        path.pb(t);
        REP(i,N-2){
            if(g[t][0]==s)
                path.pb(g[t][1]);
            else
                path.pb(g[t][0]);
            s=t;
            t=path.back();
        }
        cout<<path[0]<<" "<<path[N/3]<<" "<<path[2*N/3]<<endl;
    }
    return 0;
}
