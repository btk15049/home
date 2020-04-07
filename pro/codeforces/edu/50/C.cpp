//http://codeforces.com/contest/1036/problem/C
#include<bits/stdc++.h>

using namespace std;
typedef long long LL;

#ifdef BTK
#define DEBUG if(1)
#else
#define CIN_ONLY if(1)
struct cww {cww() {CIN_ONLY{ios::sync_with_stdio(false); cin.tie(0);}}
}star;
#define DEBUG if(0)
#endif

#define ALL(v) (v).begin(),(v).end()
#define REC(ret, ...) std::function<ret (__VA_ARGS__)>
template <typename T>inline bool chmin(T &l, T r){bool a = l>r; if (a)l = r; return a;}
template <typename T>inline bool chmax(T &l, T r){bool a = l<r; if (a)l = r; return a;}
template <typename T>istream& operator>>(istream &is, vector<T> &v){for (auto &it : v)is >> it;return is;}

class range {private: struct I { int x; int operator*() { return x; }bool operator!=(I& lhs) { return x<lhs.x; }void operator++() { ++x; } }; I i, n;public:range(int n) :i({ 0 }), n({ n }) {}range(int i, int n) :i({ i }), n({ n }) {}I& begin() { return i; }I& end() { return n; }};


LL latte[212345];
int malta=0;
LL L[21234];
LL R[21234];
constexpr LL top = 1e18;
LL cnt[212345];
int main() {
    int q;
    cin>>q;
    for(int i:range(q)){
        cin>>L[i]>>R[i];
        latte[malta++]+=L[i]-1;
        latte[malta++]+=R[i];
    }
    latte[malta++]=1e18;
    sort(latte,latte+malta);
    malta=unique(latte,latte+malta)-latte;
    for(int i:range(1,10))for(int a:range(18)){
        string s(18,'0');
        s[a]='0'+i;
        cnt[lower_bound(latte,latte+malta,stoll(s))-latte]++;
    }
    for(int i:range(1,10))for(int a:range(18)){
        for(int j:range(1,10))for(int b:range(a+1,18)){
            string s(18,'0');
            s[a]='0'+i;
            s[b]='0'+j;
            cnt[lower_bound(latte,latte+malta,stoll(s))-latte]++;
        }
    }

    for(int i:range(1,10))for(int a:range(18)){
        for(int j:range(1,10))for(int b:range(a+1,18)){
            for(int k:range(1,10))for(int c:range(b+1,18)){
                string s(18,'0');
                s[a]='0'+i;
                s[b]='0'+j;
                s[c]='0'+k;
                cnt[lower_bound(latte,latte+malta,stoll(s))-latte]++;
            }
        }
    }
    for(int i:range(1,malta))cnt[i]+=cnt[i-1];
    for(int i:range(q)){
        LL ret=cnt[lower_bound(latte,latte+malta,R[i])-latte]-cnt[lower_bound(latte,latte+malta,L[i]-1)-latte];
        if(R[i]==top)ret++;
        cout<<ret<<endl;
    }
    return 0;
}
