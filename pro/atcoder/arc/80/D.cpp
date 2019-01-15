//https://atcoder.jp/contests/arc080/tasks/arc080_b
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
class reverse_range {private:struct I {int x;int operator*() {return x-1;}bool operator!=(I& lhs) {return x>lhs.x;}void operator++() {--x;}};I i, n;public:reverse_range(int n) :i({ 0 }), n({ n }){}reverse_range(int i, int n) :i({ i }), n({ n }){}I& begin() {return n;}I& end() {return i;}};
class range {private: struct I { int x; int operator*() { return x; }bool operator!=(I& lhs) { return x<lhs.x; }void operator++() { ++x; } }; I i, n;public:range(int n) :i({ 0 }), n({ n }) {}range(int i, int n) :i({ i }), n({ n }) {}I& begin() { return i; }I& end() { return n; }reverse_range operator!(){return reverse_range(*i,*n);}};


int b[100][100];
int a[11234];
int main(){
    int R,C,N;
    cin>>R>>C>>N;
    for(int i:range(N)){
        cin>>a[i];
    }
    int id=0;
    for(int i:range(R)){
        if(i%2==0){
            for(int j:range(C)){
                if(a[id]==0)id++;
                a[id]--;
                b[i][j]=id+1;
            }
        }
        else{
            for(int j:!range(C)){
                if(a[id]==0)id++;
                a[id]--;
                b[i][j]=id+1;
            }
        }
    }
    for(int i:range(R)){
        for(int j:range(C)){
            cout<<b[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}