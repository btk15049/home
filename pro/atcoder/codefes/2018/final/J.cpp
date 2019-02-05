//https://atcoder.jp/contests/code-festival-2018-final/tasks/code_festival_2018_final_j
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
class reverse_range {private:struct I {int x;int operator*() {return x-1;}bool operator!=(I& lhs) {return x>lhs.x;}void operator++() {--x;}};I i, n;public:reverse_range(int n) :i({ 0 }), n({ n }){}reverse_range(int i, int n) :i({ i }), n({ n }){}I& begin() {return n;}I& end() {return i;}};
class range {private: struct I { int x; int operator*() { return x; }bool operator!=(I& lhs) { return x<lhs.x; }void operator++() { ++x; } }; I i, n;public:range(int n) :i({ 0 }), n({ n }) {}range(int i, int n) :i({ i }), n({ n }) {}I& begin() { return i; }I& end() { return n; }reverse_range operator!(){return reverse_range(*i,*n);}};
int N,n;
int S[512][8192];
int T[8192];
string out="xy";
int x[512];
int y[512];
int f[512];
int z[512][8192];
int K=1;
void ch(int i){
    for(int j:range(N)){
        if(z[i][j]){
            S[i][j]=S[y[i]][j-f[i]];
        }
        else{
            S[i][j]=S[x[i]][j];
        }
    }
}
namespace QS{
    int SS[512][8192];
    int bg[8192];
    int ed[8192];

    void qs(int b,int e,int k,int m){
        DEBUG {
            for(int i:range(b,e)){
                cout<<SS[k-1][i]+1<<",";
            }cout<<endl;
        }
        if(e-b==1)return;
        const int mid = (b+e)/2;
        int kp = k-1;
        int kq = k-1;
        {
            int j = mid;
            for(int i:range(b,e)){
                const int cur = SS[kp][i];
                if(cur>=mid){
                    bg[cur] = i;
                    ed[cur] = j++;
                }
                else{
                    bg[cur]=-1;
                }
            }
        }
        for(int j:range(m)){
            const int mov = 1<<j;
            x[k]=kp;
            y[k]=kp;
            f[k]=mov;
            for(int i:!range(b,e)){
                const int cur = SS[kp][i];
                SS[k][i]=cur;
                if(bg[cur]==i){
                    const int diff = ed[cur]-bg[cur];
                    if(diff&mov){
                        bg[cur]+=mov;
                        SS[k][bg[cur]]=cur;
                        z[k][bg[cur]]=1;
                    }
                }
            }
            kp=k;
            k++;
        }
        {
            int j = mid-1;
            for(int i:!range(b,e)){
                const int cur = SS[kq][i];
                if(cur<mid){
                    bg[cur] = i;
                    ed[cur] = j--;
                }
                else{
                    bg[cur]=-1;
                }
            }
        }
        for(int j:range(m)){
            const int mov = 1<<j;
            x[k]=kq;
            y[k]=kq;
            f[k]=-mov;
            for(int i:range(b,e)){
                const int cur = SS[kq][i];
                SS[k][i]=cur;
                if(bg[cur]==i){
                    const int diff = bg[cur]-ed[cur];
                    if(diff&mov){
                        bg[cur]-=mov;
                        SS[k][bg[cur]]=cur;
                        z[k][bg[cur]]=1;
                    }
                }
            }
            kq=k;
            k++;
        }
        x[k]=kp;
        y[k]=kq;
        f[k]=0;
        for(int i:range(b,mid)){
            z[k][i]=1;
            SS[k][i]=SS[kq][i];
        }
        for(int i:range(mid,e)){
            z[k][i]=0;
            SS[k][i]=SS[kp][i];
        }
        k++;
        chmax(K,k);
        qs(b,mid,k,m-1);
        qs(mid,e,k,m-1);
    }

}
namespace p1{
    int pos[8192];
    int cn[8192];
    int used[8192];
    int t[8192];
    void solve(){
        for(int i:range(N)){
            pos[i]=-1;
            cn[i]=0;
        }
        for(int i:!range(N)){
            pos[S[0][i]]=i;
        }
        for(int i:range(N)){
            cn[T[i]]++;
        }
        int index=0;
        for(int i:range(N)){
            const int cur = S[0][i];
            if(pos[cur]==i&&cn[cur]!=0){
                QS::SS[0][i]=index;
                //cout<<i+1<<":"<<index<<endl;
                used[index]=1;
                for(int j:range(cn[cur])){
                    t[index+j]=cur;
                }
                index+=cn[cur];
            }
        }
        if(index!=N){
            cout<<-1<<endl;
            exit(0);
        }
        queue<int> que;
        for(int i:range(N)){
            if(used[i]!=1)que.push(i);
        }
        for(int i:range(N)){
            if(pos[S[0][i]]!=i||cn[S[0][i]]==0){
                //cout<<que.front()<<endl;
                QS::SS[0][i]=que.front();que.pop();
            }
        }
        //for(int i:range(N)){cout<<QS::SS[0][i]+1<<",";}cout<<endl;
        QS::qs(0,N,K,n);
        //for(int i:range(N)){cout<<QS::SS[K-1][i]+1<<",";}cout<<endl;
        for(int i:range(1,K))ch(i);
        //for(int i:range(N)){cout<<S[0][i]+1<<" ";}cout<<endl;
        //for(int i:range(N)){cout<<S[K-1][i]+1<<" ";}cout<<endl;
        for(int j:range(n)){
            const int mov = 1<<j;
            x[K]=K-1;
            y[K]=K-1;
            f[K]=mov;
            for(int i:range(N)){
                const int cur = S[K-1][i];
                if(cur!=t[i]){
                    z[K][i]=1;
                }
            }
            ch(K);
            K++;
        }
        //for(int i:range(N)){cout<<S[K-1][i]+1<<" ";}cout<<endl;
        //for(int i:range(N)){cout<<T[i]+1<<" ";}cout<<endl;

    }
}
namespace p2{
    queue<int> que[8192];
    void solve(){
        for(int i:range(N)){
            que[T[i]].push(i);
        }
        for(int i:range(N)){
            QS::SS[K-1][i]=que[S[K-1][i]].front();
            que[S[K-1][i]].pop();
        }
        QS::qs(0,N,K,n);
    }
}

int main(){
    cin>>N;
    for(int i:range(N)){
        cin>>S[0][i];S[0][i]--;
    }
    for(int i:range(N)){
        cin>>T[i];T[i]--;
    }
    n=0;
    while((1<<n)<N)n++;
    p1::solve();
    p2::solve();
    cout<<K-1<<endl;

    DEBUG {
        for(int j:range(N)){
            cout<<S[0][j]+1<<",";
        }
        cout<<endl;
    }

    for(int i:range(1,K)){
        cout<<x[i]<<" "<<y[i]<<" "<<f[i]<<" ";
        for(int j:range(N)){
            cout<<out[z[i][j]];
        }
        cout<<endl;
        ch(i);
        DEBUG {
            for(int j:range(N)){
                cout<<S[i][j]+1<<",";
            }
            cout<<endl;
        }
    }
    DEBUG {
        for(int j:range(N)){
            cout<<S[K-1][j]+1<<",";
        }
        cout<<endl;
        for(int j:range(N)){
            cout<<T[j]+1<<",";
        }
        cout<<endl;
    }
    bool check = true;
    for(int j:range(N)){
        if(S[K-1][j]!=T[j])check=false;
    }
    if(check==false){
        cout<<"WA"<<endl;
        return 1;
    }
    //cout<<K<<endl;

    return 0;
}