#include<bits/stdc++.h>
using namespace std;
typedef long long LL;

#define CIN_ONLY if(1)
struct cww{cww(){
    CIN_ONLY{
        ios::sync_with_stdio(false);cin.tie(0);
    }
}}star;
#ifdef BTK
#define DEBUG if(1)
#else
#define DEBUG if(0)
#endif

#define fin "\n"
#define FOR(i,bg,ed) for(int i=(bg);i<(ed);i++)
#define REP(i,n) FOR(i,0,n)
#define ALL(v) (v).begin(),(v).end()
#define fi first
#define se second
#define pb push_back
#define REC(ret, ...) std::function<ret (__VA_ARGS__)>
template <typename T>inline bool chmin(T &l,T r)
{bool a=l>r;if(a)l=r;return a;}
template <typename T>inline bool chmax(T &l,T r)
{bool a=l<r;if(a)l=r;return a;}
template <typename T>
istream& operator>>(istream &is,vector<T> &v){
    for(auto &it:v)is>>it;
    return is;
}
    
int main(){
    int N;
    cin>>N;
    vector<int> v(N);
    cin>>v;
    for(auto &it:v)it--;
    int cnt=0;
    REP(i,N-1){
        if(v[i]==i){
            swap(v[i],v[i+1]);
            cnt++;
        }
    }
    {
        int i=N-2;
        if(v[i+1]==i+1){
            swap(v[i],v[i+1]);
            cnt++;
        }
    }
    cout<<cnt<<endl;

    return 0;
}
