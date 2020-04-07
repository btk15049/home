//http://codeforces.com/contest/1010/problem/B
#include<bits/stdc++.h>

using namespace std;
typedef long long LL;
#ifdef BTK
#define DEBUG if(1)
#else
#define CIN_ONLY if(0)
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

LL target;
int s[30];
int id=0;
int n;
int t[30];
int local_query(LL pos){
    int ret;
    if(pos==target){
        ret=0;
    }
    else if(pos<target){
        ret=1;
    }
    else {
        ret=-1;
    }
    ret=ret*s[id++];
    id%=n;
    return ret;
}
int cnt=0;
int query(LL pos){
    cout<<pos<<endl;fflush(stdout);
    #ifdef  BTK
        int ret= local_query(pos);
        cnt++;
        cout<<">>"<<cnt<<"th:"<<ret<<endl;
        return ret;
    #else
        int ret;
        cin>>ret;
        return ret;
    #endif
}

int main() {
    LL m;
    cin>>m>>n;
    #ifdef BTK
        cin>>target;
        for(int i:range(n))cin>>s[i];
    #endif
    for(int i:range(n)){
        int ret=query(m-i);
        if(ret==0){return 0;}
        t[i]=-ret;
    }
    LL lb=0,ub=m-n;
    int i=0;
    while(ub-lb>1){
        LL mid=(lb+ub+1)/2;
        int ret=query(mid);
        ret*=t[i++];
        i%=n;
        if(ret==0)return 0;
        if(ret==1)lb=mid;
        else ub=mid-1;
    }
    query(ub);
    return 0;
}
/*
    10000 5
    33
    1 -1 -1 -1 1
*/
