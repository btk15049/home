//http://codeforces.com/contest/1015/problem/E2
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#ifdef BTK
#define DEBUG if(1)
#else
#define CIN_ONLY if(0)
struct cww {cww() {CIN_ONLY{ios::sync_with_stdio(false); cin.tie(0);}}}star;
#define DEBUG if(0)
#endif
#define ALL(v) (v).begin(),(v).end()
#define REC(ret, ...) std::function<ret (__VA_ARGS__)>
template <typename T>inline bool chmin(T &l, T r){bool a = l>r; if (a)l = r; return a;}
template <typename T>inline bool chmax(T &l, T r){bool a = l<r; if (a)l = r; return a;}
template <typename T>istream& operator>>(istream &is, vector<T> &v){for (auto &it : v)is >> it;return is;}
class range {private: struct I { int x; int operator*() { return x; }bool operator!=(I& lhs) { return x<lhs.x; }void operator++() { ++x; } }; I i, n;public:range(int n) :i({ 0 }), n({ n }) {}range(int i, int n) :i({ i }), n({ n }) {}I& begin() { return i; }I& end() { return n; }};


int tate[1123][1123];
int yoko[1123][1123];
int U[1123][1123];
int D[1123][1123];
int L[1123][1123];
int R[1123][1123];
char s[1123];
int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i:range(n)){
        scanf("%s",s);
        for(int j:range(m)){
            if(s[j]=='*'){
                U[i][j]=1;
                D[i][j]=1;
                L[i][j]=1;
                R[i][j]=1;
            }
        }
    }
    for(int i:range(n)){
        for(int j:range(1,m)){
            if(L[i][j]==0)continue;
            L[i][j]+=L[i][j-1];
        }
        for(int rj:range(1,m)){
            int j = m-1-rj;
            if(R[i][j]==0)continue;
            R[i][j]+=R[i][j+1];
        }
    }
    for(int j:range(m)){
        for(int i:range(1,n)){
            if(U[i][j]==0)continue;
            U[i][j]+=U[i-1][j];
        }
        for(int ri:range(1,n)){
            int i = n-1-ri;
            if(D[i][j]==0)continue;
            D[i][j]+=D[i+1][j];
        }
    }
    vector<int> a,b,c;
    for(int i:range(n)){
        for(int j:range(m)){
            int k = min({U[i][j],D[i][j],L[i][j],R[i][j]});
            if(k>=2){
                a.push_back(i+1);
                b.push_back(j+1);
                c.push_back(k-1);
                tate[i-(k-1)][j]++;
                yoko[i][j-(k-1)]++;
                tate[i+k][j]--;
                yoko[i][j+k]--;
            }
        }
    }
    for(int i:range(n)){
        for(int j:range(m)){
            if(j>0)yoko[i][j]+=yoko[i][j-1];
            if(i>0)tate[i][j]+=tate[i-1][j];
            if(U[i][j]>0&&tate[i][j]+yoko[i][j]==0){
                printf("-1\n");
                return 0;
            }
        }
    }
    printf("%d\n",a.size());
    for(int i:range(a.size())){
        printf("%d %d %d\n",a[i],b[i],c[i]);
    }
    return 0;
}