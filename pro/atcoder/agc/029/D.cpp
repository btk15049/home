//https://beta.atcoder.jp/contests/agc029/tasks/agc029_d
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

int R,C,N;
set<pair<int,int>> wall;
int pos[1123456];
int main(){
    cin>>R>>C;
    int ret=R;
    cin>>N;
    for(int i:range(R+10)){
        pos[i]=1e6;
    }
    for(int i:range(N)){
        int r,c;
        cin>>r>>c;
        wall.insert({r,c});
        chmin(pos[r],c);
    }
    for(int i:range(R+2)){
        wall.insert({i,0});
        wall.insert({i,C+1});
    }
    for(int i:range(C+2)){
        wall.insert({0,i});
        wall.insert({R+1,i});
    }
    int cur=1;
    for(int i:range(2,R+1)){
        int r = i-1;
        int c = pos[i];
        //cout<<i<<" "<<cur<<" "<<wall.count({i,cur+1})<<endl;
        if(cur<c);
        else{
        //cout<<r<<" "<<c<<endl;
        chmin(ret,r);
        }
        if(wall.count({i,cur+1})==0)cur++;
    }
    cout<<ret<<endl;
    return 0;
}