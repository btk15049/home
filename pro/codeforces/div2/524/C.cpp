//http://codeforces.com/contest/1080/problem/C
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

LL R,C;
LL r1,c1,r2,c2;
LL r3,c3,r4,c4;

int in(LL rr,LL cc,LL t,LL b,LL l,LL r){
    return t<=rr&&rr<b&&l<=cc&&cc<r;
}
LL rp[10];
LL cp[10];
int board[10][10];
int main(){
    int t;
    cin>>t;
    while(t--){
        cin>>R>>C;
        cin>>c1>>r1>>c2>>r2;
        cin>>c3>>r3>>c4>>r4;
        r2++;
        c2++;
        r4++;
        c4++;
        int rs=0,cs=0;
        rp[rs++]=r1;
        rp[rs++]=r2;
        rp[rs++]=r3;
        rp[rs++]=r4;
        rp[rs++]=1;
        rp[rs++]=R+1;
        sort(rp,rp+rs);
        rs=unique(rp,rp+rs)-rp;
        cp[cs++]=c1;
        cp[cs++]=c2;
        cp[cs++]=c3;
        cp[cs++]=c4;
        cp[cs++]=1;
        cp[cs++]=C+1;
        sort(cp,cp+cs);
        cs=unique(cp,cp+cs)-cp;
        for(int i:range(rs-1))for(int j:range(cs-1))board[i][j]=-1;
        for(int i:range(rs-1))for(int j:range(cs-1)){
            if(in(rp[i],cp[j],r1,r2,c1,c2)&&
            in(rp[i+1]-1,cp[j],r1,r2,c1,c2)&&
            in(rp[i],cp[j+1]-1,r1,r2,c1,c2)&&
            in(rp[i+1]-1,cp[j+1]-1,r1,r2,c1,c2)){
                board[i][j]=0;
            }
        }
        for(int i:range(rs-1))for(int j:range(cs-1)){
            if(in(rp[i],cp[j],r3,r4,c3,c4)&&
            in(rp[i+1]-1,cp[j],r3,r4,c3,c4)&&
            in(rp[i],cp[j+1]-1,r3,r4,c3,c4)&&
            in(rp[i+1]-1,cp[j+1]-1,r3,r4,c3,c4)){
                board[i][j]=1;
            }
        }
        LL w=0;
        LL b=0;
        for(int i:range(rs-1)){
            for(int j:range(cs-1)){
                LL area=(rp[i+1]-rp[i])*(cp[j+1]-cp[j]);
                if(board[i][j]==-1){
                    w+=area/2;
                    b+=area/2;
                    if(area%2==1){
                        if((rp[i]+cp[j])%2==1){
                            b++;
                        }
                        else{
                            w++;
                        }
                    }
                }
                else{
                    b+=(board[i][j])*area;
                    w+=(1-board[i][j])*area;
                }
            }
        }
        cout<<w<<" "<<b<<endl;
    }
    return 0;
}