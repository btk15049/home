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

bool check(string s){
    int ok=0;
    for(auto c:s){
        if(isdigit(c))ok|=1;
        if(islower(c))ok|=2;
        if(isupper(c))ok|=4;
    }
    return ok == 7;
}
string solve(string s){
    const int n = s.size();
    if(check(s))return s;
    for(int i:range(n)){
        string t=s;
        t[i]='a';
        if(check(t))return t;
        t[i]='A';
        if(check(t))return t;
        t[i]='1';
        if(check(t))return t;        
    }
    if(isdigit(s[0])){s[1]='a';s[2]='A';}
    if(islower(s[0])){s[1]='1';s[2]='A';}
    if(isupper(s[0])){s[1]='a';s[2]='1';}
    return s;
}
int main() {
    int n;
    cin>>n;
    while(n--){
        string s;
        cin>>s;
        cout<<solve(s)<<endl;
    }

    return 0;
}
