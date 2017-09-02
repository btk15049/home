#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL INF=1e16;
typedef LL A;
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
A mg(node& v,int l,int r){
    if(v.flag&isB)return v.b+v.c;
    else return v.a+v.c;
}
A mg(A l,A r){
    return max(l,r);
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
        //flag関連の処理
        v.flag=0;
        v.b=-INF;
        v.c=0;

        if(r-l==1){
            //葉の時の処理
            v.a=-INF;
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
            lg.flag=isB;lg.b=v.b;lg.c=0;
            rg.flag=isB;rg.b=v.b;rg.c=0;
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
