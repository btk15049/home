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

#define Y se
#define X fi
int main(){
    map<int,vector<pair<pair<int,int>,int>>> p;
    int N,R,C;
    cin>>N>>C>>R;
    REP(i,N){
        int type,pos,t;
        cin>>type>>pos>>t;
        int x,y;
        if(type==2){
            y=pos;
            x=-t;
            type=-1;
        }
        else{
            x=pos;
            y=-t;
        }
        
        p[x+y].pb({{x,y},type*(1+i)});
    }
    vector<pair<int,int>> res(N);
    for(auto &it:p){
        vector<pair<int,int>> s;
        vector<pair<int,int>> t;
        for(auto& v:it.se){
            if(v.se<0){
                s.pb({-v.fi.Y,-v.se-1});
                t.pb({C,-v.fi.Y});
            }
            else{
                s.pb({v.fi.X,v.se-1});
                t.pb({v.fi.X,R});
            }
            
        }
        sort(ALL(s));
        sort(ALL(t));
        int M=s.size();
        REP(i,M)
            res[s[i].se]={t[i]};
    }    
    REP(i,N)
        cout<<res[i].X<<" "<<abs(res[i].Y)<<fin;
    
    return 0;
}
