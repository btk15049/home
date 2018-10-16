//http://codeforces.com/contest/1066/problem/F
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

LL x[212345];
LL y[212345];
LL latte[212345];
int malta=0;
LL d(int i,int j){
    return abs(x[i]-x[j])+abs(y[i]-y[j]);
}
int main() {
    int n;
    cin>>n;
    for(int i:range(n)){
        cin>>x[i]>>y[i];
        latte[malta++]=max(x[i],y[i]);
    }
    x[n]=0,y[n]=0;
    n++;
    latte[malta++]=0;
    sort(latte,latte+malta);
    malta=unique(latte,latte+malta)-latte;
    using V = vector<int>;
    using VV = vector<V>;
    VV L(malta);
    for(int i:range(n)){
        int key = lower_bound(latte,latte+malta,max(x[i],y[i]))-latte;
        L[key].push_back({i});
    }
    for(int i:range(malta)){
        sort(ALL(L[i]),[&](const int l,const int r){
            int lt = (x[l]<y[l]);
            int rt = (x[r]<y[r]);
            if(lt||rt)return x[l]<x[r];
            else return y[l]>y[r];
        });
        DEBUG for(auto &it:L[i])printf("(%lld,%lld)\n",x[it],y[it]);
    }
    LL ldp=0,rdp=0;
    for(int i:range(1,malta)){
        int lm = L[i].front();
        int rm = L[i].back();
        int pl = L[i-1].front();
        int pr = L[i-1].back();
        LL inner_move = d(lm,rm);
        LL lnx = inner_move+min(ldp+d(pl,rm),rdp+d(pr,rm));
        LL rnx = inner_move+min(ldp+d(pl,lm),rdp+d(pr,lm));
        ldp=lnx;
        rdp=rnx;
    }
    cout<<min(ldp,rdp)<<endl;
    return 0;
}
