//
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
class range {private: struct I { int x; int operator*() { return x; }bool operator!=(I& lhs) { return x<lhs.x; }void operator++() { ++x; } }; I i, n;public:range(int n) :i({ 0 }), n({ n }) {}range(int i, int n) :i({ i }), n({ n }) {}I& begin() { return i; }I& end() { return n; }reverse_range operator!(){return reverse_range(*i,*n);}};

int N;
int mod;

struct ModInt{
    int x;
    LL operator*()const{
        return x;
    }
    //constructor
    ModInt(){
        x=0;
    }
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
inline ModInt inv(const ModInt x){
    LL a = *x, b = mod, u = 1, v = 0;
    while (b) {
        LL t = a / b;
        swap(a -= t * b, b);
        swap(u -= t * v, v);
    }
    return ModInt::raw((u % mod + mod) % mod);
}
inline ModInt operator-(const ModInt x){
    return add(mod, -*x);
}
inline ModInt operator+(const ModInt l,const ModInt r){
    return add(l,r);
}
inline ModInt operator*(const ModInt l,const ModInt r){
    return mul(l,r);
}
inline ModInt operator-(const ModInt l,const ModInt r){
    return add(l,-r);
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
inline ModInt operator-(const ModInt l,const int r){
    return add(l,ModInt::raw(mod-r));
}
inline ModInt operator-(const ModInt l,const LL r){
    return add(l,-ModInt::get(r));
}
inline ModInt operator/(const ModInt l,const int r){
    return mul(l,inv(ModInt::raw(r)));
}
inline ModInt operator/(const ModInt l,const LL r){
    return mul(l,inv(ModInt::get(r)));
}

inline ModInt pow(ModInt a, LL x){
    ModInt ret=1;
    while(x){
        if(x&1){
            ret=ret*a;
        }
        a=a*a;
        x>>=1;
    }
    return ret;
}

inline ModInt operator^(const ModInt l,const LL r){
    return pow(l,r);
}


namespace factorial{
    constexpr int size = 1123456;
    ModInt factorial[size];
    ModInt inverse_factorial[size];
    bool is_build = false;
    void build(){
        is_build = true;
        factorial[0]=1;
        for(int i:range(1,size)){
            factorial[i]=factorial[i-1]*i;
        }
        inverse_factorial[size-1]=inv(factorial[size-1]);
        for(int i:!range(1,size)){
            inverse_factorial[i-1]=inverse_factorial[i]*i;
        }
    }
    inline ModInt permutation(int n,int k){
        if(k<0 || k>n) return ModInt::raw(0);
        if(!is_build)build();
        return factorial[n]*inverse_factorial[n-k];
    }
    inline ModInt combination(int n, int k){
        if(k<0 || k>n) return ModInt::raw(0);
        if(!is_build)build();
        return factorial[n]*inverse_factorial[k]*inverse_factorial[n-k];
    }
}

ModInt bi[2123*2123];
ModInt ci[2123][2123];
ModInt calc(const int R){
    const int B=(N-R);
    vector<ModInt> Rs(2),Bs(2);
    for(int r:range(R)){
        Rs[r%2]=Rs[r%2]+factorial::combination(R,r)*ci[R-r][B];
    }
    return (Rs[0]-Rs[1])*bi[R*(R-1)/2+B*(B-1)/2];
}
int main(){
    cin>>N>>mod;
    bi[0]=1;
    for(int i:range(1,2123*2123)){
        bi[i]=bi[i-1]*2;
    }
    for(int r:range(1,2123)){
        ci[r][0]=1;
        for(int c:range(1,2123)){
            ci[r][c]=ci[r][c-1]*(bi[r]-1);
        }
    }
    ModInt ret=0;
    for(int i:range(1,N)){
        ret=ret+factorial::combination(N,i)*calc(i);
    }
    cout << *ret << endl;
    return 0;
}