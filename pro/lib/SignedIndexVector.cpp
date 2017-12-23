#include <bits/stdc++.h>
template <typename T> class svector:private std::vector<T>{
    using V=std::vector<T>;
    using SV=svector;
private:
    int sz;
public:
    using V::begin;
    using V::end;
    svector(int n,T ini):V(n*2+1,ini),sz(n){}
    svector(int n):SV(n,T()){}
    svector():V(),sz(0){}
    int size(){return sz;}
    T& operator[](int id){
        //assert(abs(id)<=sz);
        return V::operator[](id+sz);
    }
    SV& copy(const SV &other){
        V::operator=(other);
        sz=other.sz;
        return (*this);
    }
    SV& operator=(const SV& other){
        return copy(other);
    }
};
