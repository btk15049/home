//https://atcoder.jp/contests/keyence2019/tasks/keyence2019_c
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
    int N;
    cin>>N;
    vector<LL> ok,ng;
    vector<LL> A(N),B(N);
    cin>>A>>B;
    for(int i:range(N)){
        if(B[i]>A[i])ng.push_back(B[i]-A[i]);
        if(A[i]>B[i])ok.push_back(A[i]-B[i]);
    }
    int ret=0;
    LL need=0;
    for(auto &it:ng){
        need+=it;
        ret++;
    }
    sort(ALL(ok));
    reverse(ALL(ok));
    for(auto it:ok){
        if(need<=0){
            cout<<ret<<endl;
            return 0;
        }
        need-=it;
        ret++;
        if(need<=0){
            cout<<ret<<endl;
            return 0;
        }
    }
    cout<<-1<<endl;
    return 0;
}