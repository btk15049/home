//http://codeforces.com/contest/1067/problem/B
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

#define ng {cout<<"No"<<endl;return 0;}
#define ok {cout<<"Yes"<<endl;return 0;}
using V=vector<int>;
using VV=vector<V>;
int main(){
    int n,k;
    cin>>n>>k;
    VV g(n);
    for(int i:range(n-1)){
        int a,b;
        cin>>a>>b;
        a--;b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    V vx;
    V used(n,0);

    for(int i:range(n)){
        if(g[i].size()==1){
            vx.push_back(i);
        }
        else if(g[i].size()<3)ng;
    }
    for(int i:range(k)){
        int sz = vx.size();
        if(sz==0)ng;
        V nxt;
        for(int _:range(sz)){
            used[vx[_]]=1;
        }
        for(int _:range(sz)){
            int v = vx[_];
            int par = -1;
            for(int u:g[v]){
                if(used[u]==0&&par!=-1)ng;
                if(used[u]==0)par=u;
            }
            if(par==-1)ng;
            nxt.push_back(par);
        }
        sort(ALL(nxt));
        nxt.erase(unique(ALL(nxt)),nxt.end());
        swap(vx,nxt);
    }
    if(vx.size()!=1)ng;
    int center=vx[0];
    for(int i:range(n)){
        if(i==center){
            if(g[i].size()<3)ng;
        }
        else{
            if(g[i].size()==1);
            else if(g[i].size()<4)ng;
        }
    }
    ok;
    return 0;
}