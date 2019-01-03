//https://atcoder.jp/contests/agc030/tasks/agc030_d
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
int N,Q;
int A[3123];
int X[3123];
int Y[3123];
constexpr int mod = 1e9+7;
LL dp[3123][3123];
LL last_update[3123][3123];
LL x[3123];
int main(){
    cin>>N>>Q;
    for(int i:range(N))cin>>A[i];
    for(int i:range(Q)){
        cin>>X[i]>>Y[i];
        X[i]--;
        Y[i]--;
    }
    x[0]=1;
    for(int i:range(3120)){
        x[i+1]=x[i]*2%mod;
    }
    for(int i:range(N)){
        for(int j:range(i+1,N)){
            if(A[i]<A[j]){
                dp[i][j]++;
            }
            if(A[i]>A[j]){
                dp[j][i]++;
            }
        }
    }
    using T=tuple<int,int,LL>;
    queue<T> que;
    for(int q:range(Q)){
        for(int i:range(N)){
            if(i!=X[q]){
                dp[i][Y[q]]=dp[i][Y[q]]*x[q-last_update[i][Y[q]]]%mod;
                last_update[i][Y[q]]=q+1;
                dp[Y[q]][i]=dp[Y[q]][i]*x[q-last_update[Y[q]][i]]%mod;
                last_update[Y[q]][i]=q+1;

                que.push(T(i,X[q],dp[i][Y[q]]));
                que.push(T(X[q],i,dp[Y[q]][i]));
            }
            if(i!=Y[q]){
                dp[i][X[q]]=dp[i][X[q]]*x[q-last_update[i][X[q]]]%mod;
                last_update[i][X[q]]=q+1;
                dp[X[q]][i]=dp[X[q]][i]*x[q-last_update[X[q]][i]]%mod;
                last_update[X[q]][i]=q+1;

                que.push(T(i,Y[q],dp[i][X[q]]));
                que.push(T(Y[q],i,dp[X[q]][i]));
            }
        }
        dp[X[q]][Y[q]]=dp[X[q]][Y[q]]*x[q-last_update[X[q]][Y[q]]]%mod;
        last_update[X[q]][Y[q]]=q+1;
        dp[Y[q]][X[q]]=dp[Y[q]][X[q]]*x[q-last_update[Y[q]][X[q]]]%mod;
        last_update[Y[q]][X[q]]=q+1;
        que.push(T(X[q],Y[q],dp[Y[q]][X[q]]));
        que.push(T(Y[q],X[q],dp[X[q]][Y[q]]));
        while(que.size()){
            int i,j;
            LL p;
            tie(i,j,p)=que.front();
            que.pop();
            dp[i][j]+=p;
            dp[i][j]%=mod;
        }

    }
    LL ret=0;
    for(int i:range(N)){
        for(int j:range(N)){
                dp[i][j]=dp[i][j]*x[Q-last_update[i][j]]%mod;
                if(i>j)ret+=dp[i][j];
        }
    }
    cout<<ret%mod<<endl;
    return 0;
}