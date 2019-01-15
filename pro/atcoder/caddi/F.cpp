//https://caddi2018.contest.atcoder.jp/tasks/caddi2018_d
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

constexpr int mod = 998244353;
LL pow_mod(LL a,LL n,int M=mod){
    LL res=1;
    a%=M;
    while(n){
        if(n&1)
            res=(res*a)%M;
        a=(a*a)%M;
        n>>=1;
    }
    return res;
}

int edge1[112345][2][2];
int edge2[112345][2][2];

int v[112345][2];
map<pair<int,int>,int> pts;
int main(){
    int N,M;
    cin>>N>>M;
    LL x = 0;
    LL y = 0;
    for(int i:range(2,N)){
        x+=y;
        y+=1;
    }
    for(int i:range(N)){
        for(int a:range(2))for(int b:range(2))edge1[i][a][b]=1;
        for(int a:range(2))for(int b:range(2))edge2[i][a][b]=1;

        v[i][0]=v[i][1]=1;
    }
    for(int i:range(M)){
        int a,b,c,aa,bb;
        cin>>a>>b>>c;
        tie(aa,bb)=minmax({a,b});
        if(bb-aa==1){
            if(a<b){
                for(int p:range(2)){
                    edge1[aa][1-c][p]=0;
                }
            }
            else{
                for(int p:range(2)){
                    edge1[aa][p][1-c]=0;
                }
            }
        }
        else if(bb-aa==2){
            if(a<b){
                for(int p:range(2)){
                    edge2[aa+1][1-c][p]=0;
                }
            }
            else{
                for(int p:range(2)){
                    edge2[aa+1][p][1-c]=0;
                }
            }
        }
        else if(bb-aa==0){
            v[aa-1][1-c]=0;
        }
        else{
            if(pts.count({aa,bb})){
                if(pts[{aa,bb}]!=c){
                    cout<<0<<endl;
                    return 0;
                }
            }
            else{
                pts[{aa,bb}]=c;
                x--;
            }
        }
    }
    vector<LL> dp(2,0);
    dp[0]=v[0][0];
    dp[1]=v[0][1];
    for(int i:range(1,N)){
        vector<LL> nxt(2,0);
        for(int cur:range(2))for(int a:range(2))for(int b:range(2))for(int c:range(2)){
            if(edge1[i][a][b]==0)continue;
            if(v[i][c]==0)continue;
            if((cur+a+b+c)&1)continue;
            if(i>=2){
                for(int d:range(2)){
                    for(int e:range(2)) {
                        if(edge2[i][d][e]==0)continue;
                        if((a+b+c+d+e)&1)continue;
                        nxt[c]+=dp[cur];
                    }
                }
            }
            else{
                nxt[c]+=dp[cur];
            }
        }
        nxt[0]%=mod;
        nxt[1]%=mod;
        swap(dp,nxt);
    }
    LL ret=(dp[0]+dp[1])%mod;
    //cout<<x<<endl;
    cout<<ret*pow_mod(2,x)%mod<<endl;
    return 0;
}