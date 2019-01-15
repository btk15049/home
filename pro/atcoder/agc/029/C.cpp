//https://beta.atcoder.jp/contests/agc029/tasks/agc029_c
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
int a[212345];
inline bool solve(const int d){
    vector<pair<int,int>> ret;
    ret.push_back({a[0],1});
    int len = a[0];
    for(int i:range(1,N)){
        if(len<a[i]){
            ret.push_back({a[i]-len,1});
            len=a[i];
        }
        else{
            while(len-ret.back().first>=a[i]){
                len-=ret.back().first;
                ret.pop_back();
            }
            ret.back().first-=len-a[i];
            len=a[i];
            while(ret.size()>1&&ret[ret.size()-1].second==ret[ret.size()-2].second){
                ret[ret.size()-2].first+=ret[ret.size()-1].first;
                ret.pop_back();
            }
            if(ret.size()==1&&ret.back().second==d)return false;
            if(ret.back().second==d){
                auto p = ret.back();
                p.second=1;
                ret.pop_back();
                int k = ret.back().second;
                ret.back().first--;
                if(ret.back().first==0)ret.pop_back();
                ret.push_back({1,k+1});
                ret.push_back(p);
            }
            else{
                int k = ret.back().second;
                ret.back().first--;
                if(ret.back().first==0)ret.pop_back();
                ret.push_back({1,k+1});
            }
        }
    }
    /*
    cout<<d<<" ";
    for(auto &it:ret){
        cout<<"("<<it.first;
        cout<<","<<it.second;
        cout<<")"<<" ";
    }
    cout<<endl;*/
    return true;
}
int main(){
    cin>>N;
    for(int i:range(N))cin>>a[i];
    int lb = 0;
    int ub = N;
    while(ub-lb>1){
        const int mid = (lb+ub)/2;
        if(solve(mid)){
            ub=mid;
        }
        else{
            lb=mid;
        }
    }
    cout<<ub<<endl;
    return 0;
}