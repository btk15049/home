//http://codeforces.com/contest/1041/problem/E
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

int n;
int a[1123];
int b[1123];
vector<int> E[1123];
bool used[1123];
int main() {
    cin>>n;
    
    for(int i:range(n-1)){
        int x,y;
        cin>>x>>y;
        if(y!=n){
            cout<<"NO"<<endl;
            return 0;
        }
        E[x-1].push_back(i);
    }
    for(int i:range(n-1))if(E[i].size())used[i]=true;
    for(int ri:range(n-1)){
        const int i =n-2-ri;
        if(used[i]==false){
            cout<<"NO"<<endl;
            return 0;
        }
        vector<int> v;
        v.push_back(i);
        for(int rj:range(n-1)){
            const int j = n-2-rj;
            if(used[j]==false&&v.size()<E[i].size()){
                used[j]=true;
                v.push_back(j);
            }
        }
        v.push_back(n-1);
        for(int k:range(E[i].size())){
            a[E[i][k]]=v[k]+1;
            b[E[i][k]]=v[k+1]+1;
        }
    }
    cout<<"YES"<<endl;
    for(int i:range(n-1)){
        cout<<a[i]<<" "<<b[i]<<endl;
    }
    return 0;
}
