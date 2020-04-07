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

int cnt[10][10];
int d[10][10];
int main(){
    int N;
    cin>>N;
    string s;
    cin>>s;
    for(int i:range(N-1)){
        cnt[s[i]-'0'][s[i+1]-'0']++;
    }
    pair<int,vector<int>> ret(912345,vector<int>());
    vector<int> o(9);
    iota(ALL(o),1);
    do{
        for(int i:range(1,10)){
            d[i][i]=0;
            for(int j:range(1,10))d[i][j]=10;
        }
        for(int i:range(6)){
            d[o[i]][o[i+3]]=1;
            d[o[i+3]][o[i]]=1;
        }
        for(int i:range(10)){
            if(i%3){
                d[o[i]][o[i-1]]=1;
                d[o[i-1]][o[i]]=1;
            }
        }
        for(int k:range(1,10))
        for(int i:range(1,10))
        for(int j:range(1,10))
        chmin(d[i][j],d[i][k]+d[k][j]);
        int ans=0;
        for(int i:range(1,10)){
            for(int j:range(1,10)){
                ans+=d[i][j]*cnt[i][j];
            }
        }
        chmin(ret,make_pair(ans,o));
    }while(next_permutation(ALL(o)));
    for(int i:range(3)){
        for(int j:range(3)){
            cout<<ret.second[i*3+j];
        }
        cout<<endl;
    }
    return 0;
}