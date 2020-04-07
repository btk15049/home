//http://codeforces.com/contest/1027/problem/C
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
LL a[1123456];
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        map<LL,int> x;
        for(int i:range(n)){
            scanf("%lld",a+i);
            x[a[i]]++;
        }
        n=0;
        for(auto &it:x)if(it.second>=2){
            while(it.second>0){
                a[n++]=it.first;
                it.second--;
            }
        }
        int ret = -1;
        for(int i:range(1,n-2)){
            if(a[i]==a[i-1]&&a[i+1]==a[i+2]){
                if(ret==-1)ret = i;
                else if(a[ret+1]*a[i]>a[i+1]*a[ret])ret = i;
            }
        }
        int id = ret;
        printf("%lld %lld %lld %lld\n",a[id],a[id],a[id+1],a[id+1]);
    }

    return 0;
}