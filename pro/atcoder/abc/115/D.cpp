//https://beta.atcoder.jp/contests/abc115/tasks/abc115_d
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

int N;
LL X;
LL sum[100];
LL niku[100];
int main(){
    cin>>N>>X;
    sum[0]=1;
    niku[0]=1;
    for(int i:range(1,60)){
        sum[i]=3+2*sum[i-1];
        niku[i]=1+2*niku[i-1];
    }
    LL ret=0;
    while(N>=0){
        if(X<=1){
            break;
        }
        else if(X<2+sum[N-1]){
            N--;
            X--;
        }
        else if(X<sum[N]){
            ret+=1+niku[N-1];
            X-=2+sum[N-1];
            N--;
        }
        else{
            ret+=niku[N];
            X=0;
            break;
        }
    }
    if(N==0&&X==1)ret++;
    cout<<ret<<endl;
    return 0;
}