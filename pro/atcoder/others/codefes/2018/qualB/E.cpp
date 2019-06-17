//https://beta.atcoder.jp/contests/code-festival-2018-qualb/tasks/code_festival_2018_qualb_e
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
vector<int> p,c,pp;
bool isprime[112];
void f(int n){
    for(int i:range(2,n+1)){
        isprime[i]=true;
    }
    for(int i:range(2,n+1)){
        if(isprime[i]){
            p.push_back(i);
            c.push_back(0);
            pp.push_back(1);
            while(pp.back()*i<=n){
                c.back()++;
                pp.back()*=i;
            }
            for(int j=i+i;j<=n;j+=i){
                isprime[j]=false;
            }
        }
    }
}
int cnt[101];
int main() {
    int N;
    cin>>N;
    if(N==1){
        cout<<1<<endl;
        cout<<"+ 1"<<endl;
        return 0;
    }
    f(N);
    int M = p.size();
    vector<pair<int,int>> dec;
    double sum = 0;
    for(int i:range(M)){
        int x=1;
        for(int j:range(M)){
            if(i==j)continue;
            x=x*pp[j]%pp[i];
        }
        int y=0;
        while(y!=1){
            cnt[pp[i]]++;
            y=(y+x)%pp[i];
        }
        dec.push_back({2*cnt[pp[i]]-(pp[i]),pp[i]});
        sum+=(cnt[pp[i]]+0.0)/pp[i];
    }
    sort(ALL(dec));
    while(sum>0.7){
        sum-=1;
        cnt[dec.back().second]-=dec.back().second;
        dec.pop_back();
    }
    int ret=0;
    for(int i:range(1,N+1)){
        ret+=abs(cnt[i]);
    }
    cout<<ret<<endl;
    for(int i:range(1,N+1)){
        if(cnt[i]>0){
            for(int j:range(cnt[i]))cout<<"+ "<<i<<endl;
        }
    }
    for(int i:range(1,N+1)){
        if(cnt[i]<0){
            for(int j:range(-cnt[i]))cout<<"- "<<i<<endl;
        }
    }

    return 0;
}
