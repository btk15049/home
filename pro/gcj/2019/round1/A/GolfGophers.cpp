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

int N,M;
int f(int mod = 2){
    for(int i:range(18)){
        cout << mod << " ";
    }
    cout << endl;
    cout.flush();
    int ret=0;
    for(int i:range(18)){
        int a;
        cin >> a;
        ret+=a;
    }
    return ret%mod;
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
  for(int i=0;i<(int)b.size();i++){
    LL p, q;
    LL d = extgcd(M, m[i], p, q); // p is inv of M/d (mod. m[i]/d)
    if ((b[i] - r) % d != 0) return {0,-1};
    LL tmp = (b[i] - r) / d * p % (m[i]/d);
    r += M * tmp;
    M *= m[i]/d;
  }
  return {(r%M+M)%M, M};
}

void solve(){
    vector<LL> b,m;
    for(int mod:{16,9,5,7,11,13,17}){
        b.push_back(f(mod));
        m.push_back(mod);
    }
    LL ans = CRT(b,m).first;
    /*
    for(int i:range(N-7)){
        unused_var(i);
        f();
    }
    */
    cout << ans << endl;
    cout.flush();
    int jud;
    cin >> jud;
    DEBUG cerr << jud << endl;
}
int main(){
    int T;
    cin >> T>>N>>M;
    DEBUG cerr << T <<" " <<N <<" "<< M << endl;
    for(int i:range(T)){
        solve();
    }
    return 0;
}