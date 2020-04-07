//https://atcoder.jp/contests/wupc2019/tasks/wupc2019_i
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
constexpr int IS=112345;
int N;
LL op[IS];
LL cl[IS];
LL d[IS];
LL x[IS];
LL p[IS];
int ord[IS];
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
constexpr LL INF = 1e18;
using CHT=convex_hull_trick<LL,-INF>;
inline void add_line(LL a,LL b,CHT& cht){
    cht.insert(-a,-b);
}
inline LL get_value(LL p,CHT& cht){
    return -cht.get(p);
}

namespace quad{
	constexpr int b = 1000;
    CHT* cht[(IS+b)/b];

	inline void update(const int pos,const int id){
        const int block_id = pos / b;
        add_line(-2*d[id],d[id]*d[id]+p[id],*cht[block_id]);
	}

	inline LL baby_get(const int lb, const int ub,const int l, const int r,  int id){
		const int block_id = lb / b;
        LL ret=INF;
		for(int i = lb; i < ub ; i++){
            if(i < l || r <= i)continue;
            if(op[ord[i]]<=op[id]-1&&op[id]-1<=cl[ord[i]]){
                chmin(ret,p[ord[i]]+(d[ord[i]]-d[id])*(d[ord[i]]-d[id]));
            }
		}
        return ret;
	}

	inline LL giant_get(const int lb, const int ub, const int id){
		const int block_id = lb / b;
        //cerr << d[id]*d[id]+get_value(d[id],*cht[block_id]) << " ";
        return d[id]*d[id]+get_value(d[id],*cht[block_id]);
	}

	inline LL get(const int l, const int r,const int id){
        LL ret=INF;
		for(int i = (l / b) * b ; i < r ; i+=b){
			if(i < l || r < i + b){
				chmin(ret,baby_get(i ,i + b, l, r , id));
			}
			else{
				chmin(ret,giant_get(i, i + b, id));
			}
		}
        //cerr << endl;
        return ret;
	}
    void init(){
        vector<LL> dd(N);
        for(int i:range(N)){
            dd[i]=d[i];
        }
        sort(ALL(dd));
        dd.erase(unique(ALL(dd)),dd.end());
        for(int i=0;i<N;i+=b){
            const int block_id=i/b;
            cht[block_id]=new CHT(dd);
        }
    }
    void fini(){
        for(int i=0;i<N;i+=b){
            const int block_id=i/b;
            delete cht[block_id];
        }
    }
}


int op_ord[IS];
int ord_pos[IS];
int C[IS];
int main(){
    cin>>N;
    for(int i:range(N)){
        cin>>op[i]>>cl[i]>>d[i]>>x[i];
        if(cl[i]==-1){
            cl[i]=1e5;
        }
        C[i]=cl[i];
    }
    iota(ord,ord+N,0);
    iota(op_ord,op_ord+N,0);
    sort(ord,ord+N,[&](int l,int r){return cl[l]<cl[r];});
    sort(C,C+N);
    for(int i:range(N))ord_pos[ord[i]]=i;
    quad::init();
    queue<int> que;
    for(int i:range(N)){
        while(que.size()&&op[que.front()]<op[i]){
            quad::update(ord_pos[que.front()],que.front());
            que.pop();
        }
        LL query = quad::get(lower_bound(C,C+N,op[i]-1)-C,N,i);
        p[i]=min(x[i],query);
        que.push(i);
        //quad::update(ord_pos[i],i);
        //cerr << i << " "<<query << " "<< p[i] << endl;
    }
    for(int i:range(N)){
        cout << p[i] << endl;
    }
    return 0;
}