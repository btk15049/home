//http://codeforces.com/contest/1036/problem/D
#include<bits/stdc++.h>

using namespace std;
typedef long long LL;

#ifdef BTK
#define DEBUG if(1)
#else
#define CIN_ONLY if(1)
struct cww {cww() {CIN_ONLY{ios::sync_with_stdio(false); cin.tie(0);}}
}star;
#define DEBUG if(0)
#endif

#define ALL(v) (v).begin(),(v).end()
#define REC(ret, ...) std::function<ret (__VA_ARGS__)>
template <typename T>inline bool chmin(T &l, T r){bool a = l>r; if (a)l = r; return a;}
template <typename T>inline bool chmax(T &l, T r){bool a = l<r; if (a)l = r; return a;}
template <typename T>istream& operator>>(istream &is, vector<T> &v){for (auto &it : v)is >> it;return is;}

class range {private: struct I { int x; int operator*() { return x; }bool operator!=(I& lhs) { return x<lhs.x; }void operator++() { ++x; } }; I i, n;public:range(int n) :i({ 0 }), n({ n }) {}range(int i, int n) :i({ i }), n({ n }) {}I& begin() { return i; }I& end() { return n; }};


int a[312345];
int b[312345];
int main() {
    int n,m;
    LL A=0,B=0;
    scanf("%d",&n);
    for(int i:range(n)){
        scanf("%d",a+i);
        A+=a[i];
    }
    scanf("%d",&m);
    for(int i:range(m)){
        scanf("%d",b+i);
        B+=b[i];
    }
    if(A!=B){
        cout<<-1<<endl;return 0;
    }
    int ret=0;
    {
        int i=0,j=0;
        A=0,B=0;
        while(i<n&&j<m){
            if(A==B){
                ret++;
                A+=a[i++];
                B+=b[j++];
            }
            else if(A<B){
                A+=a[i++];
            }
            else{
                B+=b[j++];
            }
        }
    }
    cout<<ret<<endl;
    return 0;
}
