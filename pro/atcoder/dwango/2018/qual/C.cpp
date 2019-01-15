//https://beta.atcoder.jp/contests/dwacon5th-prelims/tasks/dwacon5th_prelims_c
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
string s;
int ms[1123456];
int main(){
    cin>>N;
    cin>>s;
    for(int i:range(N)){
        if(s[i]=='M')ms[i+1]++;
        ms[i+1]+=ms[i];
    }
    int Q;
    cin>>Q;
    while(Q--){
        int k;
        cin>>k;
        LL ret = 0;
        LL tot = 0;
        LL ds = 0;
        for(int i:range(N)){
            if(s[i]=='D'){
                ds++;
            }
            if(s[i]=='M'){
                tot+=ds;
            }
            if(s[i]=='C'){
                ret+=tot;
            }
            if(i-(k-1)>=0&&s[i-(k-1)]=='D'){
                ds--;
                tot-=ms[i+1]-ms[i-(k-1)];
            }
        }
        cout<<ret<<endl;
    }
    return 0;
}