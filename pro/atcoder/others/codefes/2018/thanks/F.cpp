//https://beta.atcoder.jp/contests/code-thanks-festival-2018-open/tasks/code_thanks_festival_2018_f
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
int N,M,K;
using V=vector<int>;
V g[1123];
int root=0;
int ret[1123];
int put[1123];
int cnt[1123];
int dep[1123];
void dfs(int v,int d){
    if(put[v])return;
    dep[v]=d;
    cnt[d]++;
    for(int u:g[v])dfs(u,d+1);
}
int get_all(){
    int ret=0;
    for(int i:range(400))ret+=cnt[i];
    return ret;
}
int get_lb(int need){
    int k=need;
    int ret=0;
    for(int i:range(400)){
        int p=min(k,cnt[i]);
        ret+=p*i;
        k-=p;
    }
    return ret;
}
int get_ub(int need){
    int k=need;
    int ret=0;
    for(int _i:range(400)){
        int i = 400-_i;
        int p=min(k,cnt[i]);
        ret+=p*i;
        k-=p;
    }
    return ret;
}

int main(){
    cin>>N>>M>>K;
    for(int i:range(1,N+1)){
        int p;
        cin>>p;
        if(p==0)root=i;
        else g[p].push_back(i);
    }
    for(int i:range(M)){
        bool ok=false;
        for(int j:range(1,N+1))dep[j]=-1;
        dfs(root,1);
        for(int j:range(1,N+1)){
            if(dep[j]==-1)continue;
            put[j]=1;
            for(int k:range(500))cnt[k]=0;
            dfs(root,1);
            //cout<<i<<" "<<j<<endl;
            if(get_all()>=M-i-1){
                int lb=get_lb(M-i-1);
                int ub=get_ub(M-i-1);
                if(lb<=K-dep[j]&&K-dep[j]<=ub){
                    ok=true;
                    ret[i]=j;
                    K-=dep[j];
                    break;
                }
            }
            put[j]=0;
        }
        if(ok==false){
           cout<<-1<<endl;
           return 0;
        }
    }
    string s(M,' ');
    s.back()='\n';
    for(int i:range(M))cout<<ret[i]<<s[i];
    return 0;
}