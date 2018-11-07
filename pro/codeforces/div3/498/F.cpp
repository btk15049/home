//http://codeforces.com/contest/1006/problem/F
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
LL K;
LL a[100][100];
map<LL,LL> val[30][30];
const int dr1[2]={1,0};
const int dc1[2]={0,1};
const int dr2[2]={-1,0};
const int dc2[2]={0,-1};
inline bool in(int r,int c){return 0<=r&&r<R&&0<=c&&c<C;}
int main(){
    cin>>R>>C>>K;
    LL ret = 0;
    for(int i:range(R))for(int j:range(C))cin>>a[i+20][j+20];
    for(int bit:range(1<<(C-1))){
        int r=R-1,c=C-1;
        LL x=0;
        for(int i:range(C-1)){
            x^=a[r+20][c+20];
            const int d = (bit>>i)&1;
            r+=dr2[d];
            c+=dc2[d];
        }
        if(in(r,c)){
            val[r][c][x]++;
        }
    }
    for(int bit:range(1<<(R-1))){
        int r=0,c=0;
        LL x=0;
        for(int i:range(R-1)){
            x^=a[r+20][c+20];
            const int d = (bit>>i)&1;
            r+=dr1[d];
            c+=dc1[d];
        }
        x^=a[r+20][c+20];
        if(in(r,c)&&val[r][c].count(K^x)){
            ret+=val[r][c][x^K];
        }
    }
    cout<<ret<<endl;
    return 0;
}