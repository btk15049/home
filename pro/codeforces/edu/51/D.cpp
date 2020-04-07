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

constexpr int mod = 998244353;
int main() {
    int n,k;
    cin>>n>>k;
    vector<LL> s(2*n+10),d(2*n+10);
    s[1]=2;
    d[2]=2;
    for(int i:range(n-1)){
        vector<LL> ns(2*n+10),nd(2*n+10);
        for(int j:range(2*n+1)){
            ns[j]+=d[j]*2;
            ns[j]+=s[j];
            ns[j+1]+=s[j];
            nd[j+2]+=d[j];
            nd[j]+=d[j];
            nd[j+1]+=s[j]*2;
        }
        for(auto &it:ns)it%=mod;
        for(auto &it:nd)it%=mod;
        swap(s,ns);
        swap(d,nd);
        DEBUG {
            for(int j:range(2*n+1)){
                printf("s[%d][%d]=%lld\n",i+1,j,s[j]);
            }
            for(int j:range(2*n+1)){
                printf("d[%d][%d]=%lld\n",i+1,j,d[j]);
            }
                
        }
    }
    LL ret =s[k]+d[k];
    cout<<ret%mod<<endl;
    return 0;
}
