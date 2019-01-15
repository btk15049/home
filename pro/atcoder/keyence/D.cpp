//https://atcoder.jp/contests/keyence2019/tasks/keyence2019_d
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

int R,C;
int r[11234];
int c[11234];
constexpr int mod = 1e9+7;
int main(){
    cin>>R>>C;
    LL ret=1;
    LL f=0;
    for(int i:range(R))cin>>r[i];
    for(int i:range(C))cin>>c[i];
    sort(r,r+R);
    sort(c,c+C);
    int x=R-1,y=C-1;
    LL useR=0;
    LL useC=0;
    for(int i=R*C;i>=1;i--){
        int rp=(x>=0?r[x]:0);
        int cp=(y>=0?c[y]:0);
        if(rp==i&&cp==i){
            f+=useR+useC;
            useR++;
            useC++;
            x--;
            y--;
        }
        else if(rp!=i&&cp!=i){
            ret=(ret*f)%mod;
            f--;
        }
        else if(rp==i){
            ret=(ret*useC)%mod;
            f+=(useC-1);
            useR++;
            x--;
        }
        else{ //cp==i
            ret=(ret*useR)%mod;
            f+=(useR-1);
            useC++;
            y--;
        }
        //cout<<i<<" "<<ret<<endl;
    }
    cout<<ret<<endl;
    return 0;
}