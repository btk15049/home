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
    int n;
    cin>>n;
    vector<int> v(n),c(101,0);
    cin>>v;
    for(auto &it:v)c[it]++;
    int x=0,y=0;
    for(auto &it:c){
        if(it ==1)x++;
        if(it > 2)y++;
    }
    string s(n,'B');
    if(x&1){
        if(y==0){
            cout<<"NO"<<endl;
            return 0;
        }
        for(int i:range(n)){
            if(c[v[i]]>2){
                s[i]='A';
                break;
            }
        }
    }
    for(int i:range(n)){
        if(c[v[i]]==1){
            if(x%2==0)s[i]='A';
            x--;
        }
    }
    cout<<"YES"<<endl;
    cout<<s<<endl;

    return 0;
}
