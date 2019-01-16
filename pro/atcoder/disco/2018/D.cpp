//https://atcoder.jp/contests/ddcc2019-qual/tasks/ddcc2018_qual_d
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

inline LL modulo(LL a, LL m) {
    return (a % m + m) % m;
}

// a x + b y = gcd(a, b)
// O(log (a+b) )
LL extgcd(LL a, LL b, LL &x, LL &y) {
    LL g = a; x = 1; y = 0;
    if (b != 0) g = extgcd(b, a % b, y, x), y -= (a / b) * x;
    return g;
}

// 中国剰余定理
// x%mi = bi から {x%lcm(m),lcm(m)} を求める
// リターン値を (r, m) とすると解は x ≡ r (mod. m)
// 解なしの場合は (0, -1) をリターン
pair<LL, LL> CRT(const vector<LL> &b, const vector<LL> &m) {
  LL r = 0, M = 1;
  for(int i:range(b.size())){
    LL p, q;
    LL d = extgcd(M, m[i], p, q); // p is inv of M/d (mod. m[i]/d)
    if ((b[i] - r) % d != 0) return {0,-1};
    LL tmp = (b[i] - r) / d * p % (m[i]/d);
    r += M * tmp;
    M *= m[i]/d;
  }
  return {(r%M+M)%M, M};
}

int a[32];
bool check(LL x){
    if(x==0||x>(LL)1e12)return false;
    for(int i:range(2,31)){
        LL y=x;
        LL sum=0;
        while(y){
            sum+=y%i;
            y/=i;
        }
        if(sum!=a[i])return false;
    }
    return true;
}
int main(){
    LL x=1;
    for(int i:range(2,31)){
        cin>>a[i];
    }
    vector<LL> b,m;
    for(int i:range(1,30)){
        b.push_back(a[i+1]%i);
        m.push_back(i);
    }
    auto ret=CRT(b,m);
    if(!check(ret.first)){
        cout<<"invalid"<<endl;
    }
    else{
        cout<<ret.first<<endl;
    }
    return 0;
}