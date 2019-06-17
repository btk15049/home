//
#include<vector>
#include<string>
#include<iostream>
#include<string>
#include<cstring>
#include<chrono>
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
#define FOR(i,bg,ed) for(int (i)=(bg);(i)<(ed);(i)++)
#define REP(i,n) FOR(i,0,n)

namespace xorshift{
    unsigned yy=114514;
    inline unsigned rand(){yy=yy^(yy<<13);yy=yy^(yy>>17);return yy=yy^(yy<<5);}
    constexpr int MASK  = 65535;
    inline int randInt(){return (int) (rand()&MASK);}
    inline double randDouble(){return (rand()&MASK) /(double)MASK;}
}
std::chrono::high_resolution_clock::time_point now_time;

inline void timer_set() {
    using namespace std::chrono;
    now_time = high_resolution_clock::now();
}
template<int lim>
inline bool timer_check() {
    using namespace std::chrono;
    auto ed = high_resolution_clock::now();
    auto t = ed - now_time;
    return(duration_cast<milliseconds>(t).count() < lim);
}




constexpr int N = 500;
constexpr int M = 29;
constexpr int L = 300;
constexpr int dr[4]={-1,0,1,0};
constexpr int dc[4]={0,1,0,-1};
constexpr int d_u =0;
constexpr int d_l =3;
constexpr int d_d =2;
constexpr int d_r =1;
constexpr int sr = 14;
constexpr int sc = 14;
char board[M][M];
char tmp_board[M][M];
string s[N];
int ad[30][100];
int point[1000]={0,10,3,1};
constexpr int go = -1;
struct cwwwwwww{
    int command[L];
    int num[L];
    int size=0;
}S[N];
struct box{
    int id[30];
    int size = 0;
    void push(int a){
        id[size++]=a;
    }
    int& operator[](int i){
        return id[i];
    }
}conflict[M][M];

template<typename BOARD>
inline void simulate(BOARD b,int i,int &r,int &c,int bg,int ed){
    int d=d_u;
    FOR(j,bg,ed){
        if(S[i].command[j]==go){
            const int nr = ad[r][50+dr[d]*S[i].num[j]];
            const int nc = ad[c][50+dc[d]*S[i].num[j]];
            if(b[nr][nc]=='#')continue;
            r=nr,c=nc;
        }
        else{
            if(b[r][c]=='R')d=(d+d_r*S[i].num[j])&3;
            else if(b[r][c]=='L')d=(d+d_l*S[i].num[j])&3;
            else d=(d+S[i].command[j])&3;
        }
    }
}
template<typename BOARD>
inline int simulate(BOARD b){
    int ret = 0;
    REP(i,M)REP(j,M){
        conflict[i][j].size=0;
    }
    REP(i,N){
        int r=sr,c=sc;
        simulate(b,i,r,c,0,S[i].size);
        ret-=point[conflict[r][c].size];
        conflict[r][c].push(i);
        ret+=point[conflict[r][c].size];
    }
    return ret;
}



void tmp_init(){
    REP(i,M)REP(j,M)tmp_board[i][j]='#';
    FOR(i,1,M-1)FOR(j,1,M-1)tmp_board[i][j]='.';
}
void random_set(){
    FOR(i,1,M-1)FOR(j,1,M-1){
        if(xorshift::randInt()&1){
            if(xorshift::randInt()&1)tmp_board[i][j]='R';
            else tmp_board[i][j]='L';
        }
        else tmp_board[i][j]='.';
    }
}
int pos_id[N];
int pos_size=0;
inline void pos_update(){
    pos_size=0;
    REP(i,M)REP(j,M)if(conflict[i][j].size>=2){
        pos_id[pos_size]=conflict[i][j][0];
        pos_size++;
    }
}
int loops = 0;
int update = 0;
inline bool update_check(double t,double now,double nxt){
    double r = xorshift::randDouble();
    double related_diff = nxt/now;
    //cerr<<t*related_diff*related_diff*related_diff<<endl;
    return r < t*related_diff*related_diff*related_diff;
}
constexpr double ini_t=0.3;
double t_update(double t){
    return t*0.92;
}
int solve(){
    //init
    tmp_init();
    int now_score = simulate(board);
    REP(_i,10){
        random_set();
        int nxt_score = simulate(tmp_board);
        if(now_score<nxt_score){
            //REP(i,M)REP(j,M)board[i][j]=tmp_board[i][j];
            memcpy(board,tmp_board,M*M);
            now_score=nxt_score;
        }
    }
    int best_score=simulate(board);
    //REP(i,M)REP(j,M)tmp_board[i][j]=board[i][j];
    memcpy(tmp_board,board,M*M);

    pos_update();
    double t=ini_t;
    int st=0;
    while(timer_check<2950>()){
        loops++;
        int random_value = xorshift::randInt()%pos_size;
        int id = pos_id[random_value];
        int pos = xorshift::randInt()%S[id].size;
        while(S[id].command[pos]==go)pos = xorshift::randInt()%S[id].size;
        int r=sr,c=sc;
        simulate(board,id,r,c,0,pos);
        char prv = board[r][c];
        char nxt = '-';
        int def_dir = S[id].command[pos];
        if(prv=='R')def_dir=d_r*S[id].num[pos];
        if(prv=='L')def_dir=d_l*S[id].num[pos];
        if(((d_r*S[id].num[pos])&3)!=def_dir)nxt='R';
        if(((d_l*S[id].num[pos])&3)!=def_dir)nxt='L';
        if(def_dir!=S[id].command[pos])nxt='.';
        if(nxt=='-')continue;
        board[r][c]=nxt;
        st++;
        int nxt_score = simulate(board);
        //DEBUG cerr<<nxt_score-now_score<<"\n";
        if(now_score<nxt_score||update_check(t,(double)now_score,(double)nxt_score)){
            now_score=nxt_score;
            pos_update();
            t=t_update(t);
            update++;
            if(best_score<now_score){
                st=0;
                //REP(i,M)REP(j,M)tmp_board[i][j]=board[i][j];
                memcpy(tmp_board,board,M*M);

                best_score=now_score;
            }
        }
        else{
            board[r][c]=prv;
        }

        if(st>=1000&&best_score-now_score>100){
            //REP(i,M)REP(j,M)board[i][j]=tmp_board[i][j];
            memcpy(board,tmp_board,M*M);
            now_score = simulate(board);
            pos_update();
            st=0;
            DEBUG cerr<<"reset"<<endl;
        }

    }
    REP(i,M)REP(j,M)board[i][j]=tmp_board[i][j];

    return best_score;
}

int main(){
    timer_set();

    //input
    int ei,latte,beet;cin>>ei>>latte>>beet;
    REP(i,N)cin>>s[i];

    //compress
    REP(i,N){
        int ptr=0;
        while(ptr<L){
            int jp = ptr;

            if(s[i][ptr]=='S'){
                while(jp<L&&s[i][jp]=='S'){
                    jp++;
                }
                S[i].command[S[i].size]=go;
                S[i].num[S[i].size]=min(29,jp-ptr);
            }
            else{
                int dir = 0;
                while(jp<L&&(s[i][jp]=='L'||s[i][jp]=='R')){
                    if(s[i][jp]=='L')dir+=3;
                    else dir+=1;
                    jp++;
                }
                S[i].command[S[i].size]=dir%4;
                S[i].num[S[i].size]=jp-ptr;
            }
            S[i].size++;
            ptr=jp;
        }
    }

    // board init
    REP(i,M)REP(j,M)board[i][j]='#';
    FOR(i,1,M-1)FOR(j,1,M-1)board[i][j]='.';
    REP(i,30)FOR(j,-40,40){
        ad[i][j+50]=max(1,min(M-2,i+j));
    }

    int ret = solve();
    // output
    REP(i,M){
        REP(j,M){
            cout<<board[i][j];
        }
        cout<<endl;
    }
    DEBUG cerr<<loops<<" "<<update<<" "<<ret<<endl;
    return 0;
}