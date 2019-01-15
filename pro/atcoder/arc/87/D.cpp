//https://atcoder.jp/contests/arc087/tasks/arc087_b
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

vector<int> d[2]={{0},{0}};
int g[2];
bool solve(vector<int> &dx,int x){
    bitset<16001> dp;
    dp[8000]=true;
    for(int it:dx){
        dp=(dp<<it)|(dp>>it);
    }
    return dp[8000+x];
}
int main(){
    string s;
    cin>>s>>g[0]>>g[1];
    int n=s.size();
    int id=0;
    while(id<n&&s[id]=='F'){
        g[0]--;
        id++;
    }
    int t=0;
    for(int i:range(id,n)){
        if(s[i]=='T'){
            d[t].push_back(0);
            t=1-t;
        }
        else d[t].back()++;
    }
    g[0]=abs(g[0]);
    g[1]=abs(g[1]);
    if(solve(d[0],g[0])&&solve(d[1],g[1]))cout<<"Yes"<<endl;
    else cout<<"No"<<endl;
    return 0;
}