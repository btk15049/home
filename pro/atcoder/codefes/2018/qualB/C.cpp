//https://beta.atcoder.jp/contests/code-festival-2018-qualb/tasks/code_festival_2018_qualb_c
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

int a[1123][1123];
int b[1123][1123];
int dr[]={2,-1,-2,1};
int dc[]={1,2,-1,-2};
int sr[]={1,-1,0,0,0};
int sc[]={0,0,-1,1,0};

int main() {
    int N;
    cin>>N;
    using P=pair<int,int>;
    queue<P> que;
    a[0][0]=1;
    que.push({0,0});
    while(que.size()){
        int r,c;
        tie(r,c)=que.front();
        que.pop();
        for(int i:range(5)){
            int nr = r+sr[i];
            int nc = c+sc[i];
            if(nr<0||nc<0)continue;
            if(nr>=N||nc>=N)continue;
            b[nr][nc]=1;
        }
        for(int i:range(4)){
            int nr = r+dr[i];
            int nc = c+dc[i];
            if(nr<0||nc<0)continue;
            if(nr>=N||nc>=N)continue;
            if(a[nr][nc])continue;
            que.push({nr,nc});
            a[nr][nc]=1;
        }
    }
    string x=".X";
    int cnt = 0;
    for(int i:range(N))for(int j:range(N))if(b[i][j]==0)a[i][j]=1;
    for(int i:range(N)){
        for(int j:range(N)){
            cout<<x[a[i][j]];
            cnt+=a[i][j];
        }
        cout<<endl;
    }
    DEBUG cout<<cnt<<endl;
    return 0;
}
