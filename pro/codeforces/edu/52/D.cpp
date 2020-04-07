//http://codeforces.com/contest/1065/problem/D
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

int r[334],c[334];
pair<int,int> d[334][334];
const int inf = 100*100;
inline pair<int,int> f(pair<int,int> a,pair<int,int> b){
    return {a.first+b.first,a.second+b.second};
}
int main() {
    int n;
    cin>>n;
    for(int i:range(n)){
        for(int j:range(n)){
            int a;
            cin>>a;
            a--;
            r[a]=i;
            c[a]=j;
        }
    }
    n=n*n;
    for(int i:range(3*n))for(int j:range(3*n)){
        d[i][j]={inf,0};
    }
    for(int i:range(n))for(int a:range(3))for(int b:range(3)){
        if(a!=b)d[a*n+i][b*n+i]={1,1};
    }
    for(int i:range(n))for(int j:range(n)){
        int dr=abs(r[i]-r[j]);
        int dc=abs(c[i]-c[j]);
        if(dr+dc==3&&dr<=2&&dc<=2)d[i][j]={1,0};
        if(dr==0||dc==0)d[n+i][n+j]={1,0};
        if(dr==dc)d[2*n+i][2*n+j]={1,0};
        if(dr==0&&dc==0){
            for(int k:range(3))d[k*n+i][k*n+j]={0,0};
        }
    }
    for(int k:range(3*n))for(int i:range(3*n))for(int j:range(3*n)){
        chmin(d[i][j],f(d[i][k],d[k][j]));
    }
    pair<int,int> dp[3]={{0,0},{0,0},{0,0}};
    for(int i:range(n-1)){
        pair<int,int> nx[3]={{inf,0},{inf,0},{inf,0}};
        for(int j:range(3)){
            for(int k:range(3)){
                chmin(nx[k],f(dp[j],d[j*n+i][k*n+i+1]));
            }
        }
        for(int j:range(3))dp[j]=nx[j];
    }
    pair<int,int> ret=*min_element(dp,dp+3);
    cout<<ret.first<<" "<<ret.second<<endl;
    return 0;
}

