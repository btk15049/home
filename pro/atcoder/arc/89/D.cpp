//https://beta.atcoder.jp/contests/arc089/tasks/arc089_b
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
	constexpr int BufferSize = 16123456;
	using NodeType = int;
	NodeType mem[BufferSize];
	BufferManager<NodeType> buffer(mem);
}
#endif

template<typename T,typename A>
struct RectangleSum{
    T* val;
    int R,C;
    inline T& getref(const int r,const int c){
        return val[r*C+c];
    }
    RectangleSum(
        A grid,
        int row,
        int col,
        BufferManager<T>& buf = NodeBuffer::buffer
    ){
        R=row+1;
        C=col+1;
        val = buf.get(R*C);
        for(int i=0;i<R;i++){
            getref(i,0)=0;
        }
        for(int i=0;i<C;i++){
            getref(0,i)=0;
        }
        for(int r=0;r<row;r++){
            for(int c=0;c<col;c++){
                getref(r+1,c+1) = getref(r+1,c)+getref(r,c+1)+grid[r][c]-getref(r,c);
            }
        }
    }
    inline T get(int rb, int cb, int re, int ce){
        return getref(re,ce)-getref(re,cb)-getref(rb,ce)+getref(rb,cb);
    }
    RectangleSum(){}
};

int N,K;
constexpr int SZ=2123;
int BW[2][2*SZ][2*SZ];
int main(){
    cin>>N>>K;
    for(int i:range(N)){
        int x,y;
        string w;
        cin>>x>>y>>w;
        BW[w=="B"][x%(2*K)][y%(2*K)]++;
    }
    for(int it:{0,1}){
        for(int i:range(2*K)){
            for(int j:range(2*K)){
                BW[it][i+2*K][j+2*K]=BW[it][i][j];
                BW[it][i][j+2*K]=BW[it][i][j];
                BW[it][i+2*K][j]=BW[it][i][j];
            }
        }
    }
    RectangleSum<int,decltype(BW[0])> b(BW[0],4*K,4*K);
    int ret = 0;
    for(int i:range(2*K)){
        for(int j:range(2*K)){
            BW[0][i][j] = b.get(i,j,i+K,j+K) + b.get(i+K,j+K,i+K+K,j+K+K);
        }
    }
    NodeBuffer::buffer.reset();
    RectangleSum<int,decltype(BW[1])> w(BW[1],4*K,4*K);
    for(int i:range(2*K)){
        for(int j:range(2*K)){
            BW[1][i][j] = w.get(i+K,j,i+K+K,j+K) + w.get(i,j+K,i+K,j+K+K);
        }
    }
    for(int i:range(2*K)){
        for(int j:range(2*K)){
            chmax(ret,BW[0][i][j]+BW[1][i][j]);
        }
    }
    cout<<ret<<endl;
    return 0;
}