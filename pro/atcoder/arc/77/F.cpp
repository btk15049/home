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
typedef __int128 INT;
typedef vector<LL> V;
typedef vector<V> VV;

V kmp_table_build(string word){
    int n=word.size();
    V table(n+1,0);
    table[0]=-1;
    for(int i=2,j=0;i<=n;){
        if(word[i-1]==word[j])table[i++]=++j;
        else if(j>0)j=table[j];
        else table[i++]=0;
    }
    return table;
}

V f(string s,INT k){
    LL x=s.size();
    V ret(26,0);
    LL loop=k/x;
    for(auto &it:s)ret[it-'a']+=loop;
    k-=loop*x;
    REP(i,k)ret[s[i]-'a']++;
    return ret;
}
V g(string &s1,VV &c,vector<INT> &l,INT k,int id){
    if(k==0)return V(26,0);
    if(id<=1){
        V ret(26,0);
        REP(i,k)ret[s1[i]-'a']++;
        return ret;
    }
    if(l[id-1]<=k){
        V ret=c[id-1];
        V rest=g(s1,c,l,k-l[id-1],id-2);
        REP(i,26)ret[i]+=rest[i];
        return ret;
    }
    else return g(s1,c,l,k,id-1);
}

int main(){
    string s;LL l,r;
    cin>>s>>l>>r;
    LL n=s.size()/2;
    s=s.substr(0,n);
    V table=kmp_table_build(s);
    LL x=n-table[n];
    if(n%x==0){
        s=s.substr(0,x);
        auto a=f(s,r);
        auto b=f(s,l-1);
        REP(i,26)cout<<" "+(!i)<<a[i]-b[i];cout<<endl;
    }
    else{
        VV cnt(128,V(26,0));
        vector<INT> len(128);
        REP(i,n)cnt[0][s[i]-'a']++;
        len[0]=n;
        len[1]=n+x;
        cnt[1]=cnt[0];
        REP(i,x)cnt[1][s[i]-'a']++;
        int id=-1;
        FOR(i,2,128){
            len[i]=len[i-1]+len[i-2];
            //cout<<i<<":"<<(int)len[i]<<endl;
                        
            REP(j,26)cnt[i][j]+=cnt[i-1][j]+cnt[i-2][j];
            if(len[i]>r){
                id=i;
                break;
            }
        }
        s=s+s.substr(0,x);
        auto a=g(s,cnt,len,r,id);
        auto b=g(s,cnt,len,l-1,id);
        REP(i,26)cout<<" "+(!i)<<a[i]-b[i];cout<<endl;
    }
    return 0;
}
