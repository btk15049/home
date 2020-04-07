//http://codeforces.com/contest/1016/problem/C
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#ifdef BTK
#define DEBUG if(1)
#else
#define CIN_ONLY if(0)
struct cww {cww() {CIN_ONLY{ios::sync_with_stdio(false); cin.tie(0);}}}star;
#define DEBUG if(0)
#endif
#define ALL(v) (v).begin(),(v).end()
#define REC(ret, ...) std::function<ret (__VA_ARGS__)>
template <typename T>inline bool chmin(T &l, T r){bool a = l>r; if (a)l = r; return a;}
template <typename T>inline bool chmax(T &l, T r){bool a = l<r; if (a)l = r; return a;}
template <typename T>istream& operator>>(istream &is, vector<T> &v){for (auto &it : v)is >> it;return is;}
class range {private: struct I { int x; int operator*() { return x; }bool operator!=(I& lhs) { return x<lhs.x; }void operator++() { ++x; } }; I i, n;public:range(int n) :i({ 0 }), n({ n }) {}range(int i, int n) :i({ i }), n({ n }) {}I& begin() { return i; }I& end() { return n; }};


LL a[312345];
LL b[312345];
LL as[312345];
LL bs[312345];
LL at[312345];
LL bt[312345];
int main(){
    int n;
    scanf("%d",&n);
    LL A=0,B=0;
    for(int i:range(n)){
        scanf("%lld",a+i);
        A+=a[i];
        as[i+1]=a[i]*(i+1)+as[i];
    }
    for(int i:range(n)){
        scanf("%lld",b+i);
        B+=b[i];
        bs[i+1]=b[i]*(i+1)+bs[i];
    }
    for(int ri:range(n)){
        int i = n-1-ri;
        at[i]=a[i]*(ri+1)+at[i+1];
        bt[i]=b[i]*(ri+1)+bt[i+1];
    }
    LL ret = 0;
    LL sum = 0;
    for(int i:range(n)){
        LL _x = ((as[n]-as[i])+at[i])/(n+1);
        LL _y = (bs[n]-bs[i]+bt[i])/(n+1);
        if(i%2==0){
            LL x = as[n]-as[i] - _x*(i+1);
            LL y = bt[i]-_y;
            chmax(ret,sum+x+_x*(2*i)+y+_y*(2*i+(n-i)));
            sum+=(i*2)*a[i]+(i*2+1)*b[i];
        }
        else{
            LL x = at[i]-_x;
            LL y = bs[n]-bs[i]-_y*(i+1);
            chmax(ret,sum+y+_y*(2*i)+x+_x*(2*i+(n-i)));
            sum+=(i*2)*b[i]+(i*2+1)*a[i];
        }
    }
    chmax(ret,sum);
    cout<<ret<<endl;
    return 0;
}