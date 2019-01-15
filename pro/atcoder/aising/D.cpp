//https://atcoder.jp/contests/aising2019/tasks/aising2019_d
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

int N,Q;
LL A[112345];
LL X[112345];

LL AS[112345];
LL ASS[112345][2];
bool check(LL x,int l,int r){
    if(l<0)return false;
    return max(abs(x-A[l]),abs(x-A[r-1]))<abs(x-A[r]);
}
int main(){
    cin>>N>>Q;
    for(int i:range(N)){
        cin>>A[i];
        AS[i+1]=AS[i]+A[i];
        ASS[i+1][0]+=ASS[i][0];
        ASS[i+1][1]+=ASS[i][1];
        ASS[i+1][i%2]+=A[i];
    }
    for(int i:range(Q))cin>>X[i];
    for(int i:range(N))A[i]=A[i]*3+1;
    for(int i:range(Q))X[i]=X[i]*3;
    for(int i:range(Q)){
        int lb=0,ub=(N+1)/2+1;
        while(ub-lb>1){
            const int mid = (lb+ub)/2;
            const int r=N-mid;
            const int l=N-mid-mid;
            if(check(X[i],l,r)||check(X[i],l+1,r))lb=mid;
            else ub=mid;
        }
        //cout<<lb<<" ";
        {
            int r=N-lb;
            int l=max(N-lb-lb,0);
            LL first = AS[N]-AS[r];
            LL second = ASS[l][1-N%2];
            cout<<first+second<<endl;
        }
    }
    return 0;
}
