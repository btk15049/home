//https://beta.atcoder.jp/contests/code-thanks-festival-2018-open/tasks/code_thanks_festival_2018_g
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
using P=pair<int,int>;
#define A first
#define B second
int N,K;
P ab[5123];
int p[5123];
typedef vector<LL> V;
typedef vector<V> VV;
VV cycle;
constexpr LL INF =1e12;
V f(V& c){
    int H=c.size();
    c.push_back(c[0]);
    V ret(H+1,-INF);
    {
        V dp0(5123,-INF);
        V dp1(5123,-INF);
        dp0[1]=c[0];
        for(int i:range(1,H)){
            V nxt0(5123,-INF);
            V nxt1(5123,-INF);
            for(int j:range(5123)){
                if(dp0[j]>=0){
                    chmax(nxt0[j+1],dp0[j]+c[i]);
                    chmax(nxt1[j+1],dp0[j]+c[i+1]);
                }
                if(dp1[j]>=0){
                    chmax(nxt0[j],dp1[j]+c[i]);
                    chmax(nxt1[j+1],dp1[j]+c[i+1]);
                }
            }
            swap(dp0,nxt0);
            swap(dp1,nxt1);
        }
        for(int i:range(H+1)){
            chmax(ret[i],max(dp0[i],dp1[i+1]));
        }
    }
    {
        V dp0(5123,-INF);
        V dp1(5123,-INF);
        dp1[1]=c[1];
        for(int i:range(1,H)){
            V nxt0(5123,-INF);
            V nxt1(5123,-INF);
            for(int j:range(5123)){
                if(dp0[j]>=0){
                    chmax(nxt0[j+1],dp0[j]+c[i]);
                    chmax(nxt1[j+1],dp0[j]+c[i+1]);
                }
                if(dp1[j]>=0){
                    chmax(nxt0[j],dp1[j]+c[i]);
                    chmax(nxt1[j+1],dp1[j]+c[i+1]);
                }
            }
            swap(dp0,nxt0);
            swap(dp1,nxt1);
        }
        for(int i:range(H+1)){
            chmax(ret[i],max(dp0[i],dp1[i]));
        }
    }
    return ret;
}
int main(){
    cin>>N>>K;
    for(int i:range(N)){
        cin>>ab[i].A>>ab[i].B;
    }
    sort(ab,ab+N);
    for(int i:range(N))p[i]=ab[i].B-1;
    V used(N,0);
    for(int i:range(N)){
        if(used[i])continue;
        int v=i;
        V c;
        while(used[v]==0){
            c.push_back(v);
            used[v]=1;
            v=p[v];
        }
        cycle.push_back(c);
    }
    int cur=1;
    V dp(cur,0);
    for(auto &c:cycle){
        int opo=c.size();
        int nxt_size=cur+opo;
        //for(auto &it:c)cout<<it<<" ";cout<<endl;
        V nxt(nxt_size,-INF);
        auto edge=f(c);
        for(int i:range(cur)){
            for(int j:range(opo+1)){
                chmax(nxt[i+j],dp[i]+edge[j]);
            }
        }
        swap(dp,nxt);
        cur=nxt_size;
    }
    LL ret=-INF;
    for(int k:range(K,N+1))chmax(ret,dp[k]);
    cout<<ret+N<<endl;
    return 0;
}