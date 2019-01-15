//https://caddi2018.contest.atcoder.jp/tasks/caddi2018_a
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
    LL N;
    LL P;
    cin>>N>>P;
    if(N==1){
        cout<<P<<endl;
        return 0;
    }
    LL ret=1;
    for(int i:range(2,1123456)){
        if(P%i==0){
            int cnt=0;
            while(P%i==0){
                P/=i;
                cnt++;
            }
            cnt/=N;
            for(int j:range(cnt)){
                ret*=i;
            }
        }
    }
    cout<<ret<<endl;
    return 0;
}