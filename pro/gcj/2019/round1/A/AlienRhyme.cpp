//
#include<bits/stdc++.h>
using namespace std;
#define TEMPLATE
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
template<typename T>inline T& unused_var(T& v){return v;}
class reverse_range {private:struct I {int x;int operator*() {return x-1;}bool operator!=(I& lhs) {return x>lhs.x;}void operator++() {--x;}};I i, n;public:reverse_range(int n) :i({ 0 }), n({ n }){}reverse_range(int i, int n) :i({ i }), n({ n }){}I& begin() {return n;}I& end() {return i;}};
class range {private: struct I { int x; int operator*() { return x; }bool operator!=(I& lhs) { return x<lhs.x; }void operator++() { ++x; } }; I i, n;public:range(int n) :i({ 0 }), n({ n }) {}range(int i, int n) :i({ i }), n({ n }) {}I& begin() { return i; }I& end() { return n; }reverse_range operator!(){return reverse_range(*i,*n);}};
using LL = long long;

namespace trie{
    struct node{
        int nxt[26];
        int cnt;
        node(){
            cnt=0;
            for(int i:range(26))nxt[i]=-1;
        }
    }t[112345];
    int size=0;
    int cr(){
        t[size++]=node();
        return size-1;
    }
    void init(){
        size=0;
        cr();
    }
    void ins(string s){
        int p=0;
        for(char c:s){
            int& np=t[p].nxt[c-'A'];
            if(np==-1)np=cr();
            p=np;
        }
        t[p].cnt++;
    }
    int dfs(int v,int &ret){
        for(int i:range(26)){
            if(t[v].nxt[i]!=-1){
                t[v].cnt+=dfs(t[v].nxt[i],ret);
            }
        }
        if(v&&t[v].cnt>=2){
            ret+=2;
            t[v].cnt-=2;
        }
        return t[v].cnt;
    }
}
void solve(){
    trie::init();
    int N;
    cin>>N;
    for(int i:range(N)){
        string s;
        cin>>s;
        reverse(ALL(s));
        trie::ins(s);
    }
    int ret=0;
    trie::dfs(0,ret);
    cout<<ret<<endl;
}
int main(){
    int T;
    cin >> T;
    for(int i:range(T)){
        cout << "Case #" << i+1 << ": ";
        solve();
    }
    return 0;
}
