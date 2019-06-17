//https://atcoder.jp/contests/cf18-relay-open/tasks/relay2018_i
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

int C[10];
int main(){
    int N;
    cin>>N;
    LL sum = 0;
    LL cnt = 0;
    for(int i:range(N)){
        int a;
        cin>>a;
        sum+=a;
        C[a%5]++;
    }
    {
        int k=min(C[3],C[4]);
        C[3]-=k;
        C[4]-=k;
        C[2]+=k;
    }
    {
        int k=C[3]/2;
        C[3]-=k*2;
        C[1]+=k;
    }
    {
        int k=C[4]/3;
        C[4]-=k*3;
        C[2]+=k;
    }
    {
        int k=C[4]/2;
        C[4]-=k*2;
        C[3]+=k;
    }
    for(int i:range(1,3)){
        sum-=i*C[i];
    }
    for(int i:range(3,5)){
        sum+=(5-i)*C[i];
    }
    if(C[3]&&C[2]){
        C[3]--;
        C[2]--;
        C[0]++;
    }
    if(C[3]&&C[1]){
        C[3]--;
        C[1]--;
        C[4]++;
    }
    if(C[4]&&C[1]){
        C[4]--;
        C[1]--;
        C[0]++;
    }
    if(C[4]&&C[2]){
        C[4]--;
        C[2]--;
        C[1]++;
    }
    {
        int k=C[1]/2;
        C[1]-=k*2;
        C[2]+=k;
    }

    if(C[1]||C[2]||C[3]||C[4]){
        C[0]=0;
    }
    else{
        C[0]=1;
    }
    cnt=C[0]+C[1]+C[2]+C[3]+C[4];
    cout<<sum<<" "<<cnt<<endl;
    return 0;
}