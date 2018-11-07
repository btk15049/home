//http://codeforces.com/contest/1006/problem/D
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
    int n;
    int ret=0;
    cin>>n;
    string s,t;
    cin>>s>>t;
    if(n%2==1&&s[n/2]!=t[n/2]){
        ret++;
    }
    int i=0,j=n-1;
    while(i<j){
        map<char,int> x;
        x[s[i]]++;
        x[s[j]]++;
        x[t[i]]++;
        x[t[j]]++;
        if(x.size()==2){
            if(x[s[i]]%2==1)ret++;
        }
        if(x.size()==3){
            if(s[i]==s[j])ret+=2;
            else ret++;
        }
        if(x.size()==4){
            ret+=2;
        }
        i++;j--;
    }
    cout<<ret<<endl;
    return 0;
}