//http://codeforces.com/contest/1063/problem/B
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

int R,C;
int sr,sc;
int cr,cc;
using VS=vector<string>;
VS wrap(VS in){
    VS ret(R+2,string(C+2,'*'));
    for(int i:range(R)){
        for(int j:range(C)){
            ret[i+1][j+1]=in[i][j];
        }
    }
    R+=2;
    C+=2;
    return ret;
}

const int dr[]={1,0,-1,0};
const int dc[]={0,1,0,-1};
int d[2123][2123];
int dL[2123][2123];
int dR[2123][2123];
int used[2123][2123];
int cL[]={0,0,0,1};
int cR[]={0,1,0,0};
int main() {
    cin>>R>>C>>sr>>sc>>cr>>cc;
    VS in(R);
    cin>>in;
    in=wrap(in);
    using P=pair<int,int>;
    deque<P> que;
    que.push_front({sr,sc});
    for(int i:range(2123)){
        for(int j:range(2123)){
            d[i][j]=1e8;
        }
    }
    d[sr][sc]=0;
    int ret = 0;
    while(que.size()){
        int r,c;tie(r,c)=que.front();que.pop_front();
        if(used[r][c])continue;
        ret++;
        used[r][c]=1;
        for(int i:range(4)){
            const int nr = r+dr[i];
            const int nc = c+dc[i];
            const int nL = dL[r][c]+cL[i];
            const int nR = dR[r][c]+cR[i];
            if(in[nr][nc]=='*')continue;
            if(nL>cr||nR>cc)continue;
            if(chmin(d[nr][nc],nL+nR)){
                dL[nr][nc]=nL;
                dR[nr][nc]=nR;
                if(nL+nR-d[r][c]==0){
                    que.push_front({nr,nc});
                }
                else{
                    que.push_back({nr,nc});
                }
            }
        }
    }
    cout<<ret<<endl;
    return 0;
}
