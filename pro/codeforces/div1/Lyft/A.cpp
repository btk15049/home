//http://codeforces.com/contest/1074/problem/A
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

int n,m;
int v[112345];
int h[112345];
int e=0;
int main(){
    int need = 0;
    scanf("%d%d",&n,&m);
    for(int i:range(n)){
        scanf("%d",v+i);
    }
    for(int i:range(m)){
        int r,c1,c2;
        scanf("%d%d%d",&c1,&c2,&r);
        if(c1==1){
            if(c2==1000000000){
                need++;
            }
            else{
                h[e++]=c2;
            }
        }
    }
    if(e==0){
        printf("%d\n",need);return 0;
    }
    sort(h,h+e);
    sort(v,v+n);
    int ret = n;
    for(int i:range(n)){
        int cost = i;
        int wall = v[i];
        if(h[e-1]<wall){
            chmin(ret,cost);
            continue;
        }
        else{
            int ok = -1;
            int ng = e;
            while(ng-ok>1){
                const int mid  =(ok+ng)/2;
                if(h[mid]<wall)ok=mid;
                else ng=mid;
            }
            //printf("i=%d ng=%d\n",i,ng);
            cost+=(e-ng);
            chmin(ret,cost);
        }
    }
    printf("%d\n",need+ret);
    return 0;
}