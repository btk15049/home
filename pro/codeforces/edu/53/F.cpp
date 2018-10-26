//http://codeforces.com/contest/1073/problem/F
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

int n;
using V = vector<int>;
using P = pair<int,int>;
using PP = pair<P,P>;
V g[212345];
P sg[212345];
PP db[212345];
P pl[212345];
#define cl first.first
#define tl first.second
constexpr int INF = 1e7;
pair<P,pair<P,P>> ret;
void idfs1(int v,int p){
    sg[v]={0,v};
    for(int u:g[v]){
        if(u==p)continue;
        idfs1(u,v);
        chmax(sg[v],{sg[u].first+1,sg[u].second});
    }
}

void idfs2(int v,int p){
    vector<P> s={pl[v]};
    for(int u:g[v]){
        if(u==p)continue;
        s.push_back({sg[u].first+1,sg[u].second});
    }
    sort(ALL(s));
    reverse(ALL(s));
    for(int u:g[v]){
        if(u==p)continue;
        auto x=s[0];
        if(x.second==sg[u].second)x=s[1];
        pl[u]={x.first+1,x.second};
        idfs2(u,v);
    }
}
void dfs(int v,int p){
    db[v]={{-INF,-INF},{v,v}};
    for(int u:g[v]){
        if(u==p)continue;
        dfs(u,v);
    }
    vector<P> s;
    vector<PP> d;
    s.reserve(g[v].size());
    d.reserve(g[v].size());
    for(int u:g[v]){
        if(u==p)continue;
        s.push_back({sg[u].first+1,sg[u].second});
        d.push_back({{db[u].cl+1,db[u].tl+2},db[u].second});
    }
    sort(ALL(s));
    reverse(ALL(s));
    sort(ALL(d));
    reverse(ALL(d));


    if(d.size()>=1){
        db[v]=d.front();
    }

    if(s.size()>=2){
        chmax(db[v],{{0,s[0].first+s[1].first},{s[0].second,s[1].second}});
    }
    if(d.size()>=2){
        chmax(ret,{{d[0].cl+d[1].cl+1,d[0].tl+d[1].tl},{d[0].second,d[1].second}});
    }
    if(v!=1){
        s.push_back({pl[v]});
        sort(ALL(s));
        reverse(ALL(s));
    }
    if(g[v].size()>=3){
        for(int u:g[v]){
            if(u==p)continue;
            auto x = s[0];
            auto y = s[1];
            if(x.second==sg[u].second)x=s[2];
            if(y.second==sg[u].second)y=s[2];
            chmax(ret,
            {
                {2+db[u].cl,2+db[u].tl+x.first+y.first},
                {
                    db[u].second,
                    {x.second,y.second}
                }
            });
        }
    }
    if(g[v].size()>=4){
        chmax(ret,{{1,s[0].first+s[1].first+s[2].first+s[3].first},
                    {{s[0].second,s[1].second},{s[2].second,s[3].second}}});
    }
}
void out(int a,int b,int c,int d){
    printf("%d %d\n%d %d\n",a,b,c,d);
}
int main(){
    scanf("%d",&n);
    for(int i:range(n-1)){
        int a,b;
        scanf("%d%d",&a,&b);
        g[a].push_back(b);
        g[b].push_back(a);
    }
    int isOver3 = 0;
    int is3 = 0;
    for(int i:range(1,n+1)){
        if(g[i].size()>=3)isOver3++;
        if(g[i].size()==3)is3++;
    }
    if(isOver3==0){
        vector<int> p;
        for(int i:range(1,n+1))if(g[i].size()==1){
            p.push_back(i);
            break;
        }
        p.push_back(g[p[0]][0]);
        while(g[p.back()].size()!=1){
            p.push_back(g[p.back()][0]^g[p.back()][1]^p[p.size()-2]);
        }
        out(p[0],p[1],p[2],p.back());
        return 0;
    }
    if(isOver3==1&&is3==1){
        int root = 0;
        for(int i:range(1,n+1))if(g[i].size()==3)root=i;
        vector<int> p1={root,g[root][0]};
        vector<int> p2={root,g[root][1]};
        vector<int> p3={root,g[root][2]};
        while(g[p1.back()].size()!=1){p1.push_back(g[p1.back()][0]^g[p1.back()][1]^p1[p1.size()-2]);}
        while(g[p2.back()].size()!=1){p2.push_back(g[p2.back()][0]^g[p2.back()][1]^p2[p2.size()-2]);}
        while(g[p3.back()].size()!=1){p3.push_back(g[p3.back()][0]^g[p3.back()][1]^p3[p3.size()-2]);}
        if(p1.size()>=3){
            out(p2.back(),p3.back(),p1[1],p1.back());
            return 0;
        }
        if(p2.size()>=3){
            out(p1.back(),p3.back(),p2[1],p2.back());
            return 0;
        }
        if(p3.size()>=3){
            out(p1.back(),p2.back(),p3[1],p3.back());
            return 0;
        }
    }
    pl[1]={0,1};
    idfs1(1,1);
    idfs2(1,1);
    dfs(1,1);

    out(ret.second.first.first,ret.second.second.first,
        ret.second.first.second,ret.second.second.second);

    return 0;
}