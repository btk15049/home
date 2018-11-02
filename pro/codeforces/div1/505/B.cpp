//http://codeforces.com/contest/1025/problem/B
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

constexpr int M = 1e6;
bool p[M];
LL a[212345];
LL b[212345];
int main(){
    for(int i:range(2,M))p[i]=true;
    for(int i:range(2,M)){
        if(p[i]==false)continue;
        for(int j=i+i;j<M;j+=i)p[j]=false;
    }
    vector<int> x;
    int n;
    cin>>n;
    for(int i:range(n))cin>>a[i]>>b[i];
    {
        LL y = a[0];
        for(int i:range(2,M))if(p[i]&&y%i==0){
            x.push_back(i);y/=i;
            while(y%i==0)y/=i;
        }
        if(y>1)x.push_back(y);
    }
    {
        LL y = b[0];
        for(int i:range(2,M))if(p[i]&&y%i==0){
            x.push_back(i);y/=i;
            while(y%i==0)y/=i;
        }
        if(y>1)x.push_back(y);
    }
    for(auto it:x){
        bool ok=true;
        //cout<<it<<endl;
        for(int i:range(1,n))if(ok){
            if(a[i]%it==0||b[i]%it==0);
            else ok=false;
        }
        if(ok){
            cout<<it<<endl;
            return 0;
        }
    }
    cout<<-1<<endl;
    return 0;
}