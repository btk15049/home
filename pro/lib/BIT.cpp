#include <bits/stdc++.h>
namespace BIT_{
    using RET = int;
    constexpr int BUF = 1123456;
    int ptr = 0;
    RET t[BUF];
    inline RET* get(const int size){
        ptr+=size;
        return &(t[ptr-size]);
    }
}
//[1,n],0は扱えない!
struct BIT{
    using T=BIT_::RET;
    T* bit;
    int sz;
    BIT(int n):bit(BIT_::get(n+10)),sz(n){}
    T sum(int i){
        T s=0;
        while(i>0){
            s+=bit[i];
            i-=i&-i;
        }
        return s;
    }
    T sum(int lb,int ub){
        return sum(ub)-sum(lb-1);
    }
    void add(int i,T x){
        while(i<=sz){
            bit[i]+=x;i+=i&-i;
        }
    }
    //v[1]+v[2]+...+v[x]>=wとなる最小のxを求める
    int lowerbound(T w){
        if(w<=0)return 0;
        int x=0;
        for(int k = (1<<(31-__builtin_clz(sz)));k >0 ;k>>=1)
            if(x+k<=sz&&bit[x+k]<w){
                w-=bit[x+k];
                x+=k;
            }
        return x+1;
    }
};   
    
