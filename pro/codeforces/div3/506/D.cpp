//http://codeforces.com/contest/1029/problem/D
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

int n;
LL k;
LL a[312345];
int d[312345];
map<LL,LL> cnt[20];
int main(){
    int _k;
    scanf("%d%d",&n,&_k);
    k=_k;
    for(int i:range(n)){
        int b;
        scanf("%d",&b);
        a[i]=b;
        d[i] =to_string(b).size();
        a[i]%=k;
        (cnt[d[i]])[a[i]]++;
    }
    LL ret = 0;
    for(int i:range(n)){
        LL p = 1;
        for(int j:range(1,12)){
            p*=10;
            p%=k;
            LL need = k - a[i]*p%k;
            need%=k;
            ret+=cnt[j][need];
            if(d[i]==j&&need==a[i])ret--;
        }
    }
    printf("%lld\n",ret);
    return 0;
}