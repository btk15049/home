//http://codeforces.com/contest/1025/problem/E
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
int m,n;
int a[100];
int b[100];
int c[100];
int d[100];

int k=0;
int o[10800];
int p[10800];
int q[10800];
int r[10800];
int s[10800];

int board[100][100];

void up(int i){
    board[a[i]][b[i]]=-1;
    o[k]=a[i];p[k]=b[i];
    a[i]--;
    board[a[i]][b[i]]=i;
    q[k]=a[i];r[k]=b[i];
    s[k++]=i;
}
void down(int i){
    board[a[i]][b[i]]=-1;
    o[k]=a[i];p[k]=b[i];
    a[i]++;
    board[a[i]][b[i]]=i;
    q[k]=a[i];r[k]=b[i];
    s[k++]=i;
}
void left(int i){
    board[a[i]][b[i]]=-1;
    o[k]=a[i];p[k]=b[i];
    b[i]--;
    board[a[i]][b[i]]=i;
    q[k]=a[i];r[k]=b[i];
    s[k++]=i;
}
void right(int i){
    board[a[i]][b[i]]=-1;
    o[k]=a[i];p[k]=b[i];
    b[i]++;
    board[a[i]][b[i]]=i;
    q[k]=a[i];r[k]=b[i];
    s[k++]=i;
}

void all_up(){
    while(true){
        bool update= false;
        for(int i:range(m)){
            if(a[i]>1&&board[a[i]-1][b[i]]==-1){
                up(i);
                update=true;
            }
        }
        if(update==false)break;
    }
}
void all_left(){
    while(true){
        bool update=false;
        for(int i:range(m)){
            if(b[i]>1&&board[a[i]][b[i]-1]==-1){
                left(i);
                update=true;
            }
        }
        if(update==false)break;
    }
}


int main(){
    for(int i:range(100))for(int j:range(100))board[i][j]=-1;
    cin>>n>>m;
    for(int i:range(m)){
        cin>>a[i]>>b[i];
        board[a[i]][b[i]]=i;
    }

    if(n==1){
        cout<<0<<endl;
        return 0;
    }
    for(int i:range(m))cin>>c[i]>>d[i];
    all_up();
    while(true){
        bool exist = false;
        for(int i:range(1,n+1)){
            if(board[2][i]!=-1)exist=true;
        }
        if(exist==false)break;
        while(true){
            bool update= false;
            for(int i:range(m)){
                if(a[i]==1){
                    if(b[i]>1&&board[a[i]][b[i]-1]==-1){
                        left(i);
                        update=true;
                    }
                }
                else{
                    if(b[i]<n&&board[a[i]][b[i]+1]==-1){
                        right(i);
                        update=true;
                    }
                }
            }
            if(update==false)break;
        }
        all_up();
    }
    all_left();
    using V=vector<int>;
    vector<V> pos;
    for(int i:range(m)){
        pos.push_back({c[i],d[i],i});
    }
    sort(ALL(pos));
    vector<int> id(m);
    for(int i:range(m)){
        id[pos[i][2]]=i+1;
    }
    for(int i:range(1,m+1)){
        for(int j:range(i-1)){
            down(board[j+1][i]);
        }
    }
    for(int i:range(m)){
        while(b[i]<id[i])right(i);
        while(b[i]>id[i])left(i);
    }
    for(int i:range(m)){
        while(a[i]<id[i])down(i);
        while(a[i]>id[i])up(i);
    }

    for(int i:range(m)){
        while(b[i]<d[i])right(i);
        while(b[i]>d[i])left(i);
    }
    while(true){
        bool update= false;
        for(int i:range(m)){
            while(a[i]<c[i]&&board[a[i]+1][b[i]]==-1){
                down(i);update=true;
            }
            while(a[i]>c[i]&&board[a[i]-1][b[i]]==-1){
                up(i);update=true;
            }

        }
        if(update==false)break;
    }
    cout<<k<<"\n";
    for(int i:range(k)){
        //cout<<s[i]<<":";
        cout<<o[i]<<" "<<p[i]<<" "<<q[i]<<" "<<r[i]<<"\n";
    }
    //for(int i:range(m))if(a[i]==c[i]&&b[i]==d[i])cout<<"A";else cout<<"B";cout<<endl;
    return 0;
}