//https://atcoder.jp/contests/wupc2019/tasks/wupc2019_e
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
class reverse_range {private:struct I {int x;int operator*() {return x-1;}bool operator!=(I& lhs) {return x>lhs.x;}void operator++() {--x;}};I i, n;public:reverse_range(int n) :i({ 0 }), n({ n }){}reverse_range(int i, int n) :i({ i }), n({ n }){}I& begin() {return n;}I& end() {return i;}};
class range {private: struct I { int x; int operator*() { return x; }bool operator!=(I& lhs) { return x<lhs.x; }void operator++() { ++x; } }; I i, n;public:range(int n) :i({ 0 }), n({ n }) {}range(int i, int n) :i({ i }), n({ n }) {}I& begin() { return i; }I& end() { return n; }reverse_range operator!(){return reverse_range(*i,*n);}};
using LL = long long;

vector<int> manachar(vector<int> S){
    int i = 0, j = 0;
    vector<int> R(S.size());
    while (i < S.size()) {
      while (i-j >= 0 && i+j < S.size() && S[i-j] == S[i+j]) ++j;
      R[i] = j;
      int k = 1;
      while (i-k >= 0 && i+k < S.size() && k+R[i-k] < j) R[i+k] = R[i-k], ++k;
      i += k; j -= k;
    }
    return R;
}

LL solve(vector<int> v){
    vector<int> u;
    int n = v.size();
    u.push_back(v[0]);
    for(int i:range(1,n)){
        u.push_back(-1);
        u.push_back(v[i]);
    }
    LL ret = 0;
    auto R=manachar(u);
    for(int i:range(n-1)){
        const int l_len = i+1;
        const int r_len = n-l_len;
        const int l_cen = l_len-1;
        const int r_cen = u.size()-r_len;
        if(R[l_cen]>=l_len && R[r_cen]>=r_len)ret++;
    }
    return ret;
}

int main(){
    int R,C;
    cin>>R>>C;
    vector<int> rc(R),cc(C);
    for(int i:range(R)){
        string s;
        cin>>s;
        for(int j:range(C)){
            int a=s[j]-'0';
            rc[i]+=a;
            cc[j]+=a;
        }
    }
    cout<<solve(rc)*solve(cc)<<endl;
    return 0;
}