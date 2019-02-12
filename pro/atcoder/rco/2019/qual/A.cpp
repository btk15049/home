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
    unsigned yy=1145141919;
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

constexpr int N = 200;
struct P{
    int r,c;
}p[N];
int ord[N+1];
double d[N][N];
double dd[N][N];

void input(){
    int n;
    scanf("%d",&n);
    for(int i:range(N))scanf("%d %d",&(p[i].r),&(p[i].c));
}
void as(double S,double V){
    double sum = 0 , var = 0;
    for(int i:range(N))sum+=d[ord[i]][ord[i+1]];
    for(int i:range(N))var+=N*dd[ord[i]][ord[i+1]];
    var -= sum*sum;
    const int diff = abs(S-sum);
    assert (abs(S-sum)<1e-8);
    //cerr <<fixed<<V<<" "<<var <<endl;
    assert (abs(V-var) < 1);
}
inline double ini(){
    return 1.0;
}
inline double ch(double t){
    return t* 0.999;
}
inline double eval(double cur,double nxt, double t){
    return ((nxt-cur)/cur) * util::randDouble() < t;
}
int best_ord[N+1];
double best_var = 1e18;
double best_sum = 0;
inline void cp(int *a,int *b){
    for(int i:range(N+1))b[i]=a[i];
}
void solve(){
    //init
    for(int i:range(N))ord[i]=i;ord[N]=0;
    for(int i:range(N))for(int j:range(N)){
        double dr = p[i].r-p[j].r;
        double dc = p[i].c-p[j].c;
        dd[i][j]=dr*dr+dc*dc;
        d[i][j]=sqrt(dd[i][j]);
    }
    double sum = 0,var = 0;
    for(int i:range(N)){
        sum+=d[ord[i]][ord[i+1]];
    }
    //var = S(dd-2ds/N+ss/NN)
    //    = S(dd-2ds/N) + ss/N
    //Nvar= S(Ndd) - ss
    for(int i:range(N)){
        var+=N*dd[ord[i]][ord[i+1]];
    }
    var += -sum*sum;
    int loop=0;
    double temp = ini();
    bool is_update = false;
    int update = 0;
    for(loop = 0;;loop++){
        if((loop&((1<<15)-1)) == 1){
            if(util::tm_check<1900>()==false)break;
                //cerr<<"loop:"<<loop<<endl;
                //as(sum,var);
                if(is_update == false){
                    temp+=0.3;
                    sum = best_sum;
                    var = best_var;
                    cp(best_ord,ord);
                    update++;
                }
                is_update=false;

        }
        const int l = util::ri(N-2);
        const int r = util::ri(l+2,N);
        const double old_dist1 = d[ord[l]][ord[l+1]];
        const double old_dist2 = d[ord[r]][ord[r+1]];
        const double new_dist1 = d[ord[l]][ord[r]];
        const double new_dist2 = d[ord[l+1]][ord[r+1]];
        const double sum_diff = new_dist1 + new_dist2 - old_dist1 - old_dist2;
        const double new_sum = sum+sum_diff;
        double var_diff = 0;
        var_diff += N*(new_dist1*new_dist1 - old_dist1*old_dist1);
        var_diff += N*(new_dist2*new_dist2 - old_dist2*old_dist2);
        var_diff += +sum*sum - new_sum*new_sum;
        const double new_var = var+var_diff;
        if(eval(var,new_var,temp)){
            var = new_var;
            sum = new_sum;
            reverse(ord+l+1,ord+r+1);
            is_update=true;
            if(chmin(best_var, new_var)){
                best_sum = sum;
                cp(ord,best_ord);
                //cerr<<loop<<" "<<best_var<<endl;
            }
        }
        else{
            //reverse(ord+l+1,ord+r+1);
        }
        temp = ch(temp);
    }
    /*
    cerr << fixed;
    cerr << temp << endl;
    cerr<<"loops: "<< loop << endl;
    cerr<<"rebuild: "<< update << endl;
    cerr<<"expected: "<< (int)(1e6 / (1+best_var/(N*N)))<<endl;
    */
}
void output(){
    for(int i:range(N))printf("%d\n",best_ord[i]);
}
int main(){
    input();
    solve();
    output();
    return 0;
}