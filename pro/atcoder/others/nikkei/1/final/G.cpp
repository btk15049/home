//https://atcoder.jp/contests/nikkei2019-final/tasks/nikkei2019_final_g
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


const LL INF = 1e17;

template <typename T, const T id>
class convex_hull_trick {
    struct line {
        T a, b;
        line(T a_ = 0, T b_ = 0) : a(a_), b(b_) {}
        T get(T x) { return a * x + b; }
    };
    struct node {
        line l;
        node *lch, *rch;
        node(line l_) : l(l_), lch(nullptr), rch(nullptr) {}
        ~node() {
            if (lch) delete lch;
            if (rch) delete rch;
        }
    };

private:
    const int n;
    const vector<T> pos;
    node *root;

public:
    convex_hull_trick(const vector<T>& pos_) : n(pos_.size()), pos(pos_), root(nullptr) {}
    ~convex_hull_trick() {
        if (root) delete root;
    }
    void insert(T a, T b) {
        line l(a, b);
        root = modify(root, 0, n - 1, l);
    }
    T get(T x) const {
        int t = lower_bound(pos.begin(), pos.end(), x) - pos.begin();
        assert(t < n && pos[t] == x);
        return sub(root, 0, n - 1, t);
    }

private:
    node* modify(node *p, int lb, int ub, line& l) {
        if (!p) return new node(l);
        if (p->l.get(pos[lb]) >= l.get(pos[lb]) && p->l.get(pos[ub]) >= l.get(pos[ub])) return p;
        if (p->l.get(pos[lb]) <= l.get(pos[lb]) && p->l.get(pos[ub]) <= l.get(pos[ub])) {
            p->l = l;
            return p;
        }
        int c = (lb + ub) / 2;
        if (p->l.get(pos[c]) < l.get(pos[c])) swap(p->l, l);
        if (p->l.get(pos[lb]) <= l.get(pos[lb]))
            p->lch = modify(p->lch, lb, c, l);
        else
            p->rch = modify(p->rch, c + 1, ub, l);
        return p;
    }
    T sub(node *p, int lb, int ub, int t) const {
        if (!p) return id;
        if (ub - lb == 0) return p->l.get(pos[t]);
        int c = (lb + ub) / 2;
        if (t <= c) return max(p->l.get(pos[t]), sub(p->lch, lb, c, t));
        return max(p->l.get(pos[t]), sub(p->rch, c + 1, ub, t));
    }
};
typedef vector<int> V;
typedef vector<V> VV;
namespace CD{
    struct centroid{
        int size;
        int par;
        V   cld;
        V   vex;
    }node[112345];
    stack<int> st;
    int dfs(int v,int p,int all,VV &g,int *a,int *b,int &tar,int& ans,int *used){
        int cld_size=1;
        int cld_max=0;
        used[v]=0;
        for(auto &e:g[v]){
            int u=v^a[e]^b[e];
            if(used[u]!=-1)continue;
            if(u==p)continue;
            int cld=dfs(u,v,all,g,a,b,tar,ans,used);
            chmax(cld_max,cld);
            cld_size+=cld;
        }
        chmax(cld_max,all-cld_size);
        if(cld_max<ans){
            tar=v;
            ans=cld_max;
        }
        return cld_size;
    }
    int construct(int v,VV&g,int *a,int *b,int *used,int p=-1){
        st.push(v);
        V vex;
        vex.push_back(v);
        used[v]=-1;
        while(st.size()){
            int s=st.top();st.pop();
            for(auto &e:g[s]){
                int t=s^a[e]^b[e];
                if(used[t])continue;
                st.push(t);
                used[t]=-1;
                vex.push_back(t);
            }
        }

        int lim = vex.size()+1;
        dfs(v,-1,vex.size(),g,a,b,v,lim,used);
        used[v]=1;

        node[v].size = vex.size();
        node[v].par  = p;
        node[v].vex  = vex;

        for(auto &e:g[v]){
            int u=v^a[e]^b[e];
            if(used[u])continue;
            node[v].cld.push_back(construct(u,g,a,b,used,v));
        }
        return v;
    }
    int decomposition(VV &g,int *a,int *b,int *buf){
        return construct(0,g,a,b,buf,-1);
    }
}
int N,M;
int A[112345];
int B[112345];
LL  C[112345];
int F[112345];
int qv[112345];
LL  ql[112345];
LL ret[112345];
VV g,Q;
void input(){
    cin>>N;
    g.resize(N);
    Q.resize(N);
    //cerr<<g.size()<<endl;
    for(int i:range(N-1)){
        cin>>A[i]>>B[i]>>C[i];
        A[i]--;
        B[i]--;
        //cerr<<A[i]<<" "<<B[i]<<endl;
        g[A[i]].push_back(i);
        g[B[i]].push_back(i);
    }
    cin>>M;
    for(int i:range(M)){
        cin>>qv[i]>>ql[i];
        qv[i]--;
        Q[qv[i]].push_back(i);
    }
}
LL  top[112345];
LL  dist[112345];
int dept[112345];
int on[112345];
void set_dist(int v,int p){
    for(int e:g[v]){
        chmax(top[v],C[e]);
        const int u = v^A[e]^B[e];
        if(u==p)continue;
        if(on[u]==0)continue;
        dist[u]=dist[v]+C[e];
        dept[u]=dept[v]+1;
        set_dist(u,v);
    }
}

int line[112345];
vector<int> dfs(int v){
    auto &cur = CD::node[v];
    vector<int> query;
    for(int c:cur.cld){
        auto q = dfs(c);
        for(int u:q)query.push_back(u);
    }
    for(int u:Q[v])query.push_back(u);
    for(int u:cur.vex)on[u]=1;
    dist[v]=dept[v]=0;
    set_dist(v,v);
    int ls = 0;
    vector<LL> lens;
    for(int u:cur.vex){
        on[u]=0;
        //LL bg=dept[u];
        //LL la=top[u];
        //LL lb=dist[u]-dept[u]*la;
        line[ls++]=u;
        //T(bg,la,lb);
    }
    for(int q:query){
        lens.push_back(ql[q]-dept[qv[q]]);
    }
    sort(ALL(lens));
    lens.erase(unique(ALL(lens)),lens.end());
    sort(line,line+ls,[&](int l,int r){return dept[l]<dept[r];});
    sort(ALL(query),[&](int l,int r){return ql[l]-dept[qv[l]]<ql[r]-dept[qv[r]];});
    int li = 0;
    convex_hull_trick<LL,-1ll> cht(lens);
    for(int q:query){
        LL len = ql[q]-dept[qv[q]];
        while(li<ls&&dept[line[li]]<=len){
            const int u = line[li];
            LL bg=dept[u];
            LL la=top[u];
            LL lb=dist[u]-dept[u]*la;
            //insert (la,lb)
            cht.insert(la,lb);
            //cerr << " ins "<<u+1<<" "<<bg<<" "<<la<<" "<<lb<<endl;
            li++;
        }
        //if(q==1)cerr << " get "<<q+1<<" "<<len;
        if(li){
            LL ans = dist[qv[q]];
            ans += cht.get(len);
            //if(q==1)cerr<<" "<<ans<<endl;
            chmax(ret[q],ans);
        }
        //if(q==1)cerr << endl;
    }
    //cerr << v+1 <<"(";
    //for(int u:cur.vex)cerr<<u+1<<",";cerr<<"):";
    //for(int q:query)cerr<<q+1<<" ";cerr<<"$"<<endl;
    return query;
}

void solve(){
    int root = CD::decomposition(g,A,B,F);
    dfs(root);
}
void output(){
    for(int i:range(M)){
        cout << ret[i] << endl;
    }
}
int main(){
    input();
    solve();
    output();
    return 0;
}