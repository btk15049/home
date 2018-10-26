//http://codeforces.com/contest/1073/problem/C
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

int dr[112345];
int dc[112345];
LL R[212345];
LL C[212345];
LL r,c;
int n;
string s;
int main(){
    dr['U']=0;dc['U']=+1;
    dr['D']=0;dc['D']=-1;
    dr['L']=-1;dc['L']=0;
    dr['R']=+1;dc['R']=0;
    cin>>n;
    cin>>s;
    for(int i:range(n)){
        R[i+1]=R[i]+dr[s[i]];
        C[i+1]=C[i]+dc[s[i]];
    }
    cin>>r>>c;
    int ret = n+1;
    auto check=[&](LL dist,int cnt){
        if(dist>cnt)return false;
        if(dist%2!=cnt%2)return false;
        return true;
    };
    for(int i:range(n)){
        if(check(abs(r-R[i])+abs(c-C[i]),n-i)==false)continue;
        int ok = n;
        int ng = i-1;
        while(ok-ng>1){
            const int mid = (ok+ng)/2;
            if(check(abs(r-(R[i]+(R[n]-R[mid])))+abs(c-(C[i]+(C[n]-C[mid]))),mid-i))ok=mid;
            else ng=mid;
        }
        chmin(ret,ok-i);
    }
    if(ret==n+1)ret=-1;
    cout<<ret<<endl;
    return 0;
}