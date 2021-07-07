//https://beta.atcoder.jp/contests/tenka1-2018/tasks/tenka1_2018_d
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

int a[1123][1123];
int main(){
    int N;
    cin>>N;
    int K=-1;
    for(int i:range(2,1123)){
        if(i*(i-1)/2==N){
            K=i;
            break;
        }
    }
    if(K==-1)cout<<"No"<<endl;
    else {
        cout<<"Yes"<<endl;
        cout<<K<<endl;
        int p=1;
        string sp(K-1,' ');
        sp.back()='\n';
        for(int i:range(K)){
            for(int j:range(i+1,K)){
                a[i][j]=a[j][i]=p++;
            }
            int id =0;
            cout<<K-1<<" ";
            for(int j:range(K)){
                if(i!=j)cout<<a[i][j]<<sp[id++];
            }
        }
    }
    return 0;
}