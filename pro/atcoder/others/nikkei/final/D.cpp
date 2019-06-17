//https://atcoder.jp/contests/nikkei2019-final/tasks/nikkei2019_final_d
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

int N,M;
vector<int> b[212345];
vector<int> e[212345];
int main(){
    cin>>N>>M;
    set<int> x;
    for(int i:range(M)){
        int t,l,r;
        cin>>t>>l>>r;
        l--;r--;
        b[l].push_back(t);
        e[r].push_back(t);
    }
    LL ret=0;
    x.insert(0);
    for(int i:range(N)){
        for(auto &it:b[i])x.insert(it);
        ret+=*(x.rbegin());
        //cout<<*(x.rbegin())<<endl;
        for(auto &it:e[i])x.erase(it);
    }
    cout<<ret<<endl;
    return 0;
}