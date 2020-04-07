//http://codeforces.com/contest/1036/problem/E 
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

#define fi first
#define se second
#define pb push_back

#define IL inline 
namespace geo {
    typedef double D;
    typedef bool B;
    typedef complex<D> P;
#define X real()
#define Y imag()
    B comp(const P& l, const P& r){ return (l.X == r.X) ? l.Y < r.Y : l.X < r.X; }
    typedef pair<P, P> L;  //line
    typedef pair<P, P> LS; //line segment
    typedef pair<P, D> C;  //circle
    typedef vector<P> Poly;
    const D EPS = 1e-8;
    //Decompotision Macro
#define DCl(a,b,l) P (a),(b);tie(a,b)=l; 
#define DCc(a,b,c) P (a);D (b);tie(a,b)=c; 
    
    //A dot B
    IL D dot(P a, P b) { return a.X*b.X + a.Y*b.Y; }
    //A cross B
    IL D cross(P a, P b) { return a.X*b.Y - a.Y*b.X; }
    IL D ccw(P a,P b,P c){
        return cross(b - a, c - a);
    }

    IL int sgn(P a,P b, P c){
        if(cross(b-a,c-a) > EPS)return 1;
        if(cross(b-a,c-a) < -EPS)return -1;
        if(dot(b-a,c-a) < -EPS)return 2; // b-a-c
        if(dot(a-b,c-b) < -EPS)return -2; // a-b-c
        return 0;
    }
    IL D signed_distance_P_L(P p, L l) {
        DCl(a,b,l);
        return ccw(a,b,p)/ abs(b - a);
    }
    
    IL D distance_P_L(P p, L l) {
        return abs(signed_distance_P_L(p,l));
    }

    IL D distance_P_LS(P p, LS ls) {
        DCl(a,b,ls);
        if (dot(b - a, p - a) < EPS) return abs(p - a);
        if (dot(a - b, p - b) < EPS) return abs(p - b);
        return abs(cross(b - a, p - a)) / abs(b - a);
    }

    
    IL B is_LS_LS(LS p, LS q) {
        DCl(a,b,p);
        DCl(c,d,q);
        int x=sgn(a,b,c);
        int y=sgn(a,b,d);
        int z=sgn(c,d,a);
        int w=sgn(c,d,b);
        return sgn(a,b,c)*sgn(a,b,d) <= 0
            && sgn(c,d,a)*sgn(c,d,b) <= 0;
    }

    IL D distance_LS_LS(LS p,LS q){
        if(is_LS_LS(p,q))return 0;
        return min({
                distance_P_LS(p.fi,q),
                distance_P_LS(p.se,q),
                distance_P_LS(q.fi,p),
                distance_P_LS(q.se,p)    
                    });
    }

    //caution: have to use isintersected_L_L before this function
    IL P cross_L_L(L p, L q) {
        DCl(a,b,p);
        D d1 = signed_distance_P_L(a, q);
        D d2 = signed_distance_P_L(b, q);
        return (a * d2 - b * d1) / (d2 - d1);
    }
    
}


int n;
LL a[1123];
LL b[1123];
LL c[1123];
LL d[1123];
pair<LL,LL> latte[1123];
LL dx[1123];
LL dy[1123];
LL g[1123];

LL gcd(LL a,LL b){
    return (b==0)?a:gcd(b,a%b);
}
LL get_int_pts(LL x1,LL d,LL ok,LL ng,double target){
    while(ng-ok>1){
        const LL mid = (ok+ng)/2;
        if(x1+mid*d<=target+0.5)ok = mid;
        else ng = mid;
    }
    return ok;
}
int main() {
    int n;
    cin>>n;
    for(int i:range(n)){
        cin>>a[i]>>b[i]>>c[i]>>d[i];
        if(a[i]>c[i]){
            swap(a[i],c[i]);
            swap(b[i],d[i]);
        }
        if(a[i]==c[i]&&b[i]>d[i]){
            swap(b[i],d[i]);
        }
        dx[i]=c[i]-a[i];
        dy[i]=d[i]-b[i];
        g[i] = gcd(dx[i],abs(dy[i]));

    }
    set<pair<LL,LL>> s;
    LL ret=0;
    for(int i:range(n)){
        int malta=0;
        using namespace geo;
        LS p(P(a[i],b[i]),P(c[i],d[i]));
        ret+=g[i]+1;
        for(int j:range(n)){
            if(i!=j){
                LS q(P(a[j],b[j]),P(c[j],d[j]));
                if(is_LS_LS(p,q)){
                    P pt=cross_L_L(p,q);
                    LL ki,kj;
                    if(a[i]<c[i])ki=get_int_pts(a[i],dx[i]/g[i],0,g[i]+1,pt.X);
                    else ki=get_int_pts(b[i],dy[i]/g[i],0,g[i]+1,pt.Y);
                    if(a[j]<c[j])kj=get_int_pts(a[j],dx[j]/g[j],0,g[j]+1,pt.X);
                    else kj=get_int_pts(b[j],dy[j]/g[j],0,g[j]+1,pt.Y);
                    LL x1=a[i]+ki*dx[i]/g[i];
                    LL x2=a[j]+kj*dx[j]/g[j];
                    LL y1=b[i]+ki*dy[i]/g[i];
                    LL y2=b[j]+kj*dy[j]/g[j];
                    if(x1==x2&&y1==y2){
                        latte[malta++]={x1,y1};
                    }
                }
            }
        }
        sort(latte,latte+malta);
        malta=unique(latte,latte+malta)-latte;
        ret-=malta;
        for(int j:range(malta))s.insert(latte[j]);

    }
    cout<<ret+s.size()<<endl;
    return 0;
}