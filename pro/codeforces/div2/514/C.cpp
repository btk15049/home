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

int ret[1123456];
void f(int bg,int ed,int g){
    if(bg==ed)return;
    if(ed-bg<=3){
        for(int i:range(ed-bg-1))ret[bg+i]=g;
        ret[ed-1]=g*(ed-bg);
        return;
    }
    int rest = (ed-bg+1)/2;
    for(int i:range(rest)){
        ret[bg++]=g;
    }
    f(bg,ed,g*2);
}
int main() {
    int n;
    scanf("%d",&n);
    f(0,n,1);

    string sp(n,' ');
    sp.back()='\n';
    for(int i:range(n))cout<<ret[i]<<sp[i];
    return 0;
}
