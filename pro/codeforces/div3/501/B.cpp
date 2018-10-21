//http://codeforces.com/contest/1015/problem/B
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

int o[100];
int used[100];
int pos[100];
int main(){
    int n;
    string s,t;
    cin>>n>>s>>t;
    vector<int> ret;
    for(int i:range(n)){
        bool ok=false;
        for(int j:range(n)){

            if(t[i]==s[j]&&used[j]==0){
                used[j]=1;
                pos[j]=i;
                ok=true;
                break;
            }
        }
        if(ok==false){
            cout<<-1<<endl;
            return 0;
        }
    }
    for(int i:range(n)){
        for(int j=n-1;j>i;j--){
            if(pos[j]<pos[j-1]){
                swap(pos[j],pos[j-1]);
                ret.push_back(j);
            }
        }
    }
    cout<<ret.size()<<endl;
    string sp(ret.size(),' ');
    if(ret.size())sp.back()='\n';
    for(int i:range(ret.size()))cout<<ret[i]<<sp[i];

    return 0;
}