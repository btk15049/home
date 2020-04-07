//https://atcoder.jp/contests/wupc2019/tasks/wupc2019_b
#include<bits/stdc++.h>
using namespace std;
#define TEMPLATE
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
using LL = long long;

int a[100][100];
int cnt[4];
void Y(int x){
    cout<<"Yes "<<x<<endl;exit(0);
}
void N(){
    cout<<"No"<<endl;exit(0);
}
int main(){
    int R,C;
    cin>>R>>C;
    int top = 0;
    for(int i:range(R)){
        for(int j:range(C)){
            cin>>a[i][j];
            if(a[i][j]==0)cnt[0]++;
            else if(a[i][j]==5)cnt[1]++;
            else if(a[i][j]<5)cnt[2]++;
            else cnt[3]++;
            chmax(top,a[i][j]);
        }
    }
    if(cnt[0]==R*C)Y(0);
    if(cnt[1]==0)N();
    if(cnt[3]==0)Y(1);
    if(R>=2&&C>=2){
        if(top<=7)Y(2);
        if(top<=8)Y(3);
        if(top<=9)Y(4);
    }
    else if(R==1||C==1){
        vector<int> x;
        for(int i:range(R))for(int j:range(C)){
            if(a[i][j]>=5)x.push_back(a[i][j]);
        }
        if(x.front()==5||x.back()==5){
            if(top<=7)Y(2);
            if(top<=8)Y(3);
            if(top<=9)Y(4);
        }
        else{
            int ret=10;
            for(int i:range(1,x.size()-1)){
                if(x[i]==5){
                    int p=0,q=0;
                    for(int j:range(0,i)){
                        chmax(p,x[j]);
                    }
                    for(int j:range(i,x.size())){
                        chmax(q,x[j]);
                    }
                    int ans=0;
                    if(p<=6)ans+=1;
                    else ans+=p-6;
                    if(q<=6)ans+=1;
                    else ans+=q-6;
                    chmin(ret,ans+1);
                }
            }
            Y(ret);
        }
    }
    return 0;
}