//http://codeforces.com/contest/1037/problem/E
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


using V =vector<int>;
using VV=vector<V>;

int n,m,k;
int a[212345];
int b[212345];
int d[212345];
int ee[212345];
int ev[212345];
int ret[212345];
V g[212345];
int main(){
    cin>>n>>m>>k;
    for(int i:range(m)){
        cin>>a[i]>>b[i];
        a[i]--;b[i]--;
        g[a[i]].push_back(i);
        g[b[i]].push_back(i);
        d[a[i]]++;
        d[b[i]]++;
        ee[i]=1;
    }
    int v = n;
    queue<int> que;
    for(int i:range(n)){
        if(d[i]>=k){
            ev[i]=1;
        }
        else{
            ev[i]=0;
            que.push(i);
        }
    }
    for(int ri:range(m)){
        while(que.size()){
            int x=que.front();que.pop();
            v--;
            for(auto &e:g[x]){
                if(ee[e]==0)continue;
                int y=a[e]^b[e]^x;
                ee[e]=0;d[x]--;d[y]--;
                if(ev[y]==0)continue;
                else if(d[y]<k){
                    ev[y]=0;
                    que.push(y);
                }
            }
        }
        int i = m-1-ri;
        ret[i]=v;
        if(ee[i]==1){
            ee[i]=0;d[a[i]]--;d[b[i]]--;
            if(ev[a[i]]==1&&d[a[i]]<k){
                ev[a[i]]=0;que.push(a[i]);
            }
            if(ev[b[i]]==1&&d[b[i]]<k){
                ev[b[i]]=0;que.push(b[i]);
            }
        }
    }
    for(int i:range(m))cout<<ret[i]<<endl;
    return 0;
}