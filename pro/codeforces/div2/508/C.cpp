//http://codeforces.com/contest/1038/problem/C
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
int num[26];
int main() {
    int n;
    cin>>n;
    LL diff=0;
    vector<LL> a(n),b(n);
    cin>>a>>b;
    sort(ALL(a));
    sort(ALL(b));
    for(int i:range(n))diff+=a[i];
    for(int i:range(n))diff-=b[i];
    int k=1;
    for(int i:range(2*n)){
        if(b.size()==0){
            a.pop_back();
        }
        else{
            if(a.size()==0||a.back()<b.back()){
                diff+=k*b.back();b.pop_back();
            }
            else{
                a.pop_back();
            }
        }
        swap(a,b);
        k*=-1;
    }
    cout<<diff<<endl;
    return 0;
}

