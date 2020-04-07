//https://agc027.contest.atcoder.jp/tasks/agc027_c
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


using V=vector<int>;
using VV = vector<V>;
int main() {
    int N,M;
    string s;
    cin>>N>>M>>s;
    VV g(N*4);
    const int AA=0,AB=N,BA=N+N,BB=N+N+N;
    for(int i:range(M)){
        int u,v;
        cin>>u>>v;
        u--;v--;
        if(s[u]!=s[v]){
            if(s[u]>s[v])swap(u,v);
            g[AB+u].push_back(BB+v);
            g[BA+v].push_back(AA+u);
        }
        else{
            if(s[u]=='A'){
                g[AA+u].push_back(AB+v);
                g[AA+v].push_back(AB+u);
            }
            else{
                g[BB+u].push_back(BA+v);
                g[BB+v].push_back(BA+u);
            }
        }
    }
    queue<int> que;
    V in(4*N);
    
    for(int f:range(4*N)){
        for(int t:g[f]){
            in[t]++;
        }
    }
    for(int i:range(4*N)){
        if(in[i]==0)que.push(i);
    }
    while(que.size()){
        int v=que.front();que.pop();
        for(int u:g[v]){
            in[u]--;
            if(in[u]==0)que.push(u);
        }
    }

    for(int i:range(4*N)){
        if(in[i]!=0){
            cout<<"Yes"<<endl;
            return 0;
        }
    }
    cout<<"No"<<endl;
    return 0;
}
