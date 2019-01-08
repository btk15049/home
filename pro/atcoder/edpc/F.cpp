//https://atcoder.jp/contests/dp/tasks/dp_f
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

int dp[3123][3123];
int main(){
    string s,t;
    cin>>s>>t;
    int A=s.size();
    int B=t.size();
    for(int i:range(A+10))for(int j:range(B+10))dp[i][j]=-1000000;
    dp[0][0]=0;
    for(int i:range(3123))dp[i][0]=dp[0][i]=0;
    for(int i:range(A)){
        for(int j:range(B)){
            dp[i+1][j+1]=dp[i][j];
            if(s[i]==t[j])dp[i+1][j+1]++;
            chmax(dp[i+1][j+1],dp[i+1][j]);
            chmax(dp[i+1][j+1],dp[i][j+1]);
        }
    }
    stack<char> st;
    int p=A,q=B;
    while(p>0&&q>0){
        if(s[p-1]==t[q-1]){
            st.push(s[p-1]);
            p--;q--;
        }
        else{
            if(dp[p][q]==dp[p-1][q]){
                p--;
            }
            else if(dp[p][q]==dp[p][q-1]){
                q--;
            }
            else{
                p--;q--;
            }
        }
    }
    while(st.size()){
        cout<<st.top();st.pop();
    }
    cout<<endl;
    return 0;
}