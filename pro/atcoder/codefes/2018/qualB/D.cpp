//https://atcoder.jp/contests/code-festival-2018-qualb/tasks/code_festival_2018_qualb_d
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
class reverse_range {private:struct I {int x;int operator*() {return x-1;}bool operator!=(I& lhs) {return x>lhs.x;}void operator++() {--x;}};I i, n;public:reverse_range(int n) :i({ 0 }), n({ n }){}reverse_range(int i, int n) :i({ i }), n({ n }){}I& begin() {return n;}I& end() {return i;}};
class range {private: struct I { int x; int operator*() { return x; }bool operator!=(I& lhs) { return x<lhs.x; }void operator++() { ++x; } }; I i, n;public:range(int n) :i({ 0 }), n({ n }) {}range(int i, int n) :i({ i }), n({ n }) {}I& begin() { return i; }I& end() { return n; }reverse_range operator!(){return reverse_range(*i,*n);}};
int N,M;
/*
    le[i][j] : ソート後，[0,i)がx[j]以下で，[i,N)がx[j+1]以上である確率
    le[i][j] = p[0,j+1)^i * p[j+1,M)^(N-i) * N! / {(i)!(N-i)!}
    le[i][j] = e^ { i*log(p[0,j+1)) + (N-i)*log(p[j+1,M)) + log[1,N+1) - log[1,i+1) -log[1,N-i+1)}
*/
double le[2123][2123];
double les[2123][2123];
double e[2123][2123];
LL p[2123];
LL ps[2123];
double q;
LL x[2123];
double li[2123];
double ls[2123];
LL psum(int l,int r){return ps[r]-ps[l];}
double lsum(int l,int r){return ls[r]-ls[l];}
double lesum(int j,int l,int r){return les[r][j]-les[l][j];}


double mul_safe(double a,double b){
    if(a==0)return 0;
    if(b==0)return 0;
    return a*b;
}
double log_safe(double a){
    if(a==0)return 0;
    return log(a);
}

int main(){
    cin>>N>>M>>q;
    cout<<fixed;
    cout<<setprecision(10);

    for(int i:range(M)){
        cin>>x[i]>>p[i];
        ps[i+1]=p[i]+ps[i];
    }
    for(int i:range(1,N+10)){
        li[i]=log(i);
        ls[i+1]=li[i]+ls[i];
        //cout<<i<<" "<<li[i]<<endl;
    }
    for(int i:range(1,N+1)){
        for(int j:range(M)){
            //cout<<"j="<<j<<" "<<psum(j+1,M)<<endl;
            const double in = +mul_safe(i,log_safe(psum(0,j+1)))
                        +mul_safe(N-i,log_safe(psum(j+1,M)))
                        -mul_safe(N,log(q))
                        +lsum(1,N+1)
                        -lsum(1,i+1)
                        -lsum(1,N-i+1);
            if(i<N&&j==M-1)le[i][j]=0;
            else le[i][j] = exp(in);
            les[i+1][j] = les[i][j] + le[i][j];
            //cout<<i<<" "<<j<<" "<<le[i][j]<<endl;
        }
    }
    double ret=0;
    for(int i:range(N)){
        double ans=1e18;
        double topE = 0;
        double topP = 0;
        double botE = 0;
        double botP = 0;

        for(int j:range(M)){
            const double ee = lesum(j,i+1,N+1)-lesum(j-1,i+1,N+1);
            topE+=x[j]*ee;
            topP+=ee;
        }
        for(int j:range(M)){
            const double ee = lesum(j,i+1,N+1)-lesum(j-1,i+1,N+1);
            topE-=x[j]*ee;
            topP-=ee;
            chmin(ans,(topE-topP*x[j])+(botP*x[j]-botE));
            botE+=x[j]*ee;
            botP+=ee;
        }
        ret+=ans;
    }
    cout<<fixed;
    cout<<setprecision(10);
    cout<<ret<<endl;
    return 0;
}