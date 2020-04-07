//https://atcoder.jp/contests/wupc2019/tasks/wupc2019_d
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

using V=vector<int>;
using P=pair<int,int>;
constexpr int INF = 1e6;

#ifndef NDBUF
#define NDBUF
template<typename T>
struct BufferManager {
	T *mem;
	int ptr;
	BufferManager(T* mem) {
		ptr = 0;
		this->mem = mem;
	}
	T* get(int m) {
		ptr += m;
		return mem + ptr - m;
	}
	void reset() {
		ptr = 0;
	}
};
#endif

namespace PairBuffer {
	constexpr int BufferSize = 812345;
	using NodeType = pair<int,int>;
	NodeType mem[BufferSize];
	BufferManager<NodeType> buffer(mem);
}


template<typename T>
struct IntervalHeap{
    T* h;
    int size;
    IntervalHeap(){}
    IntervalHeap(int reserved_size, BufferManager<T>& buf){
        h = buf.get(reserved_size);
        size = 0;
    }
    inline void inner_swap(int a,int b){
        std::swap(h[a],h[b]);
    }
    inline void heap_down(){
        int p;
        for(p=1;(p<<1)+3<size;){
            if(h[p-1]>h[p])inner_swap(p-1,p);
            int s=p-1,t=p<<1;
            if(h[s]>h[t]||h[s]>h[t+2]){
                if(h[t]>h[t+2])t+=2;
            }
            else if(h[++s]<h[++t]||h[s]<h[t+2]){
                if(h[t]<h[t+2])t+=2;
            }
            else return;
            inner_swap(s,t);
            p=t|1;
        }
        if(h[p-1]>h[p])inner_swap(p-1,p);
        for(int i=0,t=(p<<1);i<2&&t<size;i++,t+=2)if(h[p-1]>h[t])inner_swap(p-1,t);
        for(int i=0,t=(p<<1)+1;i<2&&t<size;i++,t+=2)if(h[p]<h[t])inner_swap(p,t);
        for(int t=(p<<1);t+1<size;t+=2)if(h[t]>h[t+1])inner_swap(t,t+1);
    }
   inline void push(T t){
        int n,p;
        h[n=size++]=t;
        if(n&1){if(h[n-1]>h[n]){inner_swap(n-1,n);n--;}}
        else if(n>0){
            p=(n-((n^2)&2))>>1;
            if(h[n]>h[p]){inner_swap(n,p);n=p;}
            else if(h[n]<h[p-1]){inner_swap(n,p-1);n=p-1;}
            else return;
        }
        else return;
        if(n&1){
            for (;n>1;n=p)
                if(h[p=(n-((n^2)&2))>>1]<h[n])inner_swap(p,n);
                else break;
        }
        else{
            for(;n>1;n=p)
                if(h[p=((n-((n^2)&2))>>1)-1]>h[n])inner_swap(p,n);
                else break;
        }
    }
    inline void pop(int x){
        inner_swap(x,size-1);
        if(--size>2)heap_down();
    }
    /*methods*/
    inline bool is_empty(){return size==0;}
    inline T get_min(){return h[0];}
    inline T get_max(){return h[size==1?0:1];}
    inline void pop_min(){pop(0);}
    inline void pop_max(){pop(1);}
    inline void clear(){size=0;}
};



int main(){
    int N;
    int M;
    cin>>N>>M;
    vector<V> g(N);
    for(int i:range(M)){
        int a,b;
        cin>>a>>b;
        a--;b--;
        g[a].push_back(b);
    }
    vector<vector<P>> seg(N);
    for(int i:range(N)){
        g[i].push_back(-10);
        g[i].push_back(i);
        g[i].push_back(N+10);
        sort(ALL(g[i]));
        for(int j:range(1,g[i].size())){
            const int u = g[i][j-1];
            const int v = g[i][j];
            if(v-u>1){
                seg[i].push_back({u+1,v-1});
            }
        }
    }
    vector<int> lb(N),ub(N);
    vector<int> pos(N);
    set<P> bg;
    IntervalHeap<P> ed(N+10,PairBuffer::buffer);
    for(int i:range(N)){
        bg.insert({seg[i][pos[i]].first,i});
        ed.push({seg[i][pos[i]].second,i});
    }
    for(int i:range(N)){
        while(ed.get_min().first<i){
            const int id = ed.get_min().second;
            ed.pop_min();
            bg.erase({seg[id][pos[id]].first,id});
            pos[id]++;
            bg.insert({seg[id][pos[id]].first,id});
            ed.push({seg[id][pos[id]].second,id});
        }
        lb[i]=max(i+1,bg.rbegin()->first);
    }
    bg.clear();
    ed.clear();
    for(int i:range(N)){
        pos[i]=seg[i].size()-1;
        bg.insert({seg[i][pos[i]].second,i});
        ed.push({seg[i][pos[i]].first,i});
    }
    ub[N-1]=N-1;
    for(int i:!range(N)){
        while(ed.get_max().first>i){
            const int id = ed.get_max().second;
            ed.pop_max();
            bg.erase({seg[id][pos[id]].second,id});

            pos[id]--;
            bg.insert({seg[id][pos[id]].second,id});
            ed.push({seg[id][pos[id]].first,id});
        }
        ub[i]=min(i-1,bg.begin()->first);
    }
    V ret={N+1,-1,-1};
    for(int i:range(N)){
        if(lb[i]>=N||ub[N-1]<i)continue;
        int ok=N-1;
        int ng=lb[i]-1;
        while(ok-ng>1){
            const int mid = (ok+ng)/2;
            if(ub[mid]>=i)ok=mid;
            else ng=mid;
        }
        chmin(ret,V{ok-i,i+1,ok+1});
    }
    if(ret[0]==N+1){
        cout<<-1<<endl;
    }
    else{
        cout<<ret[1]<<" "<<ret[2]<<endl;
    }

    return 0;
}