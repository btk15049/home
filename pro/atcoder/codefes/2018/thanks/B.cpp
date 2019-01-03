//https://beta.atcoder.jp/contests/code-thanks-festival-2018-open/tasks/code_thanks_festival_2018_b
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

string ok="Yes";
string ng="No";
int main(){
    LL x,y;
    cin>>x>>y;
    if(x<y)swap(x,y);
    if((x-y)%2!=0){
        cout<<ng<<endl;return 0;
    }
    LL nd=(x-y)/2;
    if((x-3*nd)%4!=0){
        cout<<ng<<endl;return 0;
    }
    LL a=(x-3*nd)/4;
    if((x-a)%3!=0){
        cout<<ng<<endl;return 0;
    }
    LL b=(x-a)/3;
    //cout<<a<<" "<<b<<endl;
    if(a<0||b<0){
        cout<<ng<<endl;return 0;
    }
    if(a*3+b!=y){
        cout<<ng<<endl;return 0;
    }
    cout<<ok<<endl;
    return 0;
}