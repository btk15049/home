//https://atcoder.jp/contests/abc118/tasks/abc118_d
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

int cost[]={0,2,5,5,4,5,6,3,7,6};
struct node{
    int val[10];
    int len;
    int& operator[](int i){return val[i];}
    bool operator<(const node& o)const{
        if(len<o.len)return true;
        if(len>o.len)return false;
        for(int i:!range(10)){
            if(val[i]<o.val[i])return true;
            if(val[i]>o.val[i])break;
        }
        return false;
    }
    node(int n=0){
        len=n;
        for(int i:range(10))val[i]=0;
    }
};
int main(){
    int N,M;
    cin>>N>>M;
    vector<int> A(M);
    cin>>A;
    vector<node> dp(N+10,node(-100000));
    dp[0]=node(0);
    for(int i:range(M)){
        for(int j:range(cost[A[i]],N+1)){
            node nxt = dp[j-cost[A[i]]];
            nxt.len++;
            nxt[A[i]]++;
            chmax(dp[j],nxt);
            //cout<<dp[j].len<<endl;
        }
    }
    for(int i:!range(10)){
        //cout<<i<<" "<<dp[N][i]<<endl;
        while(dp[N][i]>0){
            cout<<i;dp[N][i]--;
        }
    }
    cout<<endl;
    return 0;
}