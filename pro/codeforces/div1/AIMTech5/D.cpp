//http://codeforces.com/contest/1028/problem/D
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

constexpr int mod = 1e9+7;
char buf[10];
int main(){
    int n;
    scanf("%d",&n);
    set<int> buy,sell,btk;
    LL ret = 1;
    buy.insert(-1);
    sell.insert(1e9);
    for(int i:range(n)){
        int p;
        scanf("%s%d",buf,&p);
        if(buf[1]=='D'){
            //ADD
            if(p<*buy.rbegin())buy.insert(p);
            else if(p>*sell.begin())sell.insert(p);
            else btk.insert(p);
        }
        else{
            //ACCEPTED
            if(btk.count(p)){
                ret*=2;
                ret%=mod;
                for(auto q:btk){
                    if(q<p)buy.insert(q);
                    if(q>p)sell.insert(q);
                }
                btk.clear();
            }
            else if(p==*buy.rbegin()){
                buy.erase(p);
                for(auto q:btk)sell.insert(q);
                btk.clear();
            }
            else if(p==*sell.begin()){
                sell.erase(p);
                for(auto q:btk)buy.insert(q);
                btk.clear();
            }
            else{
                printf("0\n");
                return 0;
            }
        }
    }
    ret*=(btk.size()+1);
    ret%=mod;
    printf("%lld\n",ret);

    return 0;
}