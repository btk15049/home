//http://codeforces.com/contest/1060/problem/E
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

using V = vector<LL>;
V l[212345];
V s[212345];
using G=vector<vector<int>>;

G g,t;
LL ret=0;
void make_tree(int v,int p){
    for(int u:g[v]){
        if(u==p)continue;
        t[v].push_back(u);
        make_tree(u,v);
    }
}

void dfs1(int v){
    l[v]={0,0};
    s[v]={1,0};
    for(int u:t[v]){
        dfs1(u);
        l[v][0]+=l[u][1]+s[u][1];
        l[v][1]+=l[u][0]+s[u][0];
        s[v][0]+=s[u][1];
        s[v][1]+=s[u][0];
    }
}
LL count(V ll,V ss){
    LL ans=0;
    ans+=ll[0]/2;
    ans+=(ll[1]-ss[1])/2+ss[1];
    return ans;
}
void dfs2(int v, V pl ,V ps){
    for(int u:t[v]){
        auto lu=l[u];
        auto su=s[u];
        auto lv=pl;
        auto sv=ps;
        lv[0]-=l[u][1]+s[u][1];
        lv[1]-=l[u][0]+s[u][0];
        sv[0]-=s[u][1];
        sv[1]-=s[u][0];
        lu[0]+=lv[1]+sv[1];
        lu[1]+=lv[0]+sv[0];
        su[0]+=sv[1];
        su[1]+=sv[0];
        int x[2]={lu[0],lu[1]};
        int y[2]={su[0],su[1]};
        LL ans = count(lu,su);
        ret+=ans;
        dfs2(u,lu,su);
    }
}
int main() {
    int n;
    cin>>n;
    g=G(n);
    t=G(n);
    for(int i:range(n-1)){
        int a,b;
        cin>>a>>b;a--;b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    make_tree(0,0);
    dfs1(0);
    dfs2(0,l[0],s[0]);
    ret+=count(l[0],s[0]);
    cout<<ret/2<<endl;
    return 0;
}
