//https://beta.atcoder.jp/contests/dwacon5th-prelims/tasks/dwacon5th_prelims_a
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

int a[112];
int main(){
    int n;
    cin>>n;
    int ave=0;
    for(int i:range(n)){
        cin>>a[i];
        ave+=a[i];
        a[i]*=n;
    }
    pair<int,int> ret={(int)1e9,0};
    for(int i:range(n)){
        chmin(ret,{abs(a[i]-ave),i});
    }
    cout<<ret.second<<endl;
    return 0;
}