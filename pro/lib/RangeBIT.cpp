#include<bits/stdc++.h>
using namespace std;
namespace BIT_{
    using RET = int;
    constexpr int BUF = 1123456;
    int ptr = 0;
    RET t[BUF];
    inline RET* get(const int size){
        ptr+=size;
        return t+ptr-size;
    }
}

struct BIT{
    using T=BIT_::RET;
    T* bit;
    int sz;
    BIT(int n):bit(BIT_::get(n+10)),sz(n){
        fill(bit,bit+n+10,0);
    }
    void add(int r,T v){//add v for [1,r]
        for(;r;r-=r&-r)bit[r]+=v;
    }
    void add(int l,int r,T v){//add v for [l,r]
        add(r,v);
        add(l-1,-v);
    }
    T get(int i){//get sum[i]
        T res=0;
        for(;i<=sz;i+=i&-i)res+=bit[i];
        return res;
    }
};
