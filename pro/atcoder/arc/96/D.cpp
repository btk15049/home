//https://atcoder.jp/contests/arc096/tasks/arc096_b
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
constexpr int S = 112345;
int N;
LL C;
LL x[2*S];
LL v[2*S];
LL vs[2*S];
LL sg[2*S],db[2*S];
int main(){
    cin>>N>>C;
    for(int i:range(1,N+1)){
        cin>>x[i]>>v[i];
    }
    x[0]=0;
    v[0]=0;
    N++;
    for(int i:range(N)){
        x[i+N]=C+x[i];
        v[i+N]=v[i];
    }
    for(int i:range(2*N)){
        vs[i+1]=vs[i]+v[i];
    }
    for(int i:range(2*N)){
        sg[i]=-1e18;
        db[i]=-1e18;
    }
    sg[N]=0;
    db[N]=0;
    for(int i:range(N+1,2*N)){
        sg[i]=sg[i-1];
        db[i]=db[i-1];
        const LL vx = vs[i+1]-vs[N];
        const LL cx = x[i]-x[N];
        chmax(sg[i],vx-cx);
        chmax(db[i],vx-2*cx);
        //cout<<vx<<"  "<<cx<<endl;
    }
    for(int i:!range(1,N)){
        sg[i]=sg[i+1];
        db[i]=db[i+1];
        const LL vx = vs[N]-vs[i];
        const LL cx = x[N]-x[i];
        chmax(sg[i],vx-cx);
        chmax(db[i],vx-2*cx);
    }
    LL ret=0;
    for(int i:range(N)){
        //cout<<sg[N+i]<<" "<<db[i+1]<<endl;
        chmax(ret,db[N+i]+sg[i+1]);
        chmax(ret,sg[N+i]+db[i+1]);
    }
    cout<<ret<<endl;
    return 0;
}