//https://atcoder.jp/contests/tenka1-2019/tasks/tenka1_2019_e
/**
 * @file template.cpp
 * @brief 競技プログラミング用テンプレート
 * @author btk15049
 * @date 2019/03/08
 */
#include<bits/stdc++.h>
using namespace std;
#define TEMPLATE
#ifdef BTK
#define DEBUG if(1)
#else
#define CIN_ONLY if(1)
struct cww {cww() {CIN_ONLY{ios::sync_with_stdio(false); cin.tie(0);}}}star;
#define DEBUG if(0)
#endif
#define ALL(v) (v).begin(),(v).end()
#define REC(ret, ...) std::function<ret (__VA_ARGS__)>
template <typename T>inline bool chmin(T &l, T r){bool a = l>r; if (a)l = r; return a;}
template <typename T>inline bool chmax(T &l, T r){bool a = l<r; if (a)l = r; return a;}
template <typename T>istream& operator>>(istream &is, vector<T> &v){for (auto &it : v)is >> it;return is;}
class reverse_range {private:struct I {int x;int operator*() {return x-1;}bool operator!=(I& lhs) {return x>lhs.x;}void operator++() {--x;}};I i, n;public:reverse_range(int n) :i({ 0 }), n({ n }){}reverse_range(int i, int n) :i({ i }), n({ n }){}I& begin() {return n;}I& end() {return i;}};
class range {private: struct I { int x; int operator*() { return x; }bool operator!=(I& lhs) { return x<lhs.x; }void operator++() { ++x; } }; I i, n;public:range(int n) :i({ 0 }), n({ n }) {}range(int i, int n) :i({ i }), n({ n }) {}I& begin() { return i; }I& end() { return n; }reverse_range operator!(){return reverse_range(*i,*n);}};
template<typename T>inline T& unused_var(T& v){return v;}
using LL = long long;

int N;
LL a[112345];

LL b[112345];
int bs=0;

LL gcd(LL a,LL b){
    return (b==0)?a:gcd(b,a%b);
}

LL f(){
    LL g=0;
    for(int i:range(bs)){
        g=gcd(g,b[i]);
    }
    return g;
}

namespace prime{
    constexpr int sz = 112345;
    bool ip[sz];
    struct pr{
        pr(){
            ip[0]=ip[1]=false;
            for(int i:range(2,sz)){
                ip[i]=true;
            }
            for(int i:range(sz)){
                if(ip[i]){
                    for(int j=i+i;j<sz;j+=i){
                        ip[j]=false;
                    }
                }
            }
        }
    }pr_init;
    inline bool is(const int i){
        return ip[i];
    }
    vector<LL> factor(LL n){
        vector<LL> ret;
        for(LL i:range(2,sz)){
            if(n%i==0){
                ret.push_back(i);
                while(n%i==0)n/=i;
            }
        }
        if(n>1)ret.push_back(n);
        return ret;
    }
}
set<LL> ret;

int main(){
    cin >> N;
    N++;
    for(int i:range(N)){
        cin>>a[i];
        b[bs++]=abs(a[i]);
    }
    reverse(a,a+N);
    {
        auto fact=prime::factor(f());
        for(auto &it:fact){
            ret.insert(it);
        }
    }
    for(int p:range(2,N+10)){
        if(prime::is(p)==false)continue;
        //if(N<=10)cerr << p <<",";
        if(a[0]%p)continue;
        for(int i:range(min(N,p-1))){
            b[i]=0;
            for(int j=i;j<N;j+=p-1){
                b[i]+=(a[j]%p+p)%p;
            }
        }
        bs=p-1;
        //if(p==2)cerr << b[0] << endl;
        if(f()%p==0)ret.insert(p);
    }
    for(auto p:ret){
        cout<<p<<"\n";
    }
}


