//http://codeforces.com/contest/1074/problem/D
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

namespace UF{
    map<int,int> rank,par,diff;
    int _find(int x){
        int prv_par = par[x];
        if (prv_par == x) return x;
        else {
            int nxt_par = _find(par[x]);
            int prv_diff = diff[x];
            diff[x] = diff[prv_par]^prv_diff;
            return par[x] = nxt_par;
        }
    }
    int find(int x){
        if(par.count(x)==0){
            par[x]=x;
            rank[x]=0;
            diff[x]=0;
        }
        return _find(x);
    }
    bool unite(int x, int y, int d){
        int rx = find(x);
        int ry = find(y);
        d = d^diff[x]^diff[y];
        if(rx==ry){
            return d==0;
        }
        x=rx;y=ry;
	    if (rank[x] < rank[y])swap(x,y);
        par[y] = x;
        diff[y]=d;
        if (rank[x] == rank[y])rank[x]++;
	    return true;
    }
    int get(int x,int y){
        int rx = find(x);
        int ry = find(y);
        if(rx!=ry)return -1;
        else return diff[x]^diff[y];
    }
}




int main(){
    int q;
    scanf("%d",&q);
    int last=0;
    for(int i:range(q)){
        //printf("(last=%d):",last);
        int t;
        scanf("%d",&t);
        if(t==2){
            int l,r;
            scanf("%d%d",&l,&r);
            l=l^last;
            r=r^last;
            if(l>r)swap(l,r);
            r++;
            int ret = UF::get(l,r);
            //printf("get %d %d\n",l,r-1);
            printf("%d\n",ret);
            if(ret==-1)ret=1;
            last=ret;
        }
        else{
            int l,r,d;
            scanf("%d%d%d",&l,&r,&d);
            l=l^last;
            r=r^last;
            if(l>r)swap(l,r);
            r++;
            d=d^last;
            //printf("add %d %d %d\n",l,r-1,d);

            UF::unite(l,r,d);
        }
    }
    return 0;
}

