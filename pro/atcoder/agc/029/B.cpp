//https://beta.atcoder.jp/contests/agc029/tasks/agc029_b
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


int main(){
    int N;
    cin>>N;
    int ret=0;
    map<LL,int> cnt;
    for(int i:range(N)){
        LL a;
        cin>>a;
        cnt[a]++;
    }
    LL sum = 1<<30;
    vector<LL> ord;
    for(auto &it:cnt)ord.push_back(it.first);
    //reverse(ALL(ord));
    while(sum>0){
        for(auto &it:ord){
            if(it<sum){
                LL a=it;
                LL b=sum-it;
                if(cnt.count(b)==0)continue;
                int k;
                if(a==b){
                    k = cnt[a]/2;
                }
                else{
                    k = min(cnt[a],cnt[b]);
                }
                cnt[a]-=k;
                cnt[b]-=k;
                ret+=k;
                //cout<<a<<" "<<b<<" "<<k<<endl;
            }
        }
        sum>>=1;
    }
    cout<<ret<<endl;

    return 0;
}