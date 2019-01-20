//https://atcoder.jp/contests/abc116/tasks/abc116_d
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
int N,K;
int t[112345];
LL d[112345];
int o[112345];
int used[112345];
int main(){
    cin>>N>>K;
    for(int i:range(N)){
        cin>>t[i]>>d[i];
        t[i]--;
    }
    iota(o,o+N,0);
    sort(o,o+N,[&](int l,int r){return d[l]<d[r];});
    reverse(o,o+N);
    LL use = 0;
    LL sum = 0;
    stack<LL> x;
    for(int _i:range(K)){
        int i=o[_i];
        if(used[t[i]])x.push(d[i]);
        else {
            used[t[i]]=1;
            use++;
        }
        sum+=d[i];
    }
    LL ret=use*use+sum;
    for(int _i:range(K,N)){
        if(x.empty())break;
        int i=o[_i];
        if(used[t[i]])continue;
        used[t[i]]=1;
        use++;
        sum+=d[i];
        sum-=x.top();
        x.pop();
        chmax(ret,use*use+sum);
    }
    cout<<ret<<endl;
    return 0;
}