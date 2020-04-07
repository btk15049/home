//http://codeforces.com/contest/1065/problem/B
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

int main() {
    LL n,m;
    cin>>n>>m;
    LL bot,top;
    if(m==0)bot=n,top=n;
    else{
        bot = n;
        LL use = min(n/2,m);
        bot-=use*2;
        if(m-use>0&&n%2==1)bot--;
        LL lb = -1,ub=n;
        while(ub-lb>1){
            const LL x= (lb+ub)/2;
            if(m<=x*(x-1)/2)ub=x;
            else lb=x;
        }
        top = n-ub;
    }
    cout<<bot<<" "<<top<<endl;
    return 0;
}

