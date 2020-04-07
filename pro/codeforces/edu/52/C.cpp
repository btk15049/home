//http://codeforces.com/contest/1065/problem/C
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
    int n;
    LL k;
    cin>>n>>k;
    vector<LL> h(n);
    cin>>h;
    sort(ALL(h));
    reverse(ALL(h));
    LL H = h.front();
    int ptr=0;
    LL ret=0;
    while(1){
        while(ptr<n&&h[ptr]>=H)ptr++;
        if(ptr==n)break;
        LL rH = H-h[ptr];
        LL onestep = k/ptr;
        LL slices = rH/onestep;
        if(slices>0){
            ret+=slices;
            H-=onestep*slices;
        }
        else{
            LL rest = k-rH*ptr;
            H = h[ptr];
            while(1){
                while(ptr<n&&h[ptr]>=H)ptr++;
                if(ptr==n||ptr>rest)break;
                rH = H-h[ptr];
                LL HH = min(rest/ptr,rH);
                H-=HH;
                rest-=HH*ptr;
            }
            ret++;
        }
    }
    cout<<ret<<endl;
    return 0;
}

