//https://atcoder.jp/contests/yahoo-procon2019-qual/tasks/yahoo_procon2019_qual_e
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

constexpr int mod = 998244353;
int R,C;
int A[312][312];
LL pow_mod(LL a,LL n,int M=mod){
    LL res=1;
    a%=M;
    while(n){
        if(n&1)
            res=(res*a)%M;
        a=(a*a)%M;
        n>>=1;
    }
    return res;
}
int get_rank(){
    int ret = 0;
    for(int c:range(C)){
        int id=-1;
        for(int i:range(ret,R)){
            if(A[i][c]==1){
                id=i;
            }
        }
        if(id==-1)continue;
        for(int j:range(C)){
            swap(A[ret][j],A[id][j]);
        }
        ret++;
        for(int i:range(ret,R)){
            if(A[i][c]==1)for(int j:range(C)){
                A[i][j] = A[i][j] xor A[ret-1][j];
            }
        }
    }
    return ret;
}
int main(){
    cin>>R>>C;
    for(int i:range(R))for(int j:range(C)){
        cin>>A[i][j];
    }
    LL ret=pow_mod(2,R+C-1)-pow_mod(2,R+C-1-get_rank())+mod;
    cout<<ret%mod<<endl;
    return 0;
}