//https://atcoder.jp/contests/tenka1-2019/tasks/tenka1_2019_c
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

int bw[212345];
int bws[212345];
int BWS(int l,int r){
    return bws[r]-bws[l];
}
int main(){
    int N;
    cin>> N;
    string S;
    cin>>S;
    for(int i:range(N)){
        bw[i]=(S[i]=='#')?1:0;
    }
    for(int i:range(N)){
        bws[i+1]=bws[i]+bw[i];
    }
    int ret=BWS(0,N);
    ret=min(ret,N-ret);
    for(int i:range(N)){
        int lb = i;
        int ub = N-i;
        chmin(ret,BWS(0,i)+(ub-BWS(i,N)));
    }
    cout<<ret<<endl;


    return 0;
}