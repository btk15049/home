//https://beta.atcoder.jp/contests/dwacon5th-prelims/tasks/dwacon5th_prelims_d
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
int N;
int D;
int cnt[1123][1123];
int B[2123][2123];
int C[2123][2123];
bool f(int r){
    //cout<<(r/D)*(LL)(r/D)<<endl;
    for(int i:range(D)){
        for(int j:range(D)){
            bool ok=true;
            for(int s:range(D)){
                for(int t:range(D)){
                    int ni=(i+s)%D;
                    int nj=(j+t)%D;
                    LL rc=r/D;
                    if(ni<r-rc*D)rc++;
                    LL cc=r/D;
                    if(nj<r-cc*D)cc++;
                    if(rc*cc<cnt[s][t]){
                        ok=false;
                    }
                }
            }
            if(ok)return true;
        }
    }
    return false;
}
bool ff(int r){

    LL a=(r/D)*(LL)(r/D);
    LL b=(r/D)*(LL)(r/D+1);
    LL c=(r/D+1)*(LL)(r/D+1);
    int md=r%D;
    int sum=0;
    for(int i:range(D))for(int j:range(D)){
        B[i+1][j+1]=B[i+1+D][j+1]=B[i+1][j+1+D]=B[i+1+D][j+1+D]=0;
        C[i+1][j+1]=C[i+1+D][j+1]=C[i+1][j+1+D]=C[i+1+D][j+1+D]=0;

        if(cnt[i][j]>c)return false;
        if(cnt[i][j]<=a)continue;
        sum++;
        if(cnt[i][j]<=b){
            B[i+1][j+1]=B[i+1+D][j+1]=B[i+1][j+1+D]=B[i+1+D][j+1+D]=1;
        }
        if(cnt[i][j]<=c){
            C[i+1][j+1]=C[i+1+D][j+1]=C[i+1][j+1+D]=C[i+1+D][j+1+D]=1;
        }
    }
    for(int i:range(2*D))for(int j:range(2*D)){
        B[i+1][j+1]+=B[i+1][j]+B[i][j+1]-B[i][j];
        C[i+1][j+1]+=C[i+1][j]+C[i][j+1]-C[i][j];
    }
    for(int i:range(D))for(int j:range(D)){
        int k = 0;
        k+= C[i+md][j+md]-C[i][j+md]-C[i+md][j]+C[i][j];
        k+= B[i+md][j+D]-B[i][j+D]-B[i+md][j+md]+B[i][j+md];
        k+= B[i+D][j+md]-B[i+md][j+md]-B[i+D][j]+B[i+md][j];
        if(k==sum)return true;
    }
    return false;
}
int main(){
    cin>>N>>D;
    //if(D>30)return -1;
    for(int i:range(N)){
        int x,y;
        cin>>x>>y;
        cnt[x%D][y%D]++;
    }
    int lb=0,ub=1e7;
    while(ub-lb>1){
        const int mid=(lb+ub)/2;
        if(ff(mid))ub=mid;
        else lb=mid;
    }
    cout<<lb<<endl;
    return 0;
}