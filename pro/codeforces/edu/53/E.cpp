//http://codeforces.com/contest/1073/problem/E
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

LL allv[1<<10][20];
LL allc[1<<10][20];
constexpr int mod = 998244353;
void all_init(){
    for(int b:range(1<<10)){
        bitset<10> bit(b);
        allv[b][0]=0;
        allc[b][0]=1;
        LL ten = 1;
        for(int i:range(1,20)){
            LL cnt = bit.count();
            LL val = 0;
            for(int j:range(10))if(bit[j]){
                val+=j*ten;
            }
            val%=mod;
            allc[b][i] = allc[b][i-1]*cnt;
            allv[b][i] = allv[b][i-1]*cnt + val*allc[b][i-1];
            allc[b][i] %=mod;
            allv[b][i] %=mod;
            ten*=10;
            ten%=mod;
        }
    }
}
pair<LL,LL> dfs(string s,int pos,int k,bool f=false){
    if(s.size()==pos)return {0ll,1ll};
    bitset<10> bit(k);
    int c=s[pos]-'0';
    LL ret = 0;
    LL cnt = 0;
    LL ten = 1;
    int dep = s.size()-(pos+1);
    for(int i:range(dep))ten=ten*10%mod;
    for(int i:range(c))if(bit[i]){
        LL p = ten*i%mod;
        ret+=p*allc[k][dep]%mod + allv[k][dep];
        cnt+=allc[k][dep];
    }
    for(int i:range(c,c+1))if(bit[i]){
        LL p = ten*i%mod;
        auto ans = dfs(s,pos+1,k);
        ret+=p*ans.second%mod + ans.first;
        cnt+=ans.second;
    }
    return {ret%mod,cnt%mod};
}
LL solve(string s,int k){
    LL ret = 0;
    int dig = s.size();
    bitset<10> b(k);
    LL ten = 1;
    for(int i:range(dig-1)){
        for(int j:range(1,10))if(b[j]){
            LL p = ten*(j)%mod;
            ret+=p*allc[k][i]%mod+allv[k][i];
        }
        ten=ten*10%mod;
    }
    {
        for(int j:range(1,s[0]-'0'))if(b[j]){
            LL p = ten*(j)%mod;
            ret+=p*allc[k][dig-1]%mod+allv[k][dig-1];
        }
        for(int j:range(s[0]-'0',s[0]+1-'0'))if(b[j]){
            LL p = ten*(j)%mod;
            auto ans = dfs(s,1,k);
            ret+=p*ans.second%mod+ans.first;
        }
    }
    return ret%mod;
}
LL dp[1<<10];
int main(){
    all_init();
    LL l,r,k;
    cin>>l>>r>>k;
    LL ret = 0;
    string ub = to_string(r);
    string lb = to_string(l-1);
    for(int i:range(1<<10)){
        dp[i] = (mod+solve(ub,i)-solve(lb,i))%mod;
        //cout<<bitset<10>(i).to_string()<<" "<<solve(ub,i)<<endl;
        for(int j:range(i)){
            if((j|i)==i){
                dp[i]+=mod-dp[j];
            }
        }
        dp[i]%=mod;
        if(bitset<10>(i).count()<=k)ret+=dp[i];
    }
    cout<<ret%mod<<endl;
    return 0;
}