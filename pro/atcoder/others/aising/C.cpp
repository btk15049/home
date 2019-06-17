//https://atcoder.jp/contests/aising2019/tasks/aising2019_c
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
int buf[412][412];
int vis[412][412];
int dr[]={0,1,0,-1};
int dc[]={1,0,-1,0};
void dfs(int r,int c,int& b,int& w){
    if(vis[r][c])return;
    if(buf[r][c]==-1)return;
    if(buf[r][c])b++;
    else w++;
    vis[r][c]=1;
    for(int d:range(4)){
        int nr=r+dr[d];
        int nc=c+dc[d];
        if(buf[r][c]!=buf[nr][nc])dfs(nr,nc,b,w);
    }
}
int main(){
    cin>>R>>C;
    for(int i:range(412))for(int j:range(412))buf[i][j]=-1;
    for(int i:range(R)){
        string s;
        cin>>s;
        for(int j:range(C)){
            buf[i+1][j+1]=(s[j]=='#');
        }
    }
    LL ret=0;
    for(int i:range(R))for(int j:range(C)){
        int b=0,w=0;
        dfs(i+1,j+1,b,w);
        ret+=b*1ll*w;
    }
    cout<<ret<<endl;
    return 0;
}