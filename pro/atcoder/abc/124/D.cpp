//https://atcoder.jp/contests/abc124/tasks/abc124_d
/**
 * @file template.cpp
 * @brief 競技プログラミング用テンプレート
 * @author btk15049
 * @date 2019/03/08
 */
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
#define REC(ret, ...) std::function<ret (__VA_ARGS__)>
template <typename T>inline bool chmin(T &l, T r){bool a = l>r; if (a)l = r; return a;}
template <typename T>inline bool chmax(T &l, T r){bool a = l<r; if (a)l = r; return a;}
template <typename T>istream& operator>>(istream &is, vector<T> &v){for (auto &it : v)is >> it;return is;}
class reverse_range {private:struct I {int x;int operator*() {return x-1;}bool operator!=(I& lhs) {return x>lhs.x;}void operator++() {--x;}};I i, n;public:reverse_range(int n) :i({ 0 }), n({ n }){}reverse_range(int i, int n) :i({ i }), n({ n }){}I& begin() {return n;}I& end() {return i;}};
class range {private: struct I { int x; int operator*() { return x; }bool operator!=(I& lhs) { return x<lhs.x; }void operator++() { ++x; } }; I i, n;public:range(int n) :i({ 0 }), n({ n }) {}range(int i, int n) :i({ i }), n({ n }) {}I& begin() { return i; }I& end() { return n; }reverse_range operator!(){return reverse_range(*i,*n);}};
template<typename T>inline T& unused_var(T& v){return v;}
using LL = long long;

struct I{
    int val,cnt;
};
int main(){
    int N,K;
    vector<I> code;
    cin>>N>>K;
    string s;
    cin>>s;
    for(int i:range(N)){
        const int p = 1-(s[i]-'0');
        if(i==0 || code.back().val != p){
            code.push_back({p,1});
        }
        else{
            code.back().cnt++;
        }
    }
    int ed = 0;
    int have = 0;
    int len = 0;
    int ret=0;
    N=code.size();
    for(int i:range(N)){
        while(ed<N && have+code[ed].val<=K){
            have+=code[ed].val;
            len+=code[ed].cnt;
            ed++;
        }
        chmax(ret,len);

        have-=code[i].val;
        len-=code[i].cnt;
    }
    cout << ret << endl;
}


