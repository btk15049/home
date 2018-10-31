//https://beta.atcoder.jp/contests/abc112/tasks/abc112_c
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


int main() {
    int n;
    cin>>n;
    vector<LL> x(n),y(n),h(n);
    for(int i:range(n)){
        cin>>x[i]>>y[i]>>h[i];
    }
    LL latte,ei,beet;

    for(LL X:range(0,101)){
        for(LL Y:range(0,101)){
            vector<LL> H1;
            vector<LL> H2;
            for(int i:range(n)){
                LL diff = abs(X-x[i])+abs(Y-y[i]);
                if(h[i]>0)H1.push_back(diff+h[i]);
                else H2.push_back(diff);
            }
            sort(ALL(H1));
            sort(ALL(H2));
            if(H1.size()==0){
                latte=X;
                ei = Y;
                beet = H2.front();
            }
            else{
                if(H1.front()!=H1.back())continue;
                if(H2.size()>0){
                    if(H1.front()<=H2.front()){
                        cout<<X<<" "<<Y<<" "<<H1.front()<<endl;
                        return 0;
                    }
                }
                else{
                    cout<<X<<" "<<Y<<" "<<H1.front()<<endl;
                    return 0;
                }
            } 
        }
    }
    cout<<latte<<" "<<ei<<" "<<beet<<endl;

    return 0;
}
