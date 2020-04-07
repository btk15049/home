//http://codeforces.com/contest/1071/problem/D
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

constexpr int sz= 1000001;
V p[sz];
int l[sz];
constexpr int mx = 8;
V y[300];
map<LL,int> s[300];
vector<pair<LL,int>> t[300];
int M = 0;
map<V,int> x;
int min_cost[300][300];
void latte(){
    iota(l,l+sz,0);
    for(int i:range(2,sz)){
        for(int j=i;j<sz;j+=i){
            if(l[j]%i==0){
                int cnt = 0;
                while(l[j]%i==0){
                    cnt++;
                    l[j]/=i;
                }
                p[j].push_back(cnt);
            }
        }
    }
    for(int i:range(1,sz)){
        sort(ALL(p[i]));
        x[p[i]]++;
    }
    for(auto &it:x){
        it.second=M++;
        y[M-1]=it.first;
    }
    for(int i:range(M)){
        set<V> now;
        now.insert(y[i]);
        map<V,int> dp;
        dp[y[i]]=0;
        for(int j:range(mx)){
            set<V> nxt;
            for(auto it:now){
                for(int k:range(it.size())){
                    V ak = it;
                    ak[k]++;
                    sort(ALL(ak));
                    if(dp.count(ak)==0){
                        dp[ak]=j+1;
                        nxt.insert(ak);
                    }
                }
                for(int k:range(it.size())){
                    V ak = it;
                    ak[k]--;
                    if(ak[k]==0){
                        swap(ak[k],ak.back());
                        ak.pop_back();
                    }
                    sort(ALL(ak));
                    if(dp.count(ak)==0){
                        dp[ak]=j+1;
                        nxt.insert(ak);
                    }
                }
                {
                    V ak = it;
                    ak.push_back(1);
                    sort(ALL(ak));
                    if(dp.count(ak)==0){
                        dp[ak]=j+1;
                        nxt.insert(ak);
                    }
                }
            }
            swap(now,nxt);
        }
        for(auto &it:dp){
            LL p = 1;
            for(auto &prc:it.first){
                p*=(prc+1);
            }
            if(s[i].count(p))chmin(s[i][p],it.second);
            else s[i][p]=it.second;
        }
        for(auto &it:s[i]){
            t[i].push_back({it.first,it.second});
        }
/*
        for(auto it:s[i]){
            printf("(%lld,%d)",it.first,it.second);
        }printf("\n");
        */
    }
    for(int i:range(M)){
        for(int j:range(i,M)){
            min_cost[i][j]=100;
            int ii=0,jj=0;
            while(ii<t[i].size()&&jj<t[j].size()){
                if(t[i][ii].first<t[j][jj].first)ii++;
                else if(t[i][ii].first>t[j][jj].first)jj++;
                else {
                    chmin(min_cost[i][j],t[i][ii].second+t[j][jj].second);
                    ii++;
                    jj++;
                }
            }
            min_cost[j][i]=min_cost[i][j];
        }
    }

}
int main(){
    latte();
    int t;
    cin>>t;
    while(t--){
        int a,b;
        cin>>a>>b;
        auto A = x[p[a]];
        auto B = x[p[b]];
        cout<<min_cost[A][B]<<"\n";
    }
    return 0;
}