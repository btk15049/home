//http://codeforces.com/contest/1038/problem/B
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
    LL S=0;
    for(int i:range(n))S+=i+1;
    for(int i=2;i*i<=S;i++){
        if(S%i==0){
            vector<int> x,y;
            x.push_back(i);
            for(int j:range(1,n+1))if(i!=j)y.push_back(j);
            cout<<"Yes"<<endl;
            string s(x.size(),' ');
            string t(y.size(),' ');
            s.back()='\n';
            t.back()='\n';
            cout<<x.size()<<" ";
            for(int j:range(x.size()))cout<<x[j]<<s[j];
            cout<<y.size()<<" ";
            for(int j:range(y.size()))cout<<y[j]<<t[j];
            return 0;
        }
    }
    cout<<"No"<<endl;
    return 0;
}

