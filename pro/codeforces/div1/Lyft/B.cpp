//http://codeforces.com/contest/1074/problem/B
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

using V=vector<int>;
using VV=vector<V>;
VV g;
int x[1123];
int y[1123];
int d[1123];
int A(int v){
    cout<<"A "<<v+1<<endl;cout.flush();
    cin>>v;
    return v-1;
}

int B(int v){
    cout<<"B "<<v+1<<endl;cout.flush();
    cin>>v;
    return v-1;
}

void C(int v){
    if(v!=-1)v++;
    cout<<"C "<<v<<endl;cout.flush();
}

void dfs(int v,int p,int dep=0){
    d[v]=dep;
    for(int u:g[v]){
        if(u==p)continue;
        dfs(u,v,dep+1);
    }
}
int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        g=VV(n);
        for(int i:range(n-1)){
            int a,b;
            cin>>a>>b;
            a--;b--;
            g[a].push_back(b);
            g[b].push_back(a);
        }
        int k1,k2;
        cin>>k1;
        for(int i:range(k1)){
            cin>>x[i];x[i]--;
        }
        cin>>k2;
        for(int i:range(k2)){
            cin>>y[i];y[i]--;
        }
        int root = B(y[0]);
        dfs(root,root);
        int near = x[0];
        for(int i:range(k1))if(d[near]>d[x[i]])near=x[i];
        int choice = A(near);
        int ret = -1;
        for(int i:range(k2))if(choice==y[i])ret=near;
        C(ret);
    }
    return 0;
}