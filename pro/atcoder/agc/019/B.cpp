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
struct PalindromicTree {
    struct node {
        map<char,int> next;
        int len, sufflink,num,first;
    };
    string S;
    vector<node> V;
    int n,s; // num,suff
	
    bool add(int pos) {
        char ch=S[pos];
        int c=s, cl=0;
        while(1) {
            cl=V[c].len;
            if(pos-1-cl>=0 && S[pos-1-cl]==ch) break;
            c=V[c].sufflink;
        }
		
        if(V[c].next.count(ch)) {
            s = V[c].next[ch];
            return false;
        }
		
        s=++n;
        V[n].len=V[c].len+2;
        V[n].first=pos;
        V[c].next[ch]=n;
		
        if(V[n].len==1) { // even length
            V[n].sufflink=2;
            V[n].num=1;
            return true;
        }
		
        while(1) {
            c=V[c].sufflink;
            cl=V[c].len;
            if(pos-1-cl>=0 && S[pos-1-cl]==ch) {
                V[n].sufflink=V[c].next[ch];
                break;
            }
        }
        V[n].num=1+V[V[n].sufflink].num;
        return true;
    }
	
    void init(string S) {
        this->S=S;
        V.clear();
        V.resize(S.size()+10);
		
        n=s=2;
        V[1].first=V[2].first=-1;
        V[1].len=-1;
        V[2].len=0;
        V[1].sufflink=V[2].sufflink=1;
    }
};

int main(){
    string S;
    cin>>S;
    LL n=S.size();
    LL ret=n*(n+1)/2;
    vector<LL> cnt(26,0);
    REP(i,n)cnt[S[i]-'a']++;
    REP(i,26)ret-=cnt[i]*(cnt[i]+1)/2;
     cout<<ret+1<<endl;
    return 0;
}
