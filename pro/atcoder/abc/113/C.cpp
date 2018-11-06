//https://beta.atcoder.jp/contests/abc113/tasks/abc113_c
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

string f(int n,int d){
    string s=to_string(n);
    while(s.size()<d)s="0"+s;
    return s;
}

int p[112345];
int y[112345];
string s[112345];
int main(){
    int n,m;
    cin>>n>>m;
    for(int i:range(m)){
        cin>>p[i]>>y[i];
        s[i]=f(p[i],6)+f(y[i],10);
    }
    sort(s,s+m);
    for(int i:range(m)){
        cout<<f(p[i],6);
        int id = lower_bound(s,s+m,f(p[i],6)+f(y[i],10))-lower_bound(s,s+m,f(p[i],6))+1;
        cout<<f(id,6)<<endl;
    }
    return 0;
}