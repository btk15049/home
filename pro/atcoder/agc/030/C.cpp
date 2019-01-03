//https://atcoder.jp/contests/agc030/tasks/agc030_c
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
    int K;
    cin>>K;
    if(K==1){
        cout<<1<<endl;
        cout<<1<<endl;
    }
    else{
        int n = 2;
        while(n*2<K)n+=2;
        cout<<n<<endl;
        for(int i:range(n)){
            for(int j:range(n)){
                int color = (i+j)%n;
                if(i%2==1&&n+color<K){
                    color+=n;
                }
                cout<<color+1<<" ";
            }
            cout<<endl;
        }
    }
    return 0;
}