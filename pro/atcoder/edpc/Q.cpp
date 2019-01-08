//https://atcoder.jp/contests/dp/tasks/dp_q
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
class range {private: struct I { int x; int operator*() { return x; }bool operator!=(I& lhs) { return x<lhs.x; }void operator++() { ++x; } }; I i, n;public:range(int n) :i({ 0 }), n({ n }) {}range(int i, int n) :i({ i }), n({ n }) {}I& begin() { return i; }I& end() { return n; }};

int N;
int h[212345];
LL a[212345];
namespace BIT_{
    using RET = LL;
    constexpr int BUF = 1123456;
    int ptr = 0;
    RET t[BUF];
    inline RET* get(const int size){
        ptr+=size;
        return t+ptr-size;
    }
}
//[1,n],0は扱えない!
struct BIT{
    using T=BIT_::RET;
    T* bit;
    int sz;
    BIT(int n):bit(BIT_::get(n+10)),sz(n){
        fill(bit,bit+n+10,0);
    }
    T sum(int i){
        T s=0;
        while(i>0){
            chmax(s,bit[i]);
            i-=i&-i;
        }
        return s;
    }
    void add(int i,T x){
        while(i<=sz){
            chmax(bit[i],x);
            i+=i&-i;
        }
    }
};

int main(){
    cin>>N;
    for(int i:range(N))cin>>h[i];
    for(int i:range(N))cin>>a[i];
    BIT bit(N+10);
    for(int i:range(N)){
        LL ans = bit.sum(h[i])+a[i];
        bit.add(h[i],ans);
    }
    cout<<bit.sum(N)<<endl;
    return 0;
}