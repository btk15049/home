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
int A[N][N];
int B[N][N];
int opt[M];
int opr[M];
int opc[M];
int K = 0;
void input(){
    int n,m;
    cin>>n>>m;
    for(int i:range(N)){
        for(int j:range(N)){
            cin>>A[i][j];
        }
    }
}
void output(){
    for(int i:range(M)){
        cout<<opt[i]<<" "<<opr[i]<<" "<<opc[i]<<endl;
    }
}
void up(int r,int c,int to){
    while(K<2430 && A[r][c]<to){
        opt[K]=1;
        opr[K]=r;
        opc[K]=c;
        K++;
        A[r][c]++;
    }
}
int vis[N][N];
constexpr int dr[]={1,0,-1,0};
constexpr int dc[]={0,-1,0,1};

void count(int r,int c,int num,vector<int>&R,vector<int>&C){
    if(max(r,c)>=N)return;
    if(min(r,c)<0)return;
    if(num>A[r][c])return;
    if(vis[r][c])return;
    vis[r][c]=1;
    R.push_back(r);
    C.push_back(c);
    for(int d:range(4)){
        count(r+dr[d],c+dc[d],num,R,C);
    }
}
void calc(int r,int c,int num,int &ret){
    if(max(r,c)>=N)return;
    if(min(r,c)<0)return;
    if(num!=A[r][c])return;
    if(vis[r][c])return;
    vis[r][c]=1;
    ret++;
    for(int d:range(4)){
        calc(r+dr[d],c+dc[d],num,ret);
    }
}


void solve(){
    vector<pair<int,int>> o;
    vector<vector<int>> RR,CC;

    for(int i:range(N)){
        for(int j:range(N)){
            vector<int> R,C;
            if(A[i][j]>=5){
                count(i,j,5,R,C);
            }
            if(R.size()>=9){
                RR.push_back(R);
                CC.push_back(C);
                o.push_back({-R.size(),RR.size()-1});
            }
        }
    }
    sort(ALL(o));
    for(auto _i:o){
        int i=_i.second;
        for(int p:range(RR[i].size())){
            up(RR[i][p],CC[i][p],9);
        }
    }
    for(int i:range(N))for(int j:range(N))vis[i][j]=0;
    for(int i:!range(1,10)){
        for(int r:range(N)){
            for(int c:range(N))if(A[r][c]==i){
                int cnt =0;
                calc(r,c,A[r][c],cnt);
                if(K<M&&cnt>=A[r][c]){
                    opt[K]=2;
                    opr[K]=r;
                    opc[K]=c;
                    K++;
                }
            }
        }
    }
    while(K<M){
        opt[K]=1;opr[K]=0;opc[K]=0;K++;
    }

}
int main(){
    input();
    solve();
    output();
    return 0;
}