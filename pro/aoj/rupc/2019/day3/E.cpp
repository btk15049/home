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

template<int base=90001,int mod=999999937>
class RollingHash{
public:
    long long hash;
    long long potential;
    RollingHash(long long hash=0,long long potential=1):hash(hash%mod),potential(potential){}

    inline RollingHash operator+(const RollingHash o)const{
        return RollingHash((hash*o.potential+o.hash)%mod,potential*o.potential%mod);
    }
    inline bool operator==(const RollingHash o)const{
        return hash==o.hash && potential==o.potential;
    }
    class Table{
    private:
        vector<RollingHash> str;
    public:
        Table(){}
        Table(const string s){
            const int n = s.size();
            str.resize(n+1);
            for(int i=0;i<n;i++){
                str[i+1]=str[i]+RollingHash(s[i],base);
            }
        }
        RollingHash substr(int lb,int ub){
            return RollingHash(str[ub].hash-str[lb].hash*str[ub-lb].potential%mod+mod,str[ub-lb].potential);
        }
    };
};

int N;
string T,rT;
bool solve(int len,RollingHash<>::Table& t,RollingHash<>::Table& rt){
    int a=N/(2*(len-1));
    int b=(N-a*2*(len-1))/(len-1);
    int c=N-(a*2+b)*(len-1);
    RollingHash<> A = t.substr(0,len-1)+rt.substr(N-len,N-1);
    RollingHash<> ret;

    while(a){
        if(a%2){
            ret=ret+A;
        }
        a>>=1;
        A=A+A;
    }
    if(b){
        ret=ret+t.substr(0,len-1);
        ret=ret+rt.substr(N-len,N-len+c);
    }
    else{
        ret=ret+t.substr(0,c);
    }
    return ret==t.substr(0,N);
}

int main(){
    cin>>N>>T;
    string rT=T;
    reverse(ALL(rT));
    RollingHash<>::Table t(T);
    RollingHash<>::Table rt(rT);

    for(int i=2;i<=N;i++){
        if(solve(i,t,rt)){
            cout<<i<<endl;
            return 0;
        }
    }
    return 0;
}