//http://codeforces.com/contest/1076/problem/C
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
    cout<<fixed;
    cout<<setprecision(10);
    int t;
    cin>>t;
    while(t--){
        long double d;
        cin>>d;
        if(d==0.0){
            cout<<"Y 0 0"<<endl;
        }
        else if(d<4){
            cout<<"N"<<endl;
        }
        else{
            long double lb = 2;
            long double ub = 0;
            for(int i:range(1000)){
                long double x=(lb+ub)/2;
                long double y=1/(1-1/x);
                if(x+y<=d){
                    lb=x;
                }
                else{
                    ub=x;
                }
            }
            cout<<"Y "<<lb<<" "<<1/(1-1/lb)<<endl;
        }
    }
    return 0;
}