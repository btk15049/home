//
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
int N,M,Q;
int m[112345];
int l[112345];

int need[112345];
int pos[112345];

int main(){
    int N,M;
    cin>>N>>M;
    for(int i:range(M)){
        cin>>m[i];
        m[i]--;
    }
    cin>>Q;
    for(int i:range(Q)){
        cin>>l[i];
    }
    for(int i:range(N)){
        pos[i]=-1e7;
    }

    for(int i:range(M)){
        pos[m[i]]=m[i];
    }
    need[0]=0-pos[0]+1;
    for(int i:range(1,N)){
        pos[i]=max(pos[i],pos[i-1]);
        need[i]=i-pos[i]+1;
    }

    sort(need,need+N);
/*
    for(int i:range(N))cerr<<pos[i]<<",";
    cerr << endl;

    for(int i:range(N))cerr<<need[i]<<",";
    cerr << endl;
*/

    for(int i:range(Q)){
        const int query = l[i];
        int ok=1e6;
        int ng=0;
        if(query<m[0]){
            ok=-1;
        }
        else{
            while(abs(ok-ng)>1){
                const int mid = (ok+ng)/2;
                int sonsitu = need+N-upper_bound(need,need+N,mid);
                if(sonsitu<=query){
                    ok=mid;
                }
                else{
                    ng=mid;
                }
            }
        }
        assert(ok<=112345);
        cout<<ok<<endl;
    }



    return 0;
}