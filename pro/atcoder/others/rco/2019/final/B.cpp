#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#ifdef BTK
#define DEBUG if(1)
#else
#define CIN_ONLY if(1)
#define DEBUG if(0)
#endif
#define ALL(v) (v).begin(),(v).end()
#define REC(ret, ...) std::function<ret (__VA_ARGS__)>
template <typename T>inline bool chmin(T &l, T r){bool a = l>r; if (a)l = r; return a;}
template <typename T>inline bool chmax(T &l, T r){bool a = l<r; if (a)l = r; return a;}
template <typename T>istream& operator>>(istream &is, vector<T> &v){for (auto &it : v)is >> it;return is;}
class reverse_range {private:struct I {int x;int operator*() {return x-1;}bool operator!=(I& lhs) {return x>lhs.x;}void operator++() {--x;}};I i, n;public:reverse_range(int n) :i({ 0 }), n({ n }){}reverse_range(int i, int n) :i({ i }), n({ n }){}I& begin() {return n;}I& end() {return i;}};
class range {private: struct I { int x; int operator*() { return x; }bool operator!=(I& lhs) { return x<lhs.x; }void operator++() { ++x; } }; I i, n;public:range(int n) :i({ 0 }), n({ n }) {}range(int i, int n) :i({ i }), n({ n }) {}I& begin() { return i; }I& end() { return n; }reverse_range operator!(){return reverse_range(*i,*n);}};

namespace util{
    unsigned yy=1145141918;
    inline unsigned rand(){yy=yy^(yy<<13);yy=yy^(yy>>17);return yy=yy^(yy<<5);}
    constexpr int MASK  = 65535;
    inline int randInt(){return (int) (rand()&MASK);}
    inline double randDouble(){return (rand()&MASK) /(double)MASK;}
    inline int ri(int n){return randInt()%n;}
    inline int ri(int l,int r){return randInt()%(r-l)+l;}
    struct timer{
        std::chrono::high_resolution_clock::time_point begin_time;
        timer(){
		    using namespace std::chrono;
		    begin_time = high_resolution_clock::now();
        }
	    inline int get() {
	        using namespace std::chrono;
		    auto ed = high_resolution_clock::now();
		    auto t = ed - begin_time;
		    return duration_cast<milliseconds>(t).count();
        }
    }tm;
    template<int T>
	inline bool tm_check(){
		return(tm.get()< T);
	}
}

int N,M;
int input[22][22];
int c[22][22];
int o[1024][3];
int ret[1024];
int sum[22][22][4];
int Q=0;

template<int color>
int sc(int sr,int sc){
    int sum = 0;
    for(int i:range(N/2)){
        for(int j:range(N/2)){
            sum+=(c[sr+i][sc+j]==color)?1:0;
        }
    }
    return sum;
}
int score(){
    return sc<0>(0,0)+sc<1>(0,N/2)+sc<2>(N/2,0)+sc<3>(N/2,N/2);
}

void sum_init(){
    for(int i:range(20)){
        for(int j:range(20)){
            for(int k:range(4)){
                sum[i][j][k]=0;
            }
        }
    }
    for(int k:range(4)){
        for(int i:range(N)){
            for(int j:range(N)){
                sum[i+1][j+1][k]=((c[i][j]==k)?1:0)+sum[i+1][j][k]+sum[i][j+1][k]-sum[i][j][k];

            }
        }
    }
}

template<int color>
int get_sum(int sr,int sc,int er,int ec){
    return sum[er][ec][color]+sum[sr][sc][color]-sum[er][sc][color]-sum[sr][ec][color];
}

enum POS{
    TOP=0,
    BOTTOM=1,
    LEFT=2,
    RIGHT=3,
    C0=4,
    C1=5,
    C2=6,
    C3=7,
};
template<int color,int pos>
int get_sum(int sr,int sc,int len){
    const int half = len/2;
    const int er = sr+len;
    const int ec = sc+len;
    if(pos==TOP){
        return get_sum<color>(sr,sc,sr+half,ec);
    }
    if(pos==BOTTOM){
        return get_sum<color>(er-half,sc,er,ec);
    }
    if(pos==LEFT){
        return get_sum<color>(sr,sc,er,sc+half);
    }
    if(pos==RIGHT){
        return get_sum<color>(sr,ec-half,er,ec);
    }
    if(pos==C3){
        return get_sum<color>(sr,sc,er,ec)-get_sum<color>(sr,sc,sr+half,sc+half);
    }
    if(pos==C2){
        return get_sum<color>(sr,sc,er,ec)-get_sum<color>(sr,ec-half,sr+half,ec);
    }
    if(pos==C1){
        return get_sum<color>(sr,sc,er,ec)-get_sum<color>(er-half,sc,er,sc+half);
    }
    if(pos==C0){
        return get_sum<color>(sr,sc,er,ec)-get_sum<color>(er-half,ec-half,er,ec);
    }

    return get_sum<color>(sr,sc,er,ec);
}


int cc[20][20];
void rot(int i,int j,int l){
    for(int x:range(l)){
        for(int y:range(l)){
            int nx=y;
            int ny=l-1-x;
            cc[i+nx][j+ny]=c[i+x][j+y];
        }
    }
    for(int x:range(l)){
        for(int y:range(l)){
            c[i+x][j+y]=cc[i+x][j+y];
        }
    }
}
void set_query(int i,int j,int l){
    if(Q>=M)return;
    o[Q][0]=i;
    o[Q][1]=j;
    o[Q][2]=l;
    rot(i,j,l);
    ret[Q]=score();
    Q++;
}

bool f(int r_min,int c_min,int r_max,int c_max,
    function<int(int,int,int)> S,
    function<int(int,int,int)> D,
    function<int(int,int,int)> T
){
    sum_init();
    pair<int,int> opt = {-1e8,-1};
    int oi=-1,oj,ol,ti;
    for(int i:range(r_min,r_max)){
        for(int j:range(c_min,c_max)){
            for(int len:range(2,N+1)){
                if(i+len>r_max)continue;
                if(j+len>c_max)continue;
                if(chmax(opt,{S(i,j,len),util::ri(65536)})){
                    oi=i;
                    oj=j;
                    ol=len;
                    ti=1;
                }
                if(chmax(opt,{D(i,j,len),util::ri(65536)})){
                    oi=i;
                    oj=j;
                    ol=len;
                    ti=2;
                }
                if(chmax(opt,{T(i,j,len),util::ri(65536)})){
                    oi=i;
                    oj=j;
                    ol=len;
                    ti=3;
                }
            }
        }
    }
    if(opt.first<=0)return false;
    if(Q+ti>M)return false;
    /*/
    cerr << opt.first/6.0 <<" ";
    cerr << "(";
    cerr << oi << " ";
    cerr << oj << ") ";
    cerr << ol << " ";
    cerr << ti << " ";
    cerr << endl;
    //*/
    for(int t:range(ti)){
        set_query(oi,oj,ol);
    }
    return Q<M;
}
void solve(){
    //cerr << "--" << endl;
    int init_q = Q;
    while(f(0,0,N,N,
            [](int i,int j,int len){
                int old_valid =
                  get_sum<0,TOP>(i,j,len)
                + get_sum<1,TOP>(i,j,len)
                + get_sum<2,BOTTOM>(i,j,len)
                + get_sum<3,BOTTOM>(i,j,len);
                int new_valid =
                  get_sum<0,LEFT>(i,j,len)
                + get_sum<1,LEFT>(i,j,len)
                + get_sum<2,RIGHT>(i,j,len)
                + get_sum<3,RIGHT>(i,j,len);
                return 6*(new_valid-old_valid);
            },
            [](int i,int j,int len){
                int old_valid =
                  get_sum<0,TOP>(i,j,len)
                + get_sum<1,TOP>(i,j,len)
                + get_sum<2,BOTTOM>(i,j,len)
                + get_sum<3,BOTTOM>(i,j,len);
                int new_valid =
                  get_sum<0,BOTTOM>(i,j,len)
                + get_sum<1,BOTTOM>(i,j,len)
                + get_sum<2,TOP>(i,j,len)
                + get_sum<3,TOP>(i,j,len);
                return 3*(new_valid-old_valid);
            },
            [](int i,int j,int len){
                int old_valid =
                  get_sum<0,TOP>(i,j,len)
                + get_sum<1,TOP>(i,j,len)
                + get_sum<2,BOTTOM>(i,j,len)
                + get_sum<3,BOTTOM>(i,j,len);
                int new_valid =
                  get_sum<0,RIGHT>(i,j,len)
                + get_sum<1,RIGHT>(i,j,len)
                + get_sum<2,LEFT>(i,j,len)
                + get_sum<3,LEFT>(i,j,len);
                return 2*(new_valid-old_valid);
            }
        )
    );
    //cerr << "--" << endl;
    while(
        f(0,0,N/2,N,
            [](int i,int j,int len){
                int old_valid =
                  get_sum<0,LEFT>(i,j,len)
                + get_sum<1,RIGHT>(i,j,len);
                int new_valid =
                  get_sum<0,BOTTOM>(i,j,len)
                + get_sum<1,TOP>(i,j,len);
                return 6*(new_valid-old_valid);
            },
            [](int i,int j,int len){
                int old_valid =
                  get_sum<0,LEFT>(i,j,len)
                + get_sum<1,RIGHT>(i,j,len);
                int new_valid =
                  get_sum<0,RIGHT>(i,j,len)
                + get_sum<1,LEFT>(i,j,len);
                return 3*(new_valid-old_valid);
            },
            [](int i,int j,int len){
                int old_valid =
                  get_sum<0,LEFT>(i,j,len)
                + get_sum<1,RIGHT>(i,j,len);
                int new_valid =
                  get_sum<0,TOP>(i,j,len)
                + get_sum<1,BOTTOM>(i,j,len);
                return 2*(new_valid-old_valid);
            }
        )
    );
    //cerr << "--" << endl;

    while(
        f(N/2,0,N,N,
            [](int i,int j,int len){
                int old_valid =
                  get_sum<2,LEFT>(i,j,len)
                + get_sum<3,RIGHT>(i,j,len);
                int new_valid =
                  get_sum<2,BOTTOM>(i,j,len)
                + get_sum<3,TOP>(i,j,len);
                return 6*(new_valid-old_valid);
            },
            [](int i,int j,int len){
                int old_valid =
                  get_sum<2,LEFT>(i,j,len)
                + get_sum<3,RIGHT>(i,j,len);
                int new_valid =
                  get_sum<2,RIGHT>(i,j,len)
                + get_sum<3,LEFT>(i,j,len);
                return 3*(new_valid-old_valid);
            },
            [](int i,int j,int len){
                int old_valid =
                  get_sum<2,LEFT>(i,j,len)
                + get_sum<3,RIGHT>(i,j,len);
                int new_valid =
                  get_sum<2,TOP>(i,j,len)
                + get_sum<3,BOTTOM>(i,j,len);
                return 2*(new_valid-old_valid);
            }
        )
    );
    while(
        f(0,0,N/2,N/2,
            [](int i,int j,int len){
                int old_valid = get_sum<0,C0>(i,j,len);
                int new_valid = get_sum<0,C2>(i,j,len);
                return 6*(new_valid-old_valid);
            },
            [](int i,int j,int len){
                int old_valid = get_sum<0,C0>(i,j,len);
                int new_valid = get_sum<0,C3>(i,j,len);
                return 3*(new_valid-old_valid);
            },
            [](int i,int j,int len){
                int old_valid = get_sum<0,C0>(i,j,len);
                int new_valid = get_sum<0,C1>(i,j,len);
                return 2*(new_valid-old_valid);
            }
        )
    );
    while(
        f(0,N/2,N/2,N,
            [](int i,int j,int len){
                int old_valid = get_sum<1,C1>(i,j,len);
                int new_valid = get_sum<1,C0>(i,j,len);
                return 6*(new_valid-old_valid);
            },
            [](int i,int j,int len){
                int old_valid = get_sum<1,C1>(i,j,len);
                int new_valid = get_sum<1,C2>(i,j,len);
                return 3*(new_valid-old_valid);
            },
            [](int i,int j,int len){
                int old_valid = get_sum<1,C1>(i,j,len);
                int new_valid = get_sum<1,C3>(i,j,len);
                return 2*(new_valid-old_valid);
            }
        )
    );
    while(
        f(N/2,0,N,N/2,
            [](int i,int j,int len){
                int old_valid = get_sum<2,C2>(i,j,len);
                int new_valid = get_sum<2,C3>(i,j,len);
                return 6*(new_valid-old_valid);
            },
            [](int i,int j,int len){
                int old_valid = get_sum<2,C2>(i,j,len);
                int new_valid = get_sum<2,C1>(i,j,len);
                return 3*(new_valid-old_valid);
            },
            [](int i,int j,int len){
                int old_valid = get_sum<2,C2>(i,j,len);
                int new_valid = get_sum<2,C0>(i,j,len);
                return 2*(new_valid-old_valid);
            }
        )
    );
    while(
        f(N/2,N/2,N,N,
            [](int i,int j,int len){
                int old_valid = get_sum<3,C3>(i,j,len);
                int new_valid = get_sum<3,C1>(i,j,len);
                return 6*(new_valid-old_valid);
            },
            [](int i,int j,int len){
                int old_valid = get_sum<3,C3>(i,j,len);
                int new_valid = get_sum<3,C0>(i,j,len);
                return 3*(new_valid-old_valid);
            },
            [](int i,int j,int len){
                int old_valid = get_sum<3,C3>(i,j,len);
                int new_valid = get_sum<3,C2>(i,j,len);
                return 2*(new_valid-old_valid);
            }
        )
    );

}
int best_Q=1000;
int best_op[1024][3];
int main(){
    cin>>N>>M;
    for(int i:range(N)){
        for(int j:range(N)){
            cin>>input[i][j];
        }
    }
    while(util::tm_check<1800>()){
        Q=0;
        for(int i:range(N))for(int j:range(N))c[i][j]=input[i][j];
        for(int i:range(10))solve();
        Q=max_element(ret,ret+Q)-ret+1;
        if(score()==400&&chmin(best_Q,Q)){
            for(int i:range(Q))for(int j:range(3))best_op[i][j]=o[i][j];
        }
    };
    //cerr << Q << ">";
    //Q=argQ+1;
    //assert(ret[argQ-1]==ret[Q-1]);
    cerr << best_Q << endl;
    for(int i:range(best_Q)){
        cout << best_op[i][0] << " ";
        cout << best_op[i][1] << " ";
        cout << best_op[i][2] << endl;
    }
}