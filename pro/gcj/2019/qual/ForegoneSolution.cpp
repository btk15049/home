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

string f(string k){
    size_t ptr = 0;
    while(ptr<k.size()&&k[ptr]=='0'){
        ptr++;
    }
    k=k.substr(ptr);
    if(k.size()==0)k="0";
    return k;
}

void solve(){
    string N;
    cin>>N;
    string A(N.size(),'0'),B(N.size(),'0');
    for(int i:range(N.size())){
        if(N[i]=='4'){
            A[i]=N[i]-1;
            B[i]='1';
        }
        else{
            A[i]=N[i];
        }
    }
    cout << f(A) << " " << f(B) << endl;
}

int main(){
    int T;
    cin >> T;
    for(int i:range(T)){
        cout << "Case #" << i+1 << ": ";
        solve();
    }
    return 0;
}