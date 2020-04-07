//
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
class reverse_range {private:struct I {int x;int operator*() {return x-1;}bool operator!=(I& lhs) {return x>lhs.x;}void operator++() {--x;}};I i, n;public:reverse_range(int n) :i({ 0 }), n({ n }){}reverse_range(int i, int n) :i({ i }), n({ n }){}I& begin() {return n;}I& end() {return i;}};
class range {private: struct I { int x; int operator*() { return x; }bool operator!=(I& lhs) { return x<lhs.x; }void operator++() { ++x; } }; I i, n;public:range(int n) :i({ 0 }), n({ n }) {}range(int i, int n) :i({ i }), n({ n }) {}I& begin() { return i; }I& end() { return n; }reverse_range operator!(){return reverse_range(*i,*n);}};


int N,M;
string S;
LL A[1123];
int a[1123];
int b[1123];
LL B[1123];

#include <bits/stdc++.h>
using namespace std;
#define pb push_back

using FLOW = LL;
namespace flow{
    constexpr FLOW INF = 1e12;
    struct edge{
        FLOW flow;
        int to,rev;
    };
    typedef vector<edge> E;
    typedef vector<E> Graph;
    void addedge(Graph&g,int from,int to,FLOW f){
        int x=g[from].size();
        int y=g[to].size();
        g[from].pb(edge{f,to,y});
        g[to].pb(edge{(FLOW)0,from,x});
    }

    vector<int> bfs(Graph& G,int s){
        int N = G.size();
        queue<int> que;
        vector<int> dist(N,-1);
        dist[s] = 0;
        que.push(s);
        for(;!que.empty();que.pop()){
            auto v=que.front();
            for(auto& e : G[v])
                if(e.flow>0&&dist[e.to]==-1){
                    dist[e.to] = dist[v] + 1;
                que.push(e.to);
                }
        }
        return dist;
    }
}
FLOW maxflow(flow::Graph& G,int s,int t){
    using namespace flow;
    FLOW res=0;
    int N = G.size();
    while(true){
        auto dist = bfs(G,s);
        if(dist[t] < 0)break;
        vector<unsigned> iter(N,0);
        std::function<FLOW(int,FLOW)> dfs=[&](int v,FLOW f){
            if(v==s)return f;
            for(auto &i = iter[v]; i < G[v].size(); i++){
                edge &e = G[v][i];
                edge &re = G[e.to][e.rev];
                if(re.flow>0 && dist[v] >dist[e.to]){
                    FLOW d=dfs(e.to,min(f,re.flow));
                    if(d>0){e.flow+=d;re.flow-=d;return d;}
                }
            }
            return (FLOW)0;
        };
        FLOW f;
        while((f=dfs(t,INF))> 0)res+=f;
    }
    return res;
}

int main(){
    cin>>N>>M>>S;
    for(int i:range(N))cin>>A[i];
    int size=N;
    int SS=size++;
    int GG=size++;
    for(int i:range(M)){
        cin>>a[i]>>b[i]>>B[i];
        a[i]--;b[i]--;
        if(a[i]>b[i])swap(a[i],b[i]);
    }
    flow::Graph g(size);
    for(int i:range(N)){
        if(S[i]=='L'){
            flow::addedge(g,SS,i,A[i]);
        }
        else{
            flow::addedge(g,i,GG,A[i]);
        }
    }
    for(int i:range(M)){
        string X=string(1,S[a[i]])+string(1,S[b[i]]);
        //cerr <<X << endl;
        flow::addedge(g,b[i],a[i],B[i]);
        /*
        if(X=="LL"){
            flow::addedge(g,a[i],b[i],B[i]);
        }
        if(X=="LR"){
            flow::addedge(g,a[i],b[i],B[i]);
        }
        if(X=="RL"){
            flow::addedge(g,a[i],b[i],B[i]);
        }
        if(X=="RR"){
            flow::addedge(g,a[i],b[i],B[i]);
        }
        */

    }
    cout <<maxflow(g,SS,GG)<<endl;
    return 0;
}