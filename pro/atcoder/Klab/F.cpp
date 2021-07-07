//https://beta.atcoder.jp/contests/tenka1-2018/tasks/tenka1_2018_f
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
int a[2123456];
int *b;
constexpr int mod = 998244353;
vector<int> pos[313245];
int put[312345];
void no(){
    cout<<0<<endl;
    exit(0);
}
int main(){
    cin>>N;
    LL ret = 1;
    for(int i:range(N)){
        int x;
        cin>>x;
        x--;
        a[i]=a[i+N]=a[i+2*N]=a[i+3*N]=x;
    }
    int *b=a;
    for(int i:range(N)){
        if(a[i]!=0&&a[i+1]==0){
            b=a+i+1;
            break;
        }
    }
    b+=N;
    LL del = 0;
    int k=0;
    while(k<N&&b[k]==0)k++;
    if(k==0)no();
    if(k==N){
        for(int i:range(N)){
            ret*=i+1;
            ret%=mod;
        }
        cout<<ret<<endl;
        return 0;
    }
    for(int i:range(N)){
        pos[b[i]].push_back(i);
    }
    for(int i:range(N)){
        int m=pos[i].size();
        for(int j:range(m-1)){
            if(pos[i][j]+1!=pos[i][j+1])no();
        }
        if(m>k)no();
        if(m>0){
            int pre = b[pos[i].front()-1];
            int nxt = b[pos[i].back()+1];
            if(m==k){
                put[i]=pos[i].front();
            }
            else{
                if(pre<i&&nxt<i){
                    put[i]=pos[i].front();
                    ret*=put[i]-max(put[pre],pos[i].back()-k);
                    ret%=mod;
                }
                else if(pre<i){
                    put[i]=pos[i].back()-k+1;
                }
                else if(nxt<i){
                    put[i]=pos[i].front();
                }
                else no();
            }
            if(pre<i){
                del+=put[i]-put[pre]-1;
            }
            if(nxt<i){
                del+=(N+put[nxt]-put[i])%N-1;
            }

        }
        else{
            ret*=del;ret%=mod;
            del--;
            if(ret==0)no();
        }
        //cout<<del<<" "<<ret<<endl;
    }
    //cout<<0<<endl;
    //return -1;
    cout<<ret<<endl;

    return 0;
}