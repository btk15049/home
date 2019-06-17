//https://atcoder.jp/contests/dp/tasks/dp_z
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



const LL INF = 1e17;


namespace CHT{
using TYPE=LL;
#define A first
#define B second
#define SIZE 1000000
    pair<TYPE,TYPE> mem[SIZE];
    template<typename T>
    inline bool is_minimam(T a1,T b1,T a2,T b2,T a3,T b3){return (a2-a1)*(b3-b2)>=(b2-b1)*(a3-a2);}
    template<typename T>
    inline bool is_maximam(T a1,T b1,T a2,T b2,T a3,T b3){return is_minimam(-a1,-b1,-a2,-b2,-a3,-b3);}
    template<typename T>
    inline bool check(pair<T,T> L1,pair<T,T> L2,pair<T,T> L3){
        return is_minimam(L1.A,L1.B,L2.A,L2.B,L3.A,L3.B);
    }
    template<typename T>
    inline T calc(pair<T,T> L,T now){
        return L.A*now+L.B;
    }
};
template<typename T>
ostream& operator<<(ostream& os,pair<T,T> t){
    os <<"("<< t.first << " "<<t.second << ")";
    return os;
}
#define mp(a,b) std::make_pair(a,b)
template<typename T>
class convex_hull_trick{
    pair<T,T> *deque;
    int s,t;
public:
    convex_hull_trick(pair<T,T> *mem):deque(mem),s(0),t(0){}
    convex_hull_trick():convex_hull_trick(CHT::mem){}
    void add(T a,T b){
        auto L=mp(a,b);
        while(s+1<t&&CHT::check(deque[t-2],deque[t-1],L))t--;
        deque[t++]=L;
    }
    T get(T now){
        while(s+1<t&&CHT::calc(deque[s],now)>=CHT::calc(deque[s+1],now))s++;
        return CHT::calc(deque[s],now);
    }
    void pop(){
        while(s+1<t&&CHT::calc(deque[s])>=CHT::calc(deque[s+1]))s++;
    }
};

int N;
LL C;
LL h[212345];
LL dp[212345];
int main(){
    cin>>N>>C;
    for(int i:range(N))cin>>h[i];
    dp[0]=0;
    convex_hull_trick<LL> deq;
    deq.add(-2*h[0],h[0]*h[0]+dp[0]);
    for(int i:range(1,N)){
        dp[i]=h[i]*h[i]+C+deq.get(h[i]);
        deq.add(-2*h[i],h[i]*h[i]+dp[i]);
    }
    cout<<*max_element(dp,dp+N)<<endl;
    return 0;
}