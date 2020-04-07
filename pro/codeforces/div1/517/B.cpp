//http://codeforces.com/contest/1071/problem/B
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

int cnt[2123][2123];
int dr[2]={0,1};
int dc[2]={1,0};

int main(){
    int n,k;
    cin>>n>>k;
    char cw = 'z'+1;
    string ret(2*n-1,cw);
    chmin(k,2*n-1);
    vector<string> s(n);
    cin>>s;
    for(int i:range(n))for(int j:range(n)){
        cnt[i][j]=-1;
    }
    cnt[0][0]=k;
    ret[0]=s[0][0];
    if(s[0][0]!='a'&&k>0){
        cnt[0][0]--;
        ret[0]='a';
    }
    for(int i:range(0,2*n-2)){
        for(int r:range(n)){
            int c = i-r;
            if(c<0||c>=n)continue;
            if(cnt[r][c]<0)continue;
            for(int j:range(2)){
                int nr = r + dr[j];
                int nc = c + dc[j];
                if(nr>=n||nc>=n)continue;
                char nxt = s[nr][nc];
                int nxt_cost = cnt[r][c];
                if(cnt[r][c]>0&&nxt!='a'){
                    nxt='a';
                    nxt_cost--;
                }
                chmin(ret[i+1],nxt);
            }
        }
        for(int r:range(n)){
            int c = i-r;
            if(c<0||c>=n)continue;
            if(cnt[r][c]<0)continue;
            for(int j:range(2)){
                int nr = r + dr[j];
                int nc = c + dc[j];
                if(nr>=n||nc>=n)continue;
                char nxt = s[nr][nc];
                int nxt_cost = cnt[r][c];
                if(cnt[r][c]>0&&nxt!='a'){
                    nxt='a';
                    nxt_cost--;
                }
                if(ret[i+1]==nxt){
                    chmax(cnt[nr][nc],nxt_cost);
                }
            }
        }
    }
    cout<<ret<<endl;
    return 0;
}