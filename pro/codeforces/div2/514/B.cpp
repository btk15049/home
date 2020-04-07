#include<bits/stdc++.h>

using namespace std;
typedef long long LL;

#ifdef BTK
#define DEBUG if(1)
#else
#define CIN_ONLY if(1)
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



int main() {
    int n,m;
    cin>>n>>m;
    vector<string> s(n),t(n,string(m,'.'));
    cin>>s;
    
    for(int i:range(n-2)){
        for(int j:range(m-2)){
            bool ok=true;
            for(int a:range(3)){
                for(int b:range(3)){
                    if(a==1&&b==1)continue;
                    ok&=(s[i+a][j+b]=='#');
                }
            }
            if(ok){
                for(int a:range(3)){
                    for(int b:range(3)){
                        if(a==1&&b==1)continue;
                        t[i+a][j+b]='#';
                    }
                }
            }
            
        }
    }
    if(s==t)cout<<"YES"<<endl;
    else cout<<"NO"<<endl;
    
    return 0;
}
