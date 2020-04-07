//https://agc027.contest.atcoder.jp/tasks/agc027_f
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

using V = vector<int>;
using VV = vector<V>;
int N;

void tree(VV& g,VV &t,int v,int p){
    for(int u:g[v]){
        if(u==p)continue;
        t[v].push_back(u);
        tree(g,t,u,v);
    }
}
void malta(int v,VV &g,V &S){
    S[v]=1;
    for(int u:g[v]){
        malta(u,g,S);
    }
}
void dfs(int v,VV &a,VV &b,V&uA,V&uB,V&S,V&T){
    int i=0,j=0;
    int mi=a[v].size();
    int mj=b[v].size();
    while(i<mi||j<mj){
        if(i<mi&&(j==mj||a[v][i]<b[v][j])){
            malta(a[v][i],a,S);
            i++;
        }
        else if(i==mi||a[v][i]>b[v][j]){
            malta(b[v][j],b,T);
            uB[b[v][j]]=1;
            j++;
        }
        else {
            dfs(a[v][i],a,b,uA,uB,S,T);
            i++;j++;
        }
    }
}
int latte(int r,VV A,VV B){
    VV a(N),b(N);
    tree(A,a,r,r);
    tree(B,b,r,r);
    V uA(N,0),uB(N,0),S(N,0),T(N,0);
    dfs(r,a,b,uA,uB,S,T);
    if(S!=T)return 100;
    for(int v:range(N)){
        if(S[v]==1){
            uA[v]=1+a[v].size();
        }
    }
    V rA(N,-1);
    for(int v:range(N)){
        for(int u:a[v]){
            if(S[v]==1&&S[u]==1){
                rA[u]=v;
            }
        }
    }
    int ret = 0;
    for(int it:S)ret+=it;
    for(bool update=true;update;){
        update=false;
        for(int i:range(N)){
            if(uA[i]==1&&uB[i]==1){
                uA[i]--;
                if(rA[i]!=-1)uA[rA[i]]--;
                uB[i]--;
                for(int j:b[i])uB[j]++;
                update=true;
            }
        }
    }        

    if(*max_element(ALL(uB))==0)return ret;
    else return 100;
}
void solve(){
    cin>>N;
    VV A(N),B(N);
    for(int i:range(N-1)){
        int a,b;
        cin>>a>>b;a--;b--;
        A[a].push_back(b);
        A[b].push_back(a);
    }
    for(int i:range(N-1)){
        int a,b;
        cin>>a>>b;a--;b--;
        B[a].push_back(b);
        B[b].push_back(a);
    }
    for(int i:range(N)){
        sort(ALL(A[i]));
        sort(ALL(B[i]));
    }
    int ret= 100;
    for(int i:range(N)){
        chmin(ret,latte(i,A,B));
    }
    if(ret==100){
        for(int i:range(N)){
            if(A[i].size()==1){
                int k = A[i][0];
                for(int j:range(N)){
                    if(j==i)continue;
                    if(j==k)continue;
                    VV nA=A;
                    nA[i][0]=j;
                    for(int p:range(nA[k].size())){
                        if(nA[k][p]==i){
                            swap(nA[k][p],nA[k].back());
                            nA[k].pop_back();
                            break;
                        }
                    }
                    nA[j].push_back(i);
                    for(int p=nA[j].size()-1;p>0;p--){
                        if(nA[j][p]<nA[j][p-1])swap(nA[j][p],nA[j][p-1]);
                    }
                    chmin(ret,latte(i,nA,B)+1);
                }
            }
        }
    }
    if(ret==100)ret=-1;
    cout<<ret<<endl;
}
int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }
}
