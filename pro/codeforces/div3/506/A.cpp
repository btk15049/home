//http://codeforces.com/contest/1029/problem/A
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
    string s;
    cin>>n>>k;
    cin>>s;
    int p = 0;
    for(int i:range(1,n)){
        int q=0;
        for(int j:range(i,n)){
            if(s[j-i]!=s[j]){
                q=0;
                break;
            }
            else q++;
        }
        chmax(p,q);
    }
    cout<<s;
    for(int i:range(k-1)){
        for(int j:range(p,n))cout<<s[j];
    }
    cout<<endl;
    return 0;
}