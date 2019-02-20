//https://atcoder.jp/contests/yahoo-procon2019-qual/tasks/yahoo_procon2019_qual_d
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

int N;
LL A[212345];
LL AS[212345];
LL ASUM(LL lb,LL ub){
    return AS[ub]-AS[lb];
}
LL dp_o[212345][4];
LL dp_e[212345][4];

int main(){
    cin>>N;
    for(int i:range(N)){
        cin>>A[i];
        AS[i+1]=AS[i]+A[i];
    }
    for(int i:range(N+10))for(int j:range(3))dp_o[i][j]=1e18;
    for(int i:range(N+10))for(int j:range(3))dp_e[i][j]=1e18;
    LL ret=ASUM(0,N);
    for(int i:range(N)){
        if(A[i]==0){
            dp_o[i+1][0]=ASUM(0,i)+1;
            dp_e[i+1][0]=ASUM(0,i)+2;
            for(int j:range(3)){
                chmin(dp_o[i+1][j],dp_o[i][j]+1);
                chmin(dp_e[i+1][j],dp_e[i][j]+2);
            }
            for(int j:range(2)){
                chmin(dp_o[i+1][j+1],dp_e[i][j]+1);
                chmin(dp_e[i+1][j+1],dp_o[i][j]+2);
            }

        }
        else{
            if(A[i]%2==0){
                dp_o[i+1][0]=ASUM(0,i)+1;
                dp_e[i+1][0]=ASUM(0,i);
                for(int j:range(3)){
                    chmin(dp_o[i+1][j],dp_o[i][j]+1);
                    chmin(dp_e[i+1][j],dp_e[i][j]);
                }
                for(int j:range(2)){
                    chmin(dp_o[i+1][j+1],dp_e[i][j]+1);
                    chmin(dp_e[i+1][j+1],dp_o[i][j]);
                }
            }
            else{
                dp_o[i+1][0]=ASUM(0,i);
                dp_e[i+1][0]=ASUM(0,i)+1;

                for(int j:range(3)){
                    chmin(dp_o[i+1][j],dp_o[i][j]);
                    chmin(dp_e[i+1][j],dp_e[i][j]+1);
                }
                for(int j:range(2)){
                    chmin(dp_o[i+1][j+1],dp_e[i][j]);
                    chmin(dp_e[i+1][j+1],dp_o[i][j]+1);
                }
            }
        }
        chmin(ret,dp_o[i+1][0]+ASUM(i+1,N));
        //chmin(ret,dp_o[i+1][2]+ASUM(i+1,N));
        chmin(ret,dp_o[i+1][1]+ASUM(i+1,N));
        chmin(ret,dp_e[i+1][1]+ASUM(i+1,N));
        chmin(ret,dp_e[i+1][0]+ASUM(i+1,N));
        chmin(ret,dp_e[i+1][2]+ASUM(i+1,N));
        /*for(int j:range(3)){
            cout<<dp_o[i+1][j]<<" o ";
        }cout<<endl;
        for(int j:range(3)){
            cout<<dp_e[i+1][j]<<" e ";
        }cout<<endl;
        */

    }
    cout<<ret<<endl;
    return 0;
}