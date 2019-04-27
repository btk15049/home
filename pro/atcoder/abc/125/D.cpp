//https://atcoder.jp/contests/abc125/tasks/abc125_d
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
template<typename T>inline T& unused_var(T& v){return v;}
class reverse_range {private:struct I {int x;int operator*() {return x-1;}bool operator!=(I& lhs) {return x>lhs.x;}void operator++() {--x;}};I i, n;public:reverse_range(int n) :i({ 0 }), n({ n }){}reverse_range(int i, int n) :i({ i }), n({ n }){}I& begin() {return n;}I& end() {return i;}};
class range {private: struct I { int x; int operator*() { return x; }bool operator!=(I& lhs) { return x<lhs.x; }void operator++() { ++x; } }; I i, n;public:range(int n) :i({ 0 }), n({ n }) {}range(int i, int n) :i({ i }), n({ n }) {}I& begin() { return i; }I& end() { return n; }reverse_range operator!(){return reverse_range(*i,*n);}};
using LL = long long;
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
namespace NodeBuffer {
	constexpr int BufferSize = 812345;
	using NodeType = LL;
	NodeType mem[BufferSize];
	BufferManager<NodeType> buffer(mem);
}
#endif

template<typename T>
struct IntervalHeap{
    T* h;
    int size;
    IntervalHeap(){}
    IntervalHeap(int reserved_size, BufferManager<T>& buf = NodeBuffer::buffer){
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

IntervalHeap<LL> p(112345),n(112345);

int main(){
    int N;
    LL base = 0;
    cin>>N;
    for(int i:range(N)){
        LL x;
        cin>>x;
        if(x>=0){
            p.push(x);
        }
        if(x<0){
            n.push(x);
        }
    }
    while(n.size>=2){
        base+=-n.get_min();n.pop_min();
        base+=-n.get_min();n.pop_min();
    }
    while(p.size>=2){
        base+=p.get_max();p.pop_max();
    }
    LL ret = base+(p.size?p.get_max():0)+(n.size?n.get_max():0);
    if(p.size&&n.size){
        chmax(ret,base-p.get_max()-n.get_max());
    }
    cout << ret << endl;
    return 0;
}