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
