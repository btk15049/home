//http://codeforces.com/contest/1028/problem/E
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
int n;
LL b[412345];
LL a[412345];
constexpr LL INF =  1e18;
constexpr LL base = 2e6;
bool check(){
    for(int i:range(n)){
        LL x = a[i];
        LL y = a[(i+1)%n];
        if(y==0)return false;
        if(y<0||y>INF)return false;
        if(x%y!=b[i])return false;
    }
    return true;
}
int main(){
    cin>>n;
    for(int i:range(n)){
        cin>>b[i];
    }
    bool all_zero=true;
    bool all_same=true;
    int pos = -1;
    for(int i:range(n)){
        if(b[i]!=0)all_zero=false;
        if(b[i]!=b[(i+1)%n])all_same=false;
        if(b[i]<b[(i+1)%n])pos=(i+1)%n;
    }
    if(all_zero==true){
        for(int i:range(n))a[i]=1;
    }
    else if(all_same==false){
        a[pos] = b[pos];
        int ptr = pos;
        while(1){
            int nxt = (n-1+ptr)%n;
            if(nxt==pos)break;
            chmax(a[nxt],base);
            if(a[nxt]%a[ptr]>b[nxt])a[nxt]+=a[ptr]-a[nxt]%a[ptr];
            a[nxt]+=b[nxt]-a[nxt]%a[ptr];
            ptr=nxt;
        }
    }
    else{
        cout<<"NO"<<endl;
        return 0;
    }
    cout<<"YES"<<endl;
    string sp(n,' ');
    sp.back()='\n';
    for(int i:range(n)){
        cout<<a[i]<<sp[i];
    }
    if(check()==false)return -1;
    return 0;
}