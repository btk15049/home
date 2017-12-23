#include <bits/stdc++.h>
namespace HEAP{
    using T = int;
    constexpr int BUF = 512345;
    T mem[BUF];
    int ptr = 0;
    T* get(int size){
        ptr += size;
        return mem+ptr-size;
    }
    void reset(){
        ptr = 0;
    }
};

#define SW(a,b) std::swap(h[a],h[b])
class heap{
private:
    using T=HEAP::T;
    T* h;
public:
    int size;
    /*methods*/
    T get_min(){return h[0];}
    T get_max(){return h[size==1?0:1];}
    /*heap down*/
    void hd(){
        int p;
        for(p=1;(p<<1)+3<size;){
            if(h[p-1]>h[p])SW(p-1,p);
            int s=p-1,t=p<<1;
            if(h[s]>h[t]||h[s]>h[t+2]){
                if(h[t]>h[t+2])t+=2;
            }
            else if(h[++s]<h[++t]||h[s]<h[t+2]){
                if(h[t]<h[t+2])t+=2;
            }
            else return;
            SW(s,t);
            p=t|1;
        }
        if(h[p-1]>h[p])SW(p-1,p);
        for(int i=0,t=(p<<1);i<2&&t<size;i++,t+=2)if(h[p-1]>h[t])SW(p-1,t);
        for(int i=0,t=(p<<1)+1;i<2&&t<size;i++,t+=2)if(h[p]<h[t])SW(p,t);
        for(int t=(p<<1);t+1<size;t+=2)if(h[t]>h[t+1])SW(t,t+1);
    }
    void pop(int x){
        SW(x,size-1);
        if(--size>2)hd();
    }
    void  pop_min(){pop(0);}
    void  pop_max(){pop(1);}
    void push(T t){
        int n,p;
        h[n=size++]=t;
        if(n&1){if(h[n-1]>h[n]){SW(n-1,n);n--;}}
        else if(n>0){
            p=(n-((n^2)&2))>>1;
            if(h[n]>h[p]){SW(n,p);n=p;}
            else if(h[n]<h[p-1]){SW(n,p-1);n=p-1;}
            else return;
        }
        else return;
        if(n&1){
            for (;n>1;n=p)
                if(h[p=(n-((n^2)&2))>>1]<h[n])SW(p,n);
                else break;            
        }
        else{
            for(;n>1;n=p)
                if(h[p=((n-((n^2)&2))>>1)-1]>h[n])SW(p,n);
                else break;
        }
    }    
    bool empty(){return size==0;}
    bool exist(){return size>0;}
    // n = reserved_size
    heap(int n = HEAP::BUF):h(HEAP::get(n)){
        size = 0;
    }
    void clear(){size=0;}
};




/*test code*/
using namespace std;
std::chrono::high_resolution_clock::time_point begin_time;
inline void timer_set() {
    using namespace std::chrono;
    begin_time = high_resolution_clock::now();
}
inline int get_time(){
    using namespace std::chrono;
    auto ed=high_resolution_clock::now();
    auto t=ed-begin_time;
    return duration_cast<milliseconds>(t).count();
}
inline bool time_check(int lim) {
    using namespace std::chrono;
    return(get_time()< lim);
}

unsigned yy=1145141919;
inline unsigned xorshift(){yy=yy^(yy<<13);yy=yy^(yy>>17);return yy=yy^(yy<<5);}
#define MASK 65535
inline int randInt(){return (int) (xorshift()&MASK);}
inline double randDouble(){return (xorshift()&MASK) /(double)MASK;}

constexpr int SZ = 100000; 
int main(){
    multiset<int> ms;
    heap h;
    while(1){
        if(ms.size()==0){
            int x=randInt();
            printf("insert:%d\n",x);
            ms.insert(x);
            h.push(x);
        }
        else{
            int t=randInt()%4;
            switch(t){
            case 0:
            case 1:
            case 2:{
                int x=randInt();
                printf("insert:%d\n",x);
                ms.insert(x);
                h.push(x);
            }break;
            case 3:{                
                printf("erase:max\n");
                ms.erase(std::prev(ms.end()));
                h.pop_max();
            }break;
            }
        }
        if(ms.size()>SZ){
            ms.erase(ms.begin());
            h.pop_min();
        }
        assert(h.size==(int)ms.size());
        printf("size:%d\n",h.size);
        if(ms.size()>0){
            printf("min:%d max:%d\n",h.get_min(),h.get_max());
            assert(h.get_min()==*ms.begin());
            assert(h.get_max()==*ms.rbegin());
        }
        puts("");
    }
    return 0;
}
