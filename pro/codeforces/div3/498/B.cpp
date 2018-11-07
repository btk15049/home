//http://codeforces.com/contest/1006/problem/B
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
    int n,k;
    cin>>n>>k;
    vector<pair<int,int>> a(n);
    for(int i:range(n)){
        int p;cin>>p;
        a[i]={p,i};
    }
    sort(ALL(a));
    reverse(ALL(a));
    a.resize(k);
    LL sum=0;
    for(auto &it:a){
        sum+=it.first;
        swap(it.first,it.second);
    }
    cout<<sum<<endl;
    sort(ALL(a));
    if(k==1)cout<<n<<endl;
    else {
        cout<<a[1].first;
        for(int i:range(1,k-1)){
            cout<<" "<<a[i+1].first-a[i].first;
        }
        cout<<" "<<n-a.back().first<<endl;
    }
    return 0;
}