//https://beta.atcoder.jp/contests/code-festival-2018-final/tasks/code_festival_2018_final_d
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
int N;
vector<int> A[31234];
typedef bitset<52> B;
vector<B> nx[31234];
vector<B> pr[31234];

LL mask[26];
int main(){
    cin>>N;
    for(int i:range(N)){
        string s;
        cin>>s;
        auto& a=A[i];
        for(auto c:s){
            if(islower(c))a.push_back(c-'a'+26);
            else a.push_back(c-'A');
        }
        int n=a.size();
        B nxt_bit;
        vector<B> nxt(n);
        for(int rj:range(n)){
            const int j = n-rj-1;
            nxt[j]=nxt_bit;
            nxt_bit[a[j]]=true;
        }
        nx[i]=nxt;

        B prv_bit;
        vector<B> prv(n);
        for(int j:range(n)){
            prv[j]=prv_bit;
            prv_bit[a[j]]=true;
        }
        pr[i]=prv;
    }
    pair<int,vector<int>> ret(-1,{-100,-100,-100});

    for(int i:range(52))for(int j:range(52)){
        vector<int> num(52,0);
        vector<int> last(52,-1);
        for(int k:range(N)){
            for(int x:range(A[k].size())){
                if(pr[k][x][i]&&nx[k][x][j]&&last[A[k][x]]!=k){
                    last[A[k][x]]=k;
                    num[A[k][x]]++;
                }
            }
        }
        for(int k:range(52)){
            pair<int,vector<int>> ans(num[k],{-i,-k,-j});
            chmax(ret,ans);
        }
    }
    //cout<<ret.first<<endl;
    for(int c:ret.second){
        c*=-1;
        if(c<26)cout<<(char)('A'+c);
        else cout<<(char)('a'+c-26);
    }
    cout<<endl;
    return 0;
}