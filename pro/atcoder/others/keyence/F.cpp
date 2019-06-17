//https://atcoder.jp/contests/keyence2019/tasks/keyence2019_f
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#ifdef BTK
#define DEBUG if(1)
#else
#define CIN_ONLY if(1)
struct cww {cww() {CIN_ONLY{ios::sync_with_stdio(false); cin.tie(0);}}}star;
#define DEBUG if(0)
#endif
#define ALL(v) (v).begin(),(v).end()
#define REC(ret, ...) std::function<ret (__VA_ARGS__)>
template <typename T>inline bool chmin(T &l, T r){bool a = l>r; if (a)l = r; return a;}
template <typename T>inline bool chmax(T &l, T r){bool a = l<r; if (a)l = r; return a;}
template <typename T>istream& operator>>(istream &is, vector<T> &v){for (auto &it : v)is >> it;return is;}
class reverse_range {private:struct I {int x;int operator*() {return x-1;}bool operator!=(I& lhs) {return x>lhs.x;}void operator++() {--x;}};I i, n;public:reverse_range(int n) :i({ 0 }), n({ n }){}reverse_range(int i, int n) :i({ i }), n({ n }){}I& begin() {return n;}I& end() {return i;}};
class range {private: struct I {int x;int operator*() {return x;}bool operator!=(I& lhs) {return x<lhs.x;}void operator++() {++x;}};I i, n;public:range(int n) :i({ 0 }), n({ n }){}range(int i, int n) :i({ i }), n({ n }){}I& begin() {return i;}I& end() {return n;}reverse_range operator!(){return reverse_range(*i,*n);}};

constexpr int mod = 1e9+7;
struct ModInt{
    int x;
    LL operator*()const{
        return x;
    }
    ModInt(){}
    ModInt(const int y){
        x=y;
    }
    ModInt(const LL y){
        x=(int)(y%mod);
    }

    static inline ModInt raw(const LL x){
        assert(x<mod);
        return ModInt((int)x);
    }
    static inline ModInt get(const LL x){
        return ModInt((int)(x%mod));
    }
    ModInt& operator=(const int o){
        this->x=o;
        return *this;
    }
    ModInt& operator=(const LL o){
        this->x=(int)(o%mod);
        return *this;
    }
};
inline ModInt mul(const ModInt l,const ModInt r){
    return ModInt::raw(*l**r%mod);
}
inline ModInt add(const ModInt l,const ModInt r){
    LL x = *l+*r;
    return ModInt::raw(x>=mod?x-mod:x);
}
inline ModInt operator+(const ModInt l,const ModInt r){
    return add(l,r);
}
inline ModInt operator*(const ModInt l,const ModInt r){
    return mul(l,r);
}
inline ModInt operator+(const ModInt l,const int r){
    return add(l,ModInt::raw(r));
}
inline ModInt operator+(const ModInt l,const LL r){
    return add(l,ModInt::get(r));
}
inline ModInt operator*(const ModInt l,const int r){
    return mul(l,ModInt::raw(r));
}
inline ModInt operator*(const ModInt l,const LL r){
    return mul(l,ModInt::get(r));
}

// a^(-1) mod m
// O(log a)
inline LL invMod(LL a, int m=mod){
  LL b = m, u = 1, v = 0;
  while (b) {
    LL t = a / b;
    swap(a -= t * b, b);
    swap(u -= t * v, v);
  }
  return (u % m + m) % m;
}

inline ModInt inv(const ModInt x){
    return ModInt::raw(invMod(*x));
}

inline ModInt operator/(const ModInt l,const ModInt r){
    return mul(l,inv(r));
}

LL fact(int n){
    LL ret=1;
    for(int i=2;i<=n;i++){
        ret=ret*i%mod;
    }
    return ret;
}
ModInt Fact(int n){
    return ModInt::raw(fact(n));
}

ModInt d[111][111];
int main(){
    int R,C,K;
    cin>>R>>C>>K;
    ModInt all = Fact(R+C)/Fact(R+C-K);
    ModInt ret = 0;
    ModInt sp = inv(ModInt::raw(R+C));
    ModInt sq = inv(ModInt::raw(R+C-1));
    for(int t:range(2,K+1)){
        ModInt score = K+1-t;
        ModInt p1 = ModInt::raw(t-1)*sq;
        ModInt p2 = sp;
        ret=ret+score*p1*p2*2*R*C*all;
    }
    for(int t:range(1,K+1)){
        ModInt score = K+1-t;
        ModInt p = sp;
        ret=ret+score*p*(R+C)*all;
    }
    ret=ret+all*K;
    cout<<*ret<<endl;
    return 0;
}