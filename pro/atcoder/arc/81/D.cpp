//https://atcoder.jp/contests/arc081/tasks/arc081_b
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
int main(){
    int N;
    string S,T;
    cin>>N>>S>>T;
    vector<int> v;
    for(int id=0;id<N;){
        if(S[id]==T[id]){
            v.push_back(1);
        }
        else{
            v.push_back(2);
        }
        id+=v.back();
    }
    vector<ModInt> dp(v.size());
    dp[0]=1;
    for(int i:range(1,v.size())){
        if(v[i-1]==1&&v[i]==2){
            dp[i]=dp[i-1];
        }
        else if(v[i-1]==2&&v[i]==2){
            dp[i]=dp[i-1]*3;
        }
        else{
            dp[i]=dp[i-1]*2;
        }
    }
    cout<<*(dp.back()*v.back()*3)<<endl;
    return 0;
}