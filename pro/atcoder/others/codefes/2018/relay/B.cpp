//https://atcoder.jp/contests/cf18-relay-open/tasks/relay2018_b
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
class reverse_range {private:struct I {int x;int operator*() {return x-1;}bool operator!=(I& lhs) {return x>lhs.x;}void operator++() {--x;}};I i, n;public:reverse_range(int n) :i({ 0 }), n({ n }){}reverse_range(int i, int n) :i({ i }), n({ n }){}I& begin() {return n;}I& end() {return i;}};
class range {private: struct I { int x; int operator*() { return x; }bool operator!=(I& lhs) { return x<lhs.x; }void operator++() { ++x; } }; I i, n;public:range(int n) :i({ 0 }), n({ n }) {}range(int i, int n) :i({ i }), n({ n }) {}I& begin() { return i; }I& end() { return n; }reverse_range operator!(){return reverse_range(*i,*n);}};


const int dr[]={0,1,0,-1};
const int dc[]={1,0,-1,0};
int o[]={0,1,2,3};
int main(){
    string s;
    cin>>s;
    int gr,gc;
    cin>>gr>>gc;
    bool ok = false;
    do{
        int r=0,c=0;
        for(auto ch:s){
            if(r==gr&&c==gc)ok=true;
            r+=dr[o[ch-'W']];
            c+=dc[o[ch-'W']];
            if(r==gr&&c==gc)ok=true;
        }
        //cout<<r<<" "<<c<<endl;
    }while(next_permutation(o,o+4));
    if(ok)cout<<"Yes"<<endl;
    else cout<<"No"<<endl;
    return 0;
}