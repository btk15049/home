//https://atcoder.jp/contests/abc125/tasks/abc125_c
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
#define REC(ret, ...) std::function<ret (__VA_ARGS__)>
template <typename T>inline bool chmin(T &l, T r){bool a = l>r; if (a)l = r; return a;}
template <typename T>inline bool chmax(T &l, T r){bool a = l<r; if (a)l = r; return a;}
template <typename T>istream& operator>>(istream &is, vector<T> &v){for (auto &it : v)is >> it;return is;}
template<typename T>inline T& unused_var(T& v){return v;}
class reverse_range {private:struct I {int x;int operator*() {return x-1;}bool operator!=(I& lhs) {return x>lhs.x;}void operator++() {--x;}};I i, n;public:reverse_range(int n) :i({ 0 }), n({ n }){}reverse_range(int i, int n) :i({ i }), n({ n }){}I& begin() {return n;}I& end() {return i;}};
class range {private: struct I { int x; int operator*() { return x; }bool operator!=(I& lhs) { return x<lhs.x; }void operator++() { ++x; } }; I i, n;public:range(int n) :i({ 0 }), n({ n }) {}range(int i, int n) :i({ i }), n({ n }) {}I& begin() { return i; }I& end() { return n; }reverse_range operator!(){return reverse_range(*i,*n);}};
using LL = long long;

LL gcd(LL a,LL b){
    return (b==0)?a:gcd(b,a%b);
}

int N;
LL A[212345];
LL B[212345];
LL C[212345];
int main(){
    cin>>N;
    for(int i:range(N)){
        cin>>A[i];
        A[i+N]=A[i];
    }
    for(int i:range(1,N+1)){
        B[i]=gcd(B[i-1],A[i-1]);
    }
    for(int i:!range(1,N+1)){
        C[i]=gcd(C[i+1],A[i-1]);
    }
    LL ret = 1;
    for(int i:range(1,N+1)){
        chmax(ret,gcd(B[i-1],C[i+1]));
    }
    cout << ret << endl;
    return 0;
}