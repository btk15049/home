//http://codeforces.com/contest/1016/problem/D
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

int n,m;

int c[112][112];
int a[112];
int b[112];
#define POS(x,i) ((x>>i)&1)
bool solve(int sh){
    vector<int> A;
    vector<int> B;
    for(int i:range(n)){
        if(POS(a[i],sh))A.push_back(i);
    }
    for(int i:range(m)){
        if(POS(b[i],sh))B.push_back(i);
    }
    if((A.size()+B.size())%2==1){
        //cout<<sh<<" "<<A.size()<<" "<<B.size()<<endl;
        return false;
    }
    while(A.size()>0&&B.size()>0){
        c[A.back()][B.back()]|=(1<<sh);
        A.pop_back();B.pop_back();
    }
    while(A.size()>0){
        c[A.back()][0]|=(1<<sh);
        A.pop_back();
    }
    while(B.size()>0){
        c[0][B.back()]|=(1<<sh);
        B.pop_back();
    }

    return true;
}
void  check(){
    for(int i:range(n)){
        int p=0;
        for(int j:range(m)){
            p^=c[i][j];
        }
        if(a[i]!=p)cout<<"row "<<i<<endl;
    }
    for(int j:range(m)){
        int p=0;
        for(int i:range(n)){
            p^=c[i][j];
        }
        if(b[j]!=p)cout<<"col "<<j<<endl;
    }

}
int main(){
    cin>>n>>m;
    for(int i:range(n))cin>>a[i];
    for(int i:range(m))cin>>b[i];
    bool ok=true;
    for(int i:range(30))ok=ok&solve(i);
    if(ok==false){
        cout<<"NO"<<endl;return 0;
    }
    cout<<"YES"<<endl;
    string sp(m,' ');
    sp.back()='\n';
    check();
    for(int i:range(n))for(int j:range(m)){
        cout<<c[i][j]<<sp[j];
    }
    return 0;
}