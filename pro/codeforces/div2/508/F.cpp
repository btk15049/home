//http://codeforces.com/contest/1038/problem/F
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
int n,k;
string s;
inline LL rot(LL x){
    return (x>>1)|((x&1)<<(n-1));
}
LL latte[40];
int main() {
    cin>>n;
    string s;
    cin>>s;
    k=s.size();
    LL in=0;
    for(int i:range(k)){
        if(s[i]=='1')in|=(1<<i);
    }
    const LL mask = (1ll<<k)-1;
    LL ret = (1ll<<(n-k))*n;
    for(int sz:range(1,n/2+1)){
        if(n%sz==0){
            for(int _b:range(1<<sz)){
                const LL b = _b;
                LL bit=0;
                for(int i:range(n/sz)){
                    bit<<=sz;
                    bit|=b;
                }
                if((bit&mask)!=in)continue;
                int malta=0;
                for(int i:range(sz)){
                    latte[malta++]=bit;
                    bit=rot(bit);
                }
                sort(latte,latte+malta);
                malta=unique(latte,latte+malta)-latte;
                if(malta!=sz)continue;
                ret-=(n-sz);
                cout<<bitset<40>(bit).to_string()<<endl;

            }
        }
    }
    cout<<ret<<endl;
    return 0;
}