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
int n;
int a[11234];
int b[11234];
int c[2123];
int lx[2123];
int rx[2123];
typedef pair<int,int> P;
int LeftRight(int g){
    int ret=1145141919;
    set<P> ri;
    set<P> li;
    int rest=0;
    REP(i,n){
        c[i]=(a[i]!=b[g+i]);
        if(c[i])
            rest++;
    }
    DEBUG cout<<rest<<endl;
    const int need=rest;
    {
        int left_most_near=0;
        REP(i,n)if(b[i]==1)left_most_near=i;
        FOR(i,n,n+n){
            if(b[i]==1)left_most_near=i;
            if(c[i-n]==1){
                lx[i-n]=i-left_most_near;
                li.insert({lx[i-n],i-n});
            }
        }
    }
    {
        int right_most_near=2*n;
        for(int i=2*n-1;i>=n;i--)
            if(b[i]==1)right_most_near=i;
        for(int i=n-1;i>=0;i--){
            if(b[i]==1)right_most_near=i;
            if(c[i]==1){
                rx[i]=right_most_near-i;
                ri.insert({rx[i],i});
            }
        }
    }
    if(rest==0)return min(n-g,g);
    REP(s,n){
        while(rest>0&&(*li.begin()).fi==s){
            rest--;
            const int delete_id=(*li.begin()).se;
            li.erase(li.begin());
            ri.erase({rx[delete_id],delete_id});
        }
        int goal_pos;
        if(rest>0){
            auto it=ri.end();
            it--;
            goal_pos=(*it).fi;
        }
        else
            goal_pos=-s;
        const int dx1=goal_pos+s;
        const int dx2=min({
                abs(g-goal_pos),
                    abs(n+g-goal_pos),
                    abs(g+n+n-goal_pos),
                    abs(g-n-goal_pos)
                              });
        chmin(ret,s+dx1+dx2);
    }
    DEBUG cout<<"Left:"<<g<<" "<<ret+need<<endl;
    
    return ret+need;
}
int RightLeft(int g){
    int ret=1145141919;
    set<P> ri;
    set<P> li;
    int rest=0;
    REP(i,n){
        c[i]=(a[i]!=b[g+i]);
        if(c[i])
            rest++;
    }
    DEBUG cout<<rest<<endl;
    const int need=rest;
    {
        int left_most_near=0;
        REP(i,n)if(b[i]==1)left_most_near=i;
        FOR(i,n,n+n){
            if(b[i]==1)left_most_near=i;
            if(c[i-n]==1){
                lx[i-n]=i-left_most_near;
                li.insert({lx[i-n],i-n});
            }
        }
    }
    {
        int right_most_near=2*n;
        for(int i=2*n-1;i>=n;i--)
            if(b[i]==1)right_most_near=i;
        for(int i=n-1;i>=0;i--){
            if(b[i]==1)right_most_near=i;
            if(c[i]==1){
                rx[i]=right_most_near-i;
                ri.insert({rx[i],i});
            }
        }
    }
    if(rest==0)return min(n-g,g);
    REP(s,n){
        while(rest>0&&(*ri.begin()).fi==s){
            rest--;
            const int delete_id=(*ri.begin()).se;
            ri.erase(ri.begin());
            li.erase({lx[delete_id],delete_id});
        }
        int goal_pos;
        if(rest>0){
            auto it=li.end();
            it--;
            goal_pos=-(*it).fi;
        }
        else
            goal_pos=s;
        const int dx1=s-goal_pos;
        const int dx2=min({
                abs(g-goal_pos),
                    abs(n+g-goal_pos),
                    abs(g-n-n-goal_pos),
                    abs(g-n-goal_pos)
                              });
        chmin(ret,s+dx1+dx2);
    }
    DEBUG cout<<"Right:"<<g<<" "<<ret+need<<endl;
    
    return ret+need;
}

int main(){
    int ret=1145141919;
    string A,B;
    cin>>A>>B;
    n=A.size();
    REP(i,n)a[i]=a[i+n]=a[i+2*n]=a[i+3*n]=A[i]-'0';
    REP(i,n)b[i]=b[i+n]=b[i+2*n]=b[i+3*n]=B[i]-'0';
    int one=0;
    REP(i,n)chmax(one,b[i]);
    if(one!=1){
        REP(i,n)chmax(one,a[i]);
        cout<<-one<<endl;
        return 0;
        
    }
    REP(i,n){
        chmin(ret,LeftRight(i));

        chmin(ret,RightLeft(i));
    }
    cout<<ret<<endl;
    return 0;
}
