//https://atcoder.jp/contests/wupc2019/tasks/wupc2019_g
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
namespace _CumSum_{
    template<class T>
    class CumSum{
    using R = typename iterator_traits<T>::value_type;
    private:
        T ptr;
    public:
        inline R diffs(const int l,const int r)const{
            return *(ptr+r) - *(ptr+l);
        }
        inline R operator[](const int i)const{
            return diffs(i,i+1);
        }
        CumSum(const T bg, const T ed):ptr(bg){
            T pi=bg;
            R tmp=*bg;
            (*bg)=0;
            while(true){
                T pn=pi+1;
                if(pn==ed)break;
                swap(*pn,tmp);
                (*pn)+=(*pi);
                pi=pn;
            }
        }
        CumSum():ptr(nullptr){}
    };
    template<typename T>
    CumSum<T> cum_sum(const T bg, const T ed){
        return CumSum<T>(bg,ed);
    }
}
using namespace _CumSum_;
int N,M;
int a[212345];
LL A[16][212345];
CumSum<LL*> As[16];
LL cost[16][16];
LL dp[1<<16];
int main(){
    cin>>N>>M;
    for(int i:range(M)){
        cin>>a[i];
        A[a[i]][i]++;
    }
    for(int i:range(N))As[i]=cum_sum(A[i],A[i]+M+1);
    for(int i:range(M)){
        for(int k:range(N)){
            cost[a[i]][k]+=As[k].diffs(0,i);
        }
    }
    for(int i:range(1,1<<N))dp[i]=1e16;
    for(int cur:range(1<<N)){
        bitset<16> b(cur);
        for(int j:range(N)){
            if(b[j])continue;
            const int nxt=cur|(1<<j);
            LL c = dp[cur];
            for(int k:range(N)){
                if(j==k||b[k])continue;
                c+=cost[j][k];
            }
            chmin(dp[nxt],c);
        }
    }
    cout<<dp[(1<<N)-1]<<endl;
    return 0;
}