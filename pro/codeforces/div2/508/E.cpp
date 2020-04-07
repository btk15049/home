//http://codeforces.com/contest/1038/problem/E
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
    using V=vector<LL>;
    using VV=vector<V>;
    using VVV = vector<VV>;
    VVV x(4,VV(4));

    for(int i:range(n)){
        int c1,v,c2;
        cin>>c1>>v>>c2;
        c1--;c2--;
        if(c1>c2)swap(c1,c2);
        x[c1][c2].push_back(v);
    }
    vector<pair<int,int>> y;
    for(int i:range(4))for(int j:range(4)){
        sort(ALL(x[i][j]));
        reverse(ALL(x[i][j]));
        if(i<j)y.push_back({i,j});
    }
    LL ret=0;
    for(int i:range(1<<4)){
        for(int j:range(1<<6)){
            LL ans=0;
            bitset<4> bi(i);
            bitset<6> bj(j);
            vector<int> d(4);
            vector<V> g(4);
            for(int k:range(4))if(bi[k])for(auto &it:x[k][k])ans+=it;
            for(int k:range(6)){
                int a,b;tie(a,b)=y[k];
                int use=(int)x[a][b].size();
                if((use%2==1)!=bj[k])use--;
                if(bi[a]&&bi[b]&&use>0){
                    for(int w:range(use))ans+=x[a][b][w];
                    g[a].push_back(b);
                    g[b].push_back(a);
                    d[a]+=use;
                    d[b]+=use;
                }
            }
            int odd = 0,even = 0;
            for(int k:range(4)){
                if(d[k]%2)odd++;
                else even++;
            }
            if(odd==1||odd==3||odd==4)continue;
            bitset<4> used(0);
            stack<int> st;
            for(int k:range(4))if(bi[k]){
                st.push(k);
                used[k]=true;
                break;
            }
            while(st.size()){
                int v=st.top();st.pop();
                for(int u:g[v]){
                    if(used[u]==false){
                        used[u]=true;
                        st.push(u);
                    }
                }
            }
            if(used==bi){
                chmax(ret,ans);
            }
        }
    }

    cout<<ret<<endl;
    return 0;
}

