//http://codeforces.com/contest/1066/problem/C
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



int pos[212345];
int main() {
    int Q;
    cin>>Q;
    int lm = 0;
    int rm = 0;
    {
        Q--;
        string t;int id;
        cin>>t>>id;
        pos[id]=0;
    }
    while(Q--){
        string t;int id;
        cin>>t>>id;
        if(t=="L"){
            lm--;
            pos[id]=lm;
        }
        if(t=="R"){
            rm++;
            pos[id]=rm;
        }
        if(t=="?"){
            cout<<min(pos[id]-lm,rm-pos[id])<<endl;;
        }
    }
    return 0;
}
