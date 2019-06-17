//https://atcoder.jp/contests/caddi2018/tasks/caddi2018_c
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
LL a[212345];
LL A[212345];
LL B[212345];
LL BS[212345];
LL BSS[212345];
LL C[212345];
LL r[212345];
LL get_height(int i,int j){
    return BS[j] - BS[i];
}
LL get_sum(int i,int j){
    return BSS[j]-BSS[i+1]-BS[i]*(j-i-1);
}
void solve(){
    for(int i:range(N-1)){
        B[i] = 0;
        if(A[i]<=A[i+1]){
            LL x = A[i];
            while(x*4<=A[i+1]){
                x*=4;
                B[i]-=2;
            }
        }
        else{
            LL x = A[i+1];
            while(A[i]>x){
                x*=4;
                B[i]+=2;
            }
        }
        BS[i+1]=BS[i]+B[i];
        BSS[i+2]=BSS[i+1]+BS[i+1];
    }
    stack<LL> st;
    C[N] = 0;
    st.push(N);
    for(int i=N-1;i>=0;i--){
        C[i] = 0;
        while(st.size()>1&&get_height(i,st.top())>0){
            st.pop();
        }
        C[i]+=get_sum(i,st.top());
        C[i]+=C[st.top()];
        st.push(i);
    }

    //for(int i:range(N)){cout<<B[i]<<" ";}cout<<endl;
    //for(int i:range(N+1)){cout<<BS[i]<<" ";}cout<<endl;
    //for(int i:range(N+2)){cout<<BSS[i]<<" ";}cout<<endl;

}

int main(){
    cin>>N;
    for(int i:range(N)){
        cin>>a[i];
    }
    for(int i:range(N))A[i]=a[i];
    solve();
    for(int i:range(N))r[i]=C[i]+i;
    for(int i:range(N))A[i]=a[N-1-i];
    solve();
    for(int i:range(1,N)){
        r[i]+=C[N-i];
    }
    LL ret= 1e18;
    for(int i:range(N)){
        chmin(ret,r[i]);
    }
    cout<<ret<<endl;
    return 0;
}