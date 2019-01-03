//https://beta.atcoder.jp/contests/tenka1-2018/tasks/tenka1_2018_c
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

using V=vector<LL>;
LL sum(V a){
    int n = a.size();
    LL ret=0;
    for(int i:range(n-1)){
        ret+=abs(a[i]-a[i+1]);
    }
    return ret;
}
int main(){
    int N;
    cin>>N;
    V a(N);
    cin>>a;
    sort(ALL(a));
    V argret=a;
    if(N%2==0){
        for(int i:range(N)){
            if(i<N/2){
                argret[i*2+1]=a[i];
            }
            else{
                int id = i-N/2;
                argret[id*2]=a[i];
            }
        }
        //for(int i:range(N))cout<<argret[i]<<endl;
    }
    else{
        {
            V p,m;
            for(int i:range(N/2)){
                m.push_back(a[i]);
            }
            for(int i:range(N/2,N)){
                p.push_back(a[i]);
            }
            swap(p[1],p.back());
            V x;
            for(int i:range(N/2)){
                x.push_back(p[i]);
                x.push_back(m[i]);
            }
            x.push_back(p.back());
            if(sum(argret)<sum(x))argret=x;
        }
        {
            V p,m;
            for(int i:range(N/2+1)){
                m.push_back(a[i]);
            }
            for(int i:range(N/2+1,N)){
                p.push_back(a[i]);
            }
            swap(m.front(),m[m.size()-2]);
            V x;
            for(int i:range(N/2)){
                x.push_back(m[i]);
                x.push_back(p[i]);
            }
            x.push_back(m.back());
            if(sum(argret)<sum(x))argret=x;
        }
    }

    cout<<sum(argret)<<endl;
    return 0;
}