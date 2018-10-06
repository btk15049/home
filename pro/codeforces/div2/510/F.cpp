//http://codeforces.com/contest/1042/problem/F
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
vector<int> g[1123456];
int ret=0;
int dfs(int v,int p){
    vector<int> c,d;
    if(g[v].size()==1){
        return 1;
    }
    for(int u:g[v]){
        if(p==u)continue;
        c.push_back(dfs(u,v));
    }
    sort(ALL(c));
    int ub = c.size()-1;
    int lb = 0;
    while(ub>=lb){
        while(lb<ub&&c[lb]+c[ub]<=k)lb++;
        d.push_back(c[ub]);
        ub--;
    }
    ret+=d.size();
    if(d.front()==0){
        ret--;
        return 0;
    }
    if(d.back()==k){
        return 0;
    }
    else {
        ret--;
        int latte=d.back()+1;
        return latte;
    }
}
int main() {
    scanf("%d%d",&n,&k);
    for(int i:range(n-1)){
        int a,b;
        scanf("%d%d",&a,&b);
        a--;b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    int r=0;
    for(int i:range(n))if(g[i].size()>=2)r=i;
    if(dfs(r,r)>0)ret++;
    printf("%d\n",ret);
    return 0;
}
