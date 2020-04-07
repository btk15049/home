//http://codeforces.com/contest/1071/problem/A
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
    LL a,b;
    cin>>a>>b;
    int x = 0;
    while((x+1ll)*(x+2)/2<=a+b)x++;
    vector<int> used(x+1,0);
    vector<int> c,d;
    for(int ri:range(x)){
        const int i = x-ri;
        if(i<=a){
            c.push_back(i);
            a-=i;
        }
        else{
            d.push_back(i);
        }
    }
    cout<<c.size()<<endl;
    for(auto i:c)cout<<i<<" ";
    cout<<endl;
    cout<<d.size()<<endl;
    for(auto i:d)cout<<i<<" ";
    cout<<endl;

    return 0;
}