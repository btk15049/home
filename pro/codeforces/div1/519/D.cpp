//http://codeforces.com/contest/1043/problem/D
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

int n,m;
int a[10][212345];
int ptr[10];
int b[10][212345];
int main(){
    scanf("%d%d",&n,&m);
    for(int i:range(m))for(int j:range(n)){
        scanf("%d",&a[i][j]);
        b[i][a[i][j]]=j;
    }
    LL ret = 0;
    for(int bg=0;bg<n;){
        int len = 0;
        for(int i:range(m)){
            ptr[i]=b[i][a[0][bg]];
        }
        while(ptr[0]<n){
            bool ok=true;
            for(int i:range(1,m)){
                if(a[0][ptr[0]]!=a[i][ptr[i]]){
                    ok=false;
                    break;
                }
            }
            if(ok){
                len++;
                for(int i:range(m))ptr[i]++;
            }
            else{
                break;
            }
        }
        bg+=len;
        ret+=(len+1ll)*len/2;
    }
    printf("%lld\n",ret);
    return 0;
}