//http://codeforces.com/contest/1041/problem/C
#include<bits/stdc++.h>

using namespace std;
typedef long long LL;

#ifdef BTK
#define DEBUG if(1)
#else
#define CIN_ONLY if(1)
struct cww {cww() {CIN_ONLY{ios::sync_with_stdio(false); cin.tie(0);}}
}star;
#define DEBUG if(0)
#endif

#define ALL(v) (v).begin(),(v).end()
#define REC(ret, ...) std::function<ret (__VA_ARGS__)>
template <typename T>inline bool chmin(T &l, T r){bool a = l>r; if (a)l = r; return a;}
template <typename T>inline bool chmax(T &l, T r){bool a = l<r; if (a)l = r; return a;}
template <typename T>istream& operator>>(istream &is, vector<T> &v){for (auto &it : v)is >> it;return is;}

class range {private: struct I { int x; int operator*() { return x; }bool operator!=(I& lhs) { return x<lhs.x; }void operator++() { ++x; } }; I i, n;public:range(int n) :i({ 0 }), n({ n }) {}range(int i, int n) :i({ i }), n({ n }) {}I& begin() { return i; }I& end() { return n; }};

int n,m,d;

pair<LL,int> p[212345];
int ret[212345];
int main() {
    cin>>n>>m>>d;
    for(int i:range(n)){
        LL a;
        cin>>a;
        p[i]={a,i};
    }
    sort(p,p+n);
    int ng=0;
    int ok=n;
    while(ok-ng>1){
        const int mid = (ng+ok)/2;
        bool f=true;
        for(int i:range(n-mid)){
            if(p[i+mid].first-p[i].first<=d)f=false;
        }
        if(f)ok=mid;
        else ng=mid;
    }
    cout<<ok<<'\n';
    string sp(n,' ');
    sp.back()='\n';
    for(int i:range(n)){
        ret[p[i].second]=i%ok+1;
    }
    for(int i:range(n))cout<<ret[i]<<sp[i];
    return 0;
}
