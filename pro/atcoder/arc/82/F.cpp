#include<bits/stdc++.h>
using namespace std;
typedef long long LL;

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


typedef long long LL;
const LL INF=1e16;
typedef pair<LL,LL> A;
typedef LL B;
typedef LL C;
struct node{
    A a;
    int flag;
    B b;
    C c;
};
#define isB (1<<0)
#define isC (1<<1)
inline A mg(node& v,int l,int r){
    if(v.flag&isB)return {v.b+v.c,v.b+v.c};
    else return {v.a.fi+v.c,v.a.se+v.c};
}
inline A mg(A l,A r){
    return minmax({l.fi,l.se,r.fi,r.se});
}
LL in[2123456];
inline A f(int x){
    return {in[x],in[x]};
}
namespace ST{
    node mem[1][2123456];
    int cnt=0;
    node* get(){return mem[cnt++];}
}
struct seg_tree{
    int size;
    node *seg;
    void init(int l,int r,int k=0){
        auto &v=seg[k];
        //flagŠÖ˜A‚Ìˆ—
        v.flag=0;
        v.b=0;
        v.c=0;

        if(r-l==1){
            //—t‚ÌŽž‚Ìˆ—
            v.a=f(l);
        }
        else if(r-l>1){
            int m=(l+r)/2;
            init(l,m,k*2+1);init(m,r,k*2+2);
            v.a=mg(mg(seg[k*2+1],l,m),mg(seg[k*2+2],m,r));
        }
    }
    seg_tree(int n){
        size=1;
        while(size<n)size*=2;
        seg=ST::get();
        init(0,size);
    }
    inline void push(int k,int l,int r){
        if(r-l<=1)return;
        auto &v=seg[k];
        auto &lg=seg[2*k+1];
        auto &rg=seg[2*k+2];
        if(v.flag&isB){
            lg.flag=isB;lg.b=v.b;
            rg.flag=isB;rg.b=v.b;
            lg.c=0;
            rg.c=0;
        }
        if(v.flag&isC){
            lg.flag|=isC;lg.c+=v.c;
            rg.flag|=isC;rg.c+=v.c;
            v.c=0;
        }
        v.flag=0;
    }
#define LQ a,b,k*2+1,l,m
#define RQ a,b,k*2+2,m,r
    A get(int a,int b,int k,int l,int r){
        if(a<=l&&r<=b)return mg(seg[k],l,r);
        push(k,l,r);          
        int m=(l+r)/2;
        bool ll=!(m<=a||b<=l);
        bool rr=!(r<=a||b<=m);
        A ret;
        if(ll&&rr)ret=mg(get(LQ),get(RQ));
        else if(ll)ret=get(LQ);
        else ret=get(RQ);
        seg[k].a=mg(mg(seg[k*2+1],l,m),mg(seg[k*2+2],m,r));
        return ret;
    }
    A get(int a,int b){return get(a,b,0,0,size);}
    void update(int a,int b,int k,int l,int r,node v){
        if(r<=a||b<=l)return;
        if(a<=l&&r<=b){
            if(v.flag==isB){
                seg[k].flag=isB;
                seg[k].b=v.b;
                seg[k].c=0;
            }
            if(v.flag==isC){
                seg[k].flag|=isC;
                seg[k].c+=v.c;
            }
        }
        else{
            push(k,l,r);           
            int m=(l+r)/2;
            update(LQ,v);
            update(RQ,v);
            seg[k].a=mg(mg(seg[k*2+1],l,m),mg(seg[k*2+2],m,r));
        }
    }
    LL lb_min(int a,int b,int k,int l,int r,LL x){
        if(l==r)return INF;
        LL ret;
        auto now=mg(seg[k],l,r);
        if(now.se<x)return INF;
        if(now.fi>=x)return l;
        int m=(l+r)/2;
        push(k,l,r);
        ret=min(
                lb_min(LQ,x),
                lb_min(RQ,x)
                );
        seg[k].a=mg(mg(seg[k*2+1],l,m),mg(seg[k*2+2],m,r));
        return ret;
    }

    LL lb_max(int a,int b,int k,int l,int r,LL x){
        if(l==r)return -1;
        LL ret;
        auto now=mg(seg[k],l,r);
        if(now.fi>x)return -1;
        if(now.se<=x)return r;
        int m=(l+r)/2;
        push(k,l,r);
        ret=max(
                lb_max(LQ,x),
                lb_max(RQ,x)
                );
        seg[k].a=mg(mg(seg[k*2+1],l,m),mg(seg[k*2+2],m,r));
        return ret;
    }

    void set(int a,int b,B val){
        node q;
        q.flag=isB;q.b=val;
        update(a,b,0,0,size,q);
    }
    void add(int a,int b,C val){
        node q;
        q.flag=isC;q.c=val;
        update(a,b,0,0,size,q);
    }
};

pair<int,int> query[212345];
int main(){
    LL X;
    int K,Q;
    
    scanf("%lld %d",&X,&K);
    REP(i,K){
        scanf("%d",&(query[i].fi));
        query[i].se=-1;
    }
    scanf("%d",&Q);
    REP(i,Q){
        scanf("%d %d",&(query[K+i].fi),&(query[K+i].se));
        in[i]=query[K+i].se;
    }
    sort(query,query+K+Q);
    sort(in,in+Q);
    int N=K+Q;
    int M=unique(in,in+Q)-in;
    FOR(i,M,2123456)in[i]=X;
    REP(i,N)if(query[i].se>=0)
        query[i].se=lower_bound(in,in+M,query[i].se)-in;
    seg_tree db(M);
    M=db.size;
    int sgn=-1;
    LL prv=0;
    REP(i,N){
        DEBUG printf(" query:%d (%d,%lld(%d))\n",i,query[i].fi,query[i].se>=0?in[query[i].se]:-1,query[i].se);
        LL seg=query[i].fi-prv;
        //
        if(seg){
            if(sgn==1){
                LL b=db.lb_min(0,M,0,0,M,X-seg);
                chmin(b,(LL)M);
                DEBUG printf("  t=%lld(%lld),sgn=1,b=%lld\n",prv+seg,seg,b);
                db.set(b,M,X);
                db.add(0,b,seg);
            }
            else{
                LL b=db.lb_max(0,M,0,0,M,seg);
                chmax(b,0ll);
                DEBUG printf("  t=%lld(%lld),sgn=-1,b=%lld\n",seg,prv+seg,b);
                db.set(0,b,0);
                db.add(b,M,-seg);
            }
        }
        prv+=seg;
        if(query[i].se==-1){
            sgn*=-1;  
        }
        else{
            printf("%lld\n",db.get(query[i].se,query[i].se+1).fi);
        }
    }
    return 0;
}
