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

int N,T;

double dfs(int cur,int depth,double cost,double profit,vector<vector<int>>& pos,int ng,vector<int> &can){
    //if(util::tm_check<4000>())
    {
        if(depth>=2){
            return profit/cost;
        }
    }

    double opt = profit/cost;
    for(int c:can){
        if(ng&(1<<c))continue;
        if(pos[c].size()<2)continue;
        for(int k:range(pos[c].size()-1)){
            int i = pos[c][k];
            int j = pos[c][k+1];
            if(abs(cur-i)<=50)chmax(opt,dfs(j,depth+1,cost+abs(cur-i)+abs(i-j),profit+c,pos,ng|(1<<c),can));
            swap(i,j);
            if(abs(cur-i)<=50)chmax(opt,dfs(j,depth+1,cost+abs(cur-i)+abs(i-j),profit+c,pos,ng|(1<<c),can));
        }
    }
    return opt;
}
void solve(){
    vector<int> card(N,-1);
    vector<vector<int>> pos(26);
    int p = 0;
    int score = 0;
    int unopened = N;
    auto query=[&](int q){
        if(T-abs(p-q)<0){
            cout << -1 << endl;cout.flush();
            //cerr << -1 << endl;cerr.flush();
            exit(0);
        }
        cout << q << endl;cout.flush();
        //cerr << q << endl;cerr.flush();
        int a;
        if(card[q]==-1)unopened--;
        cin>>card[q];
        //cerr <<"open:"<<card[q]<<endl;
        if(p!=q && card[p]==card[q]){
            score += card[q];
            card[p]=card[q]=-1;
            unopened +=2;
        }
        T-=abs(p-q);
        p=q;
    };

    auto get_card=[&](int from,int to){
        if(card[p] == -1){
            query(p);
        }
        else if(from == p){
            query(to);
        }
        else if(from<p){
            query(p-1);
        }
        else{
            query(p+1);
        }
    };

    auto init=[&](){
        cerr << T << "init" << endl;
        int le=N;
        int ri=-1;
        for(int i:range(N)){
            if(card[i]==-1){
                chmin(le,i);
                chmax(ri,i);
            }
        }
        if(abs(le-p)>abs(ri-p)){
            //while(p!=ri){
            //    get_card(ri,ri);
            //}
            while(p!=le){
                get_card(le,le);
            }
        }
        else{
            //while(p!=le){
            //    get_card(le,le);
            //}
            while(p!=ri){
                get_card(ri,ri);
            }
        }
    };
    while(1){
        //cerr << T <<" "<<unopened<< " "<<p <<endl;
        for(int i:range(1,N/2+1)){
            pos[i].clear();
        }
        vector<int> can;

        for(int i:range(N)){
            if(card[i]!=-1){
                pos[card[i]].push_back(i);
            }
        }
        for(int i:range(1,N/2+1)){
            if(pos[i].size()>=2)can.push_back(i);
        }
        if(can.size() < 5){
            //cerr << "init" << endl;
            init();
        }
        else{
            int opt_from=-1;
            int opt_to=-1;
            double opt_perf = -1;

            for(int c:can){
                for(int k:range(pos[c].size()-1)){
                    int i = pos[c][k];
                    int j = pos[c][k+1];
                    if(opt_from==-1 || abs(p-i)<=50)if(chmax(opt_perf,dfs(j,0,abs(p-i)+abs(i-j),c,pos,(1<<c),can))){
                        opt_from=i;
                        opt_to=j;
                    }
                    swap(i,j);
                    if(opt_from==-1 || abs(p-i)<=50)if(chmax(opt_perf,dfs(j,0,abs(p-i)+abs(i-j),c,pos,(1<<c),can))){
                        opt_from=i;
                        opt_to=j;
                    }
                }
            }
            assert(opt_from!=-1);
            //cerr << T << " " <<opt_perf << " "<< score <<endl;
            if(opt_perf < 1.0 ){
                int dist = N;
                for(int i:range(N)){
                    if(card[i]==-1){
                        if(chmin(dist,abs(p-i))){
                            opt_from = i;
                            opt_to = i;
                        }
                    }
                }
            }
            get_card(opt_from,opt_to);
        }
    }
}

void input(){
    cin>>N>>T;
}
int main(){
    input();
    solve();
    return 0;
}