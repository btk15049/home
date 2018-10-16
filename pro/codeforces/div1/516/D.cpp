//http://codeforces.com/contest/1063/problem/D
#include<bits/stdc++.h>

using namespace std;
typedef long long LL;

#ifdef BTK
#define DEBUG if(1)
#else
#define CIN_ONLY if(0)
struct cww {cww() {CIN_ONLY{ios::sync_with_stdio(false); cin.tie(0);}}}star;
#define DEBUG if(0)
#endif

#define ALL(v) (v).begin(),(v).end()
#define REC(ret, ...) std::function<ret (__VA_ARGS__)>
template <typename T>inline bool chmin(T &l, T r){bool a = l>r; if (a)l = r; return a;}
template <typename T>inline bool chmax(T &l, T r){bool a = l<r; if (a)l = r; return a;}
template <typename T>istream& operator>>(istream &is, vector<T> &v){for (auto &it : v)is >> it;return is;}

class range {private: struct I { int x; int operator*() { return x; }bool operator!=(I& lhs) { return x<lhs.x; }void operator++() { ++x; } }; I i, n;public:range(int n) :i({ 0 }), n({ n }) {}range(int i, int n) :i({ i }), n({ n }) {}I& begin() { return i; }I& end() { return n; }};
LL calc_rp(LL lp,LL L,LL k,LL l,LL r,LL n){
    return (k - (l+lp))/L-(n+lp);
}
bool isless(LL lp,LL rp,LL L,LL n,LL l,LL r){
    if(lp<0)return true;
    if(rp>r)return true;
    return false;
}
bool isok(LL lp,LL rp,LL L,LL n,LL l,LL r,LL k){
    return (0<=lp&&lp<=l)
            &&(0<=rp&&rp<=r)
            &&((n+lp+rp)*L+(l+lp)==k);
}
LL solve(LL L,LL k,LL l,LL r,LL n){
    LL lp_min = (k-l)%L;
    if(lp_min<0)lp_min+=L;
    LL rp_max = calc_rp(lp_min,L,k,l,r,n);
    if(!isless(lp_min,rp_max,L,n,l,r)){
        if(isok(lp_min,rp_max,L,n,l,r,k)){
            return lp_min + rp_max;
        }
    }
    else{
        LL lb = 0;
        LL ub = l+10;
        while(ub-lb>1){
            const int mid = (lb+ub)/2;
            if(isless(lp_min+L*mid,rp_max-(L+1)*mid,L,n,l,r)){
                lb = mid;
            }
            else{
                ub = mid;
            }
        }
        {
            LL lp = lp_min+L*ub;
            LL rp = rp_max-(L+1)*ub;
            if(isok(lp,rp,L,n,l,r,k)){
                return lp+rp;
            }
        }
    }

    return -2;
}


int main() {
    LL n,l,r,k;
    cin>>n>>l>>r>>k;
    l--;
    r+=n-l;
    r%=n;
    LL ret = -1;
    //cout<<r<<endl;
    if(n<=1123456){
        for(int _s:range(n+1)){
            LL s= _s;
            {
                LL L = k/(n+s);
                LL a = k - L*(n+s)-r;
                LL b = s-a;
                if(isok(a,b,L,n,r,n-r,k)){
                    chmax(ret,s);
                }
            }
            if(r>0){
                LL L = k/(n+s);
                LL a = (k+1) - L*(n+s) - 2 - (r-1);
                LL b = (s-1-a);
                if(isok(a,b,L,n-1,r-1,n-r,k+1-2*(L+1))){
                    chmax(ret,s);
                }
            }
        }
    }
    else{
        if(isok(k-r,n-r,0,n,r,n-r,k)){
            chmax(ret,(k-r)+(n-r));
        }
        if(isok(k-r,n-r,0,n-1,r-1,n-r,k-1)){
            if(r>0)chmax(ret,(k-r)+(n-r)+1);
        }
        for(LL L = 1;L*n<=k;L++){
            chmax(ret,solve(L,k,r,n-r,n));
            if(r>0)chmax(ret,solve(L,k+1-2*(L+1),r-1,n-r,n-1)+1);
            if(L==1&&r==0){
                chmax(ret,solve(L,k+1-2,r,n-r-1,n-1)+1);
            }
        }
    }
    cout<<ret<<endl;
    return 0;
}
