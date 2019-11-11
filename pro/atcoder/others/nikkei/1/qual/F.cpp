//https://atcoder.jp/contests/nikkei2019-qual/tasks/nikkei2019_qual_f
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

constexpr LL INF=1e12;
int N,K;
int used[112345];
vector<LL> col[112345];
LL ret[212345];
vector<pair<LL,int>> stone;
void solve(){
    int invalid=0;
    LL sum = 0;
    set<pair<LL,int>> P,Q,R,S,T;
    for(int i:range(N)){
        const int color = stone[i].second/2;
        invalid ^= stone[i].second%2;
        if(stone[i].second%2==1&&invalid==0){
            S.insert({stone[i].first*2,i});
            if(col[color].size()>=3){
                T.insert({stone[i].first*2+col[color][2],i});
            }
        }
    }
    for(int i:range(N)){
        const int color = stone[i].second/2;
        invalid ^= stone[i].second%2;
        //cerr<<i+1<<"th stone is "<< color <<" "<<stone[i].first << " " << stone[i].second%2<<endl;
        if(invalid){
            ret[i+1]=-2;
            LL q=-2,ps=-2,rt=-2;

            if(Q.size())q=sum+Q.rbegin()->first;
            if(P.size()&&S.size())ps=sum-P.begin()->first+S.rbegin()->first;
            if(R.size()&&T.size()){
                //cerr << "r_first= " << R.begin()->first << " ";
                //cerr << "t_last= " << T.rbegin()->first << " ";
                rt=sum-R.begin()->first+T.rbegin()->first;
            }
            ret[i+1]=max({q,ps,rt});
            //cerr << "sum= " << sum   << " ";
            //cerr << "q= " << q   << " ";
            //cerr << "ps= "<< ps  << " ";
            //cerr << "rt= "<< rt  << " ";
            //cerr<<endl;
            sum+=stone[i].first;
        }
        else{
            sum+=stone[i].first;
            ret[i+1]=sum;
        }
        used[color]++;
        if(stone[i].second%2==0){
            P.insert({stone[i].first,i});
            Q.erase({col[color][used[color]-1],color});
        }
        if(used[color]>=2&&used[color]<col[color].size()){
            Q.insert({col[color][used[color]],color});
        }
        if(used[color]==2){
            R.insert({stone[i].first*2,i});
            S.erase({stone[i].first*2,i});
            if(col[color].size()>=3){
                T.erase({stone[i].first*2+col[color][2],i});
            }
        }
    }
}
int main(){
    cin>>N>>K;
    for(int i:range(N)){
        int c;
        LL v;
        cin>>c>>v;
        c--;
        col[c].push_back(v*2);
    }
    for(int i:range(K)){
        sort(ALL(col[i]));
        LL x=0;
        x+=col[i].back();col[i].pop_back();
        x+=col[i].back();col[i].pop_back();
        stone.push_back({x/2,2*i+1});
        stone.push_back({x/2,2*i+1});
        for(LL v:col[i]){
            stone.push_back({v,2*i});
        }
        col[i].push_back(x/2);
        col[i].push_back(x/2);
        reverse(ALL(col[i]));
    }
    sort(ALL(stone));
    reverse(ALL(stone));
    solve();
    for(int i:range(1,N+1)){
        cout<<ret[i]/2<<endl;
    }
    return 0;
}