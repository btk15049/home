//https://atcoder.jp/contests/arc090/tasks/arc090_b
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

int N,M;
LL pos[112345];
int a[212345];
int b[212345];
LL c[212345];
vector<int> g[112345];
void dfs(int v){
    for(int e:g[v]){
        int u = a[e];
        LL  d = c[e];
        if(v == u){
            u = b[e];
            d = -d;
        }

        if(pos[u]==-1){
            pos[u]=pos[v]+d;
            dfs(u);
        }
        else{
            if(pos[u]!=pos[v]+d){
                cout<<"No"<<endl;
                exit(0);
            }
        }
    }
}
int main(){
    cin >> N >> M;
    for(int i:range(M)){
        cin >>a[i]>>b[i]>>c[i];
        a[i]--;
        b[i]--;
        g[a[i]].push_back(i);
        g[b[i]].push_back(i);
    }
    for(int i:range(N))pos[i]=-1;
    for(int i:range(N)){
        if(pos[i]==-1){
            pos[i]=1e12;
            dfs(i);

        }
    }
    DEBUG cerr << "a" << endl;
    cout<<"Yes"<<endl;
    return 0;
}