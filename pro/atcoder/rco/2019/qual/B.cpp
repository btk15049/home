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

constexpr int N = 50;
constexpr int M = 2500;
int a[N][N];
int A[N][N];
int opt[M];
int opr[M];
int opc[M];
int K = 0;
int vis[N][N];
pair<int,int> dp[2512][2512];

void cl(){
    for(int i:range(N))for(int j:range(N))A[i][j]=a[i][j];
    K=0;
    for(int i:range(N))for(int j:range(N))vis[i][j]=0;
}

constexpr int dr[]={1,0,-1,0};
constexpr int dc[]={0,-1,0,1};

void input(){
    int n,m;
    cin>>n>>m;
    for(int i:range(N)){
        for(int j:range(N)){
            cin>>a[i][j];
        }
    }
}
void output(){
    for(int i:range(M)){
        cout<<opt[i]<<" "<<opr[i]<<" "<<opc[i]<<endl;
    }
}
void up(int r,int c,int to){
    while(K<M && A[r][c]<to){
        opt[K]=1;
        opr[K]=r;
        opc[K]=c;
        K++;
        A[r][c]++;
    }
}
void gt(int r,int c){
    opt[K]=2;
    opr[K]=r;
    opc[K]=c;
    K++;
}

void count(int r,int c,int bg,int ed,vector<int>&R,vector<int>&C,int &W){
    if(max(r,c)>=N)return;
    if(min(r,c)<0)return;
    if(A[r][c]<bg||ed<A[r][c])return;
    if(vis[r][c])return;
    vis[r][c]=1;
    R.push_back(r);
    C.push_back(c);
    W+=ed-A[r][c];
    for(int d:range(4)){
        count(r+dr[d],c+dc[d],bg,ed,R,C,W);
    }
}

void vis_clear(){
    for(int i:range(N)){
        for(int j:range(N)){
            vis[i][j]=0;
        }
    }
}
int ID[N][N];
void dfs(int fr,int fc,int r,int c,int bg,int ed,int cost,vector<int> path,vector<int>& ret,int flag){
    if(max(r,c)>=N)return;
    if(min(r,c)<0)return;
    if(ID[r][c]!=-1){
        if(ID[fr][fc]!=ID[r][c]){
            if(cost<ret.back()||(flag&&cost==ret.back()&&path.size()+1>ret.size())){
                ret = path;
                ret.push_back(cost);
            }
        }
        return;
    }
    else{
        if(A[r][c]>ed)return;
        int cdr = abs(fr-r);
        int cdc = abs(fc-c);
        if(cdr+cdc>3)return;
        cost+=ed-A[r][c];
        path.push_back(r);
        path.push_back(c);
        if(cost>ret.back())return;
        for(int d:range(4)){
            int nr=r+dr[d];
            int nc=c+dc[d];
            int ndr=abs(fr-nr);
            int ndc=abs(fc-nc);
            if(ndr+ndc>cdr+cdc)dfs(fr,fc,nr,nc,bg,ed,cost,path,ret,flag);
        }
    }

}
void build(int bg,int ed,const int INF,int flag){
    vis_clear();
    vector<vector<int>> RR,CC;
    vector<int> id;
    int p = 0;
    for(int i:range(N)){
        for(int j:range(N)){
            ID[i][j]=-1;
        }
    }

    for(int i:range(N)){
        for(int j:range(N)){
            vector<int> R,C;
            int w=1;
            if(bg<=A[i][j]&&A[i][j]<=ed){
                if(vis[i][j]==0){
                    count(i,j,bg,ed,R,C,w);
                    if(R.size()<ed){
                        RR.push_back(R);
                        CC.push_back(C);
                        id.push_back(p);
                    }
                    for(int k:range(R.size())){
                        ID[R[k]][C[k]]=p;
                    }
                    p++;
                }
            }
        }
    }
    if(RR.size()==0)return;
    vector<int> ret={INF};
    for(int i:range(RR.size())){
        auto& R=RR[i];
        auto& C=CC[i];
        for(int j:range(R.size())){
            for(int d:range(4)){
                dfs(R[j],C[j],R[j]+dr[d],C[j]+dc[d],bg,ed,0,{},ret,flag);
            }
        }
    }
    if(ret.back()==INF)return;;
    //cerr<<ret.back()<<endl;
    ret.pop_back();
    while(ret.size()){
        int c=ret.back();ret.pop_back();
        int r=ret.back();ret.pop_back();
        up(r,c,bg);
        //cerr<<"("<<r<<","<<c<<")"<<" ";
    }
    //cerr<<endl;
    build(bg,ed,INF,flag);
}

int solve(int INF,int flag,bool db=false){
    int score=0;
    build(7,9,INF,flag);
    //build(4,6);
    vis_clear();

    vector<vector<int>> RR,CC;
    vector<int> V,W;
    for(int i:range(N)){
        for(int j:range(N)){
            vector<int> R,C;
            int w=1;
            int bg,ed;
            if(A[i][j]>=7){
                bg=7,ed=9;
            }
            else if(A[i][j]>=3){
                bg=3,ed=6;
            }
            else{
                bg=1,ed=2;
            }
            count(i,j,bg,ed,R,C,w);
            int mx = bg;
            for(int k:range(R.size())){
                chmax(mx,A[R[k]][C[k]]);
            }

            if(R.size()>=mx){
                RR.push_back(R);
                CC.push_back(C);
                W.push_back(w-(ed-mx)*R.size());
                V.push_back(mx);
                //if(db)cerr << R.front() << " " << C.front() << " " << mx*R.size() << endl;
            }
            else{
                for(int k:range(R.size())){
                    vis[R[k]][C[k]]=0;
                }
            }
        }
    }
    for(int i:range(N)){
        for(int j:range(N)){
            vector<int> R,C;
            int w=1;
            int bg,ed;
            bg=2,ed=9;
            if(A[i][j]==1){
                bg=1,ed=1;
            }
            count(i,j,bg,ed,R,C,w);
            int mx = bg;
            for(int k:range(R.size())){
                chmax(mx,A[R[k]][C[k]]);
            }
            if(R.size()>=mx){
                RR.push_back(R);
                CC.push_back(C);
                W.push_back(w-(ed-mx)*R.size());
                V.push_back(mx);
            }
        }
    }

    for(int i:range(RR.size()+10))for(int j:range(2512))dp[i][j]={-1,-1};
    dp[0][0]={0,-1};
    for(int i:range(RR.size())){
        const int w = W[i];
        const int v = RR[i].size()*V[i];
        for(int j:range(2512)){
            pair<int,int> use = {-1,-1};
            if(j-W[i]>=0)use = {dp[i][j-w].first+v,i};
            dp[i+1][j]=max(dp[i][j],use);
        }
    }
    int opt_i =0,opt_j=0;
    for(int i:range(RR.size()+10)){
        for(int j:range(M-K)){
            if(dp[i][j]>dp[opt_i][opt_j]){
                opt_i=i;
                opt_j=j;
                score = dp[i][j].first;
            }
        }
    }
    queue<int> qR,qC,qS;
    while(1){
        const int last_used = dp[opt_i][opt_j].second;
        if(last_used==-1)break;
        const int w=W[last_used];
        const int ed=V[last_used];
        const int v=ed*RR[last_used].size();
        for(int i:range(RR[last_used].size())){
            const int r=RR[last_used][i];
            const int c=CC[last_used][i];
            up(r,c,ed);
        }
        for(int i:range(1)){
            const int r=RR[last_used][i];
            const int c=CC[last_used][i];
            qR.push(r);
            qC.push(c);
            qS.push(RR[last_used].size()*V[last_used]);
        }
        opt_i=last_used;
        opt_j-=w;
    }
    while(qR.size()){
        gt(qR.front(),qC.front());
        //if(db)cerr << K << ":" << qR.front() << " " << qC.front() <<" "<< qS.front() << endl;
        qR.pop();
        qC.pop();
        qS.pop();
    }
    up(0,0,M);
    return score;
}
int main(){
    input();
    vector<int> ret={0,0};
    for(int i:range(7,14))for(int j:range(2)){
        cl();
        int score = solve(i,j);
        chmax(ret,vector<int>{score,-i,-j});
    }
    cl();
    solve(-ret[1],-ret[2],true);
    cerr<<"argmax:"<<-ret[1]<<" ";
    cerr<<"type:"<<-ret[2]<<" ";
    cerr<<"expected:"<<ret[0]<<endl;
    output();
    return 0;
}
