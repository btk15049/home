//https://beta.atcoder.jp/contests/code-festival-2018-final/tasks/code_festival_2018_final_a
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
int N,M;
int a[112345];
int b[112345];
int c[112345];
vector<int> g[112345];
LL num[111234];
int main(){
    LL ret=0;
    cin>>N>>M;
    for(int i:range(M)){
        cin>>a[i]>>b[i]>>c[i];
        g[a[i]].push_back(i);
        g[b[i]].push_back(i);
    }
    for(int i:range(1,N+1)){
        for(int j:range(1000,2123))num[j]=0;
        sort(ALL(g[i]),[&](int l,int r){
            int lu=i^a[l]^b[l];
            int ru=i^a[r]^b[r];
            return lu<ru;
        });
        for(auto e:g[i]){
            ret+=num[2540-c[e]];
            num[c[e]]++;
        }
        //cout<<ret<<endl;
    }
    cout<<ret<<endl;

    return 0;
}