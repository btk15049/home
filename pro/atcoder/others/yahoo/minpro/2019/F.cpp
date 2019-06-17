//https://atcoder.jp/contests/yahoo-procon2019-qual/tasks/yahoo_procon2019_qual_f
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

LL dp[4123][4123];
constexpr int mod =998244353;
LL RS[2123];
int main(){
    string s;
    cin>>s;
    int n=s.size();
    dp[0][0]=1;
    for(int i:range(n)){
        int r=s[i]-'0';
        RS[i+1]=RS[i]+r;
    }
    for(int i:range(1,2*n+1)){
        int rs=RS[min(i,n)];
        int cs=2*min(i,n)-RS[min(i,n)];
        for(int j:range(i+1)){
            int r=j;
            int c=i-j;
            if(r<=rs&&r>0){
                dp[r][c]+=dp[r-1][c];
            }
            if(c<=cs&&c>0){
                dp[r][c]+=dp[r][c-1];
            }
            dp[r][c]%=mod;
        }
    }
    cout<<dp[RS[n]][2*n-RS[n]]<<endl;
    return 0;
}