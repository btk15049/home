//
#include<bits/stdc++.h>
using namespace std;
#define TEMPLATE
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
template<typename T>inline T& unused_var(T& v){return v;}
class reverse_range {private:struct I {int x;int operator*() {return x-1;}bool operator!=(I& lhs) {return x>lhs.x;}void operator++() {--x;}};I i, n;public:reverse_range(int n) :i({ 0 }), n({ n }){}reverse_range(int i, int n) :i({ i }), n({ n }){}I& begin() {return n;}I& end() {return i;}};
class range {private: struct I { int x; int operator*() { return x; }bool operator!=(I& lhs) { return x<lhs.x; }void operator++() { ++x; } }; I i, n;public:range(int n) :i({ 0 }), n({ n }) {}range(int i, int n) :i({ i }), n({ n }) {}I& begin() { return i; }I& end() { return n; }reverse_range operator!(){return reverse_range(*i,*n);}};
using LL = long long;

map<pair<int,int>,vector<int>> ar,ac;
void solve(){
    int R,C;
    cin>>R>>C;
    if(ar.count({R,C})){
        cout<<"POSSIBLE"<<endl;
        vector<int> rr=ar[{R,C}];
        vector<int> cc=ac[{R,C}];
        for(int i:range(R*C)){
            cout<<rr[i]+1<<" "<<cc[i]+1<<endl;
        }
    }
    else{
        cout<<"IMPOSSIBLE"<<endl;
    }
}
int main(){
    //build();return 0;
    ar[make_pair(2,5)]=vector<int>{0,1,0,1,0,1,0,1,0,1};
    ac[make_pair(2,5)]=vector<int>{1,3,0,2,4,1,3,0,2,4};
    ar[make_pair(3,4)]=vector<int>{0,1,2,0,1,2,0,1,2,0,1,2};
    ac[make_pair(3,4)]=vector<int>{0,2,0,1,3,1,2,0,2,3,1,3};
    ar[make_pair(3,5)]=vector<int>{0,1,0,2,0,2,0,1,0,1,2,1,2,1,2};
    ac[make_pair(3,5)]=vector<int>{1,3,0,1,2,3,4,1,3,0,2,4,0,2,4};
    ar[make_pair(4,3)]=vector<int>{1,3,0,2,1,0,2,0,3,1,2,3};
    ac[make_pair(4,3)]=vector<int>{1,0,1,2,0,2,1,0,1,2,0,2};
    ar[make_pair(4,4)]=vector<int>{0,2,1,0,2,0,3,0,1,3,1,2,3,1,2,3};
    ac[make_pair(4,4)]=vector<int>{0,3,1,3,2,1,0,2,0,1,2,0,2,3,1,3};
    ar[make_pair(4,5)]=vector<int>{0,1,0,1,0,1,0,1,0,2,3,1,2,3,2,3,2,3,2,3};
    ac[make_pair(4,5)]=vector<int>{1,3,0,2,4,1,3,0,2,3,1,4,1,3,0,2,4,0,2,4};
    ar[make_pair(5,2)]=vector<int>{1,3,0,2,4,1,3,0,2,4};
    ac[make_pair(5,2)]=vector<int>{0,1,0,1,0,1,0,1,0,1};
    ar[make_pair(5,3)]=vector<int>{0,4,1,3,0,2,0,1,3,1,2,4,2,3,4};
    ac[make_pair(5,3)]=vector<int>{1,0,1,2,0,1,2,0,1,2,0,1,2,0,2};
    ar[make_pair(5,4)]=vector<int>{1,0,1,0,2,0,1,2,0,1,3,4,3,4,2,3,4,2,3,4};
    ac[make_pair(5,4)]=vector<int>{1,3,0,2,1,0,2,0,1,3,2,0,3,1,2,0,2,3,1,3};
    ar[make_pair(5,5)]=vector<int>{0,2,1,0,2,0,1,0,1,0,1,2,1,2,3,4,2,3,4,3,4,3,4,3,4};
    ac[make_pair(5,5)]=vector<int>{2,3,1,3,0,1,3,0,2,4,0,2,4,1,3,1,4,1,3,0,2,4,0,2,4};
    int T;
    cin >> T;
    for(int i:range(T)){
        cout << "Case #" << i+1 << ": ";
        solve();
    }
    return 0;
}
