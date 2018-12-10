//https://beta.atcoder.jp/contests/code-festival-2018-final/tasks/code_festival_2018_final_i
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
LL K;
int A[112345];
LL B[112345];
using V=vector<LL>;
V in[70];
V mg(V a,V b){
    const int n=a.size();
    const int m=b.size();
    V ret(n+m);
    int i=0,j=0;
    while(i<n&&j<m){
        if(a[i]<b[j]){
            ret[i+j]=a[i];
            i++;
        }
        else{
            ret[i+j]=b[j];
            j++;
        }
    }
    while(i<n){
        ret[i+j]=a[i];
        i++;
    }
    while(j<m){
        ret[i+j]=b[j];
        j++;
    }
    return ret;
}

void compress(V& bag){
    int n=bag.size();
    if(n%2==1){
        bag.push_back(0);
        for(int i:range(n)){
            swap(bag[n-i],bag[n-i-1]);
        }
        n++;
    }
    for(int i:range(n/2)){
        bag[i]=bag[2*i]+bag[2*i+1];
    }
    bag.resize(n/2);
}
LL solve(LL x){
    //cout<<x<<endl;
    V bag;
    LL ret=0;
    for(int i:range(70)){
        bag = mg(bag,in[i]);
        if(x&1){
            //cout<<i;
            if(bag.size()>0){
                //cout<<":"<<bag.back();
                ret+=bag.back();
                bag.pop_back();
            }
            //cout<<" ";
        }
        x>>=1;
        compress(bag);
    }
    //cout<<endl<<" "<<ret<<endl;
    return ret;
}
int main(){
    cin>>N>>K;
    for(int i:range(N)){
        cin>>A[i]>>B[i];
        in[A[i]].push_back(B[i]);
    }
    for(int i:range(70)){
        sort(ALL(in[i]));
    }
    LL ng = -1;
    LL ok = 1e6*1e9;
    while(ok-ng>1){
        const LL mid = (ok+ng)/2;
        (solve(mid)>=K?ok:ng)=mid;
    }
    cout<<ok<<endl;

    return 0;
}