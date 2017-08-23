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

typedef vector<int> V;
int main(){
    string s;
    cin>>s;
    int n=s.size();
    reverse(ALL(s));
    V len(26,0);
    V id(26,-1);
    V nxt(n,-1);
    V k(n,0);
    REP(i,n){
        REP(j,26){
            if(len[k[i]]>len[j]){
                k[i]=j;
            }
        }
        nxt[i]=id[k[i]];
        id[s[i]-'a']=i;
        len[s[i]-'a']=len[k[i]]+1;
    }
    int v=0;
    REP(i,26)if(len[v]>len[i])v=i;
    string ret;
    ret+=(char)('a'+v);
    v=id[v];
    
    while(v!=-1){
        DEBUG cout<<v<<endl;
        ret+=(char)('a'+k[v]);
        v=nxt[v];
    }
    cout<<ret<<endl;
    return 0;
}
