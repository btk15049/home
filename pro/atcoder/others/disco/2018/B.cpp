//https://beta.atcoder.jp/contests/ddcc2019-qual/tasks/ddcc2018_qual_b
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
double EPS=1e-10;
bool in1(double x,double y){
    return y>=-x+0.5-EPS;
}
bool in2(double x,double y){
    return y>=x-0.5-EPS;
}
bool in3(double x,double y){
    return y<=x+0.5+EPS;
}
bool in4(double x,double y){
    return y<=-x+1.5+EPS;
}
bool in(double x,double y){
    return in1(x,y)&&in2(x,y)&&in3(x,y)&&in4(x,y);
}

int main(){
    int N;
    cin>>N;
    double p=N;
    int ret=0;
    for(int i:range(N)){
        for(int j:range(N)){
            double x1=i/p;
            double x2=(i+1)/p;
            double y1=j/p;
            double y2=(j+1)/p;
            if(in(x1,y1)&&in(x1,y2)&&in(x2,y1)&&in(x2,y2)){
                //cout<<i<<j<<" ";
                ret++;
            }

        }
    }
        cout<<ret<<endl;

    return 0;
}