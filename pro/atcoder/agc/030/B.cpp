//https://atcoder.jp/contests/agc030/tasks/agc030_b
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
namespace xorshift{
    unsigned yy=1145141919;
    inline unsigned rand(){yy=yy^(yy<<13);yy=yy^(yy>>17);return yy=yy^(yy<<5);}
    constexpr int MASK  = 65535;
    inline int randInt(){return (int) (rand()&MASK);}
    inline double randDouble(){return (rand()&MASK) /(double)MASK;}
}
LL L;
int N;
LL A[512345];
LL dp[50][50][2];
LL naive(){
    for(int i:range(50))
        for(int j:range(50))
            dp[i][j][0]=dp[i][j][1]=0;

    dp[N+1][N+1][0]=0;
    LL ret=0;
    for(int len:range(N)){
        for(int i:range(N+1-len,N+2)){
            const int j = i+len;
            chmax(dp[i-1][j][0],dp[i][j][0]+A[i]-A[i-1]);
            chmax(dp[i-1][j][0],dp[i][j][1]+A[j]-A[i-1]);
            chmax(dp[i][j+1][1],dp[i][j][1]+A[j+1]-A[j]);
            chmax(dp[i][j+1][1],dp[i][j][0]+A[j+1]-A[i]);
        }
    }
    for(int i:range(1,N+2)){
        chmax(ret,dp[i][i+N][0]);
        chmax(ret,dp[i][i+N][1]);
    }
    return ret;
}
LL naive2(){
    LL ret=0;
    for(int i:range(0,N+1)){
        LL ans = A[N+1]-A[N+1-i];
        int pos = 0;
        int l = N+1-i;
        int r = N+1;
        while(r-l<N){
            if(pos==0){
                ans+=A[++r]-A[l];
            }
            else{
                ans+=A[r]-A[--l];
            }
            pos=1-pos;
        }
        chmax(ret,ans);
    }
    for(int i:range(0,N+1)){
        LL ans = -A[N+1]+A[N+1+i];
        int pos = 1;
        int l = N+1;
        int r = N+1+i;
        while(r-l<N){
            if(pos==0){
                ans+=A[++r]-A[l];
            }
            else{
                ans+=A[r]-A[--l];
            }
            pos=1-pos;
        }
        chmax(ret,ans);
    }
    return ret;
}
LL P[512345];
LL PS[512345];
LL PK[512345];
LL B[512345];
LL BS[512345];
LL BK[512345];

LL psum(int i,int j,int k){
    return PS[j]-PS[i]-(PK[i]-k)*(A[j]-A[i]);
}
LL bsum(int i,int j,int k){
    return BS[j]-BS[i]-(BK[j-1]-k)*(A[j]-A[i]);
}
LL solve(){
    LL ret=0;
    for(int i=2*N+1,k=1;i>=0;i--){
        B[i]=(A[i+1]-A[i])*k;
        BK[i]=k;
        k+=2;
    }
    for(int i=0,k=1;i<=2*N+1;i++){
        P[i]=(A[i+1]-A[i])*k;
        PK[i]=k;
        k+=2;
    }
    for(int i:range(2*N+2)){
        PS[i+1]=PS[i]+P[i];
        BS[i+1]=BS[i]+B[i];
    }

    for(int i:range(0,N+1)){
        int l = N+1-i;
        int r = N+1;
        int rest = N-i;
        int lmost = l-rest/2;
        int rmost = r+rest-rest/2;
        LL ans = (A[r]-A[l])*(1+rest);
        if(rest%2==1){
            ans+=psum(lmost,l,2);
            ans+=bsum(r,rmost,1);
        }
        else{
            ans+=psum(lmost,l,1);
            ans+=bsum(r,rmost,2);
        }
        chmax(ret,ans);
    }
    for(int i:range(0,N+1)){
        int l = N+1;
        int r = N+1+i;
        int rest = N-i;
        int lmost = l-rest+rest/2;
        int rmost = r+rest/2;
        LL ans = (A[r]-A[l])*(1+rest);
        if(rest%2==1){
            ans+=psum(lmost,l,1);
            ans+=bsum(r,rmost,2);
        }
        else{
            ans+=psum(lmost,l,2);
            ans+=bsum(r,rmost,1);
        }
        chmax(ret,ans);
    }

    return ret;
}
void init(){
    A[N+1]=L;
    for(int i:range(1,N+1)){
        A[N+1+i] = L+A[i];
    }
    A[2*N+2]=2*L;
}
void gene(){
    L = xorshift::randInt()%500+30;
    N = 20;
    A[0]=0;
    for(int i:range(1,N+1)){
        A[i]=xorshift::randInt()%(L-1)+1;
    }
    sort(A,A+N+2);
}
int main(){

    cin>>L>>N;
    A[0]=0;
    for(int i:range(N)){
        cin>>A[i+1];
    }
    init();
    cout<<solve()<<endl;
    /*
    for(int i:range(10000)){
        gene();
        init();
        if(naive()!=naive2()){
            for(int j:range(N+2)){
                cout<<A[j]<<" ";
            }
            cout<<endl;
            cout<<naive()<<" "<<naive2()<<endl;
            break;
        }
        if(solve()!=naive2()){
            for(int j:range(N+2)){
                cout<<A[j]<<" ";
            }
            cout<<endl;
            cout<<solve()<<" "<<naive2()<<endl;
            break;
        }

    }
    */
    return 0;
}