//https://atcoder.jp/contests/nikkei2019-final/tasks/nikkei2019_final_c
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

LL R,C;
int K;
LL r[112345];
LL c[112345];
LL rs[112345];
LL cs[112345];
int main(){
    cin>>R>>C>>K;
    for(int i:range(K)){
        int a,b;
        cin>>a>>b;
        r[a]--;
        c[b]--;
    }
    for(int i:range(1,R+1))r[i]+=C;
    for(int i:range(1,C+1))c[i]+=R;
    LL N=R*C-K;
    LL ret=0;
    for(int i:range(1,R+1)){
        rs[i+1]=rs[i]+r[i];
    }
    for(int i:range(1,C+1)){
        cs[i+1]=cs[i]+c[i];
        //if(R<3)cerr << i<<" "<<cs[i+1]<<endl;
    }
    LL tr,tc;
    {
        LL lb=0,ub=R;
        while(ub-lb>1){
            const int mid=(lb+ub)/2;
            if(rs[mid+1]<(N+1)/2)lb=mid;
            else ub=mid;
        }
        tr=ub;
    }
    {
        LL lb=0,ub=C;
        while(ub-lb>1){
            const int mid=(lb+ub)/2;
            if(cs[mid+1]<(N+1)/2)lb=mid;
            else ub=mid;
        }
        tc=ub;
    }
    for(int i:range(1,R+1))ret+=abs(i-tr)*r[i];
    for(int i:range(1,C+1))ret+=abs(i-tc)*c[i];
    //cerr<<tr<<" "<<tc<<endl;
    cout<<ret<<endl;
    return 0;
}