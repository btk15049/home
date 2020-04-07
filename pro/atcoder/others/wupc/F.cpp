//https://atcoder.jp/contests/wupc2019/tasks/wupc2019_f
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

namespace _Graph_{
    /**
    * @file Graph.cpp
    * @brief グラフクラス
    * @author btk15049
    * @date 2019/03/11
    * @datails
    *  verify: WUPC C
    */

    #ifdef BTK
    #ifndef TEMPLATE
    #include "Template.cpp"
    #endif
    #endif
    #define GRAPH

    /**
    * @brief 辺を扱う構造体の例
    * @details
        辺に重みなどを加えたい場合は変数とかを増やして作る．
        Graphに使うために必要な要件:
        - id,a,bは必須，他のパラメータ増やすときはコンストラクタを忘れずに
        - versusは必須，基本的にコピペでOK
    */
    struct Edge{
        int id,a,b;
        /**
         * @brief Construct a new Edge object
         * @param id 辺番号
         * @param a 辺に接続する頂点番号
         * @param b 辺に接続する頂点番号
         */
        Edge(int id=0,int a=0,int b=0):id(id),a(a),b(b){}
        /**
         * @brief 辺における，vの対になってる頂点番号を取得する
         * @param v 頂点番号
         * @return int vじゃない方の頂点番号
         */
        inline int versus(const int v)const{
            return a^b^v;
        }
    };
    /**
     * @brief グラフクラス
     * @tparam E=Edge 新たなグラフクラス作るときは書き換える
     * @details 0-indexedで使うことしか考えてないので注意．
     */
    template<typename E=Edge>
    class Graph{
    private:
        //! 辺集合
        vector<E> edges;
        //! 隣接リスト
        vector<vector<int>> g;
    public:
        /**
         * @brief Construct a new Graph object
         * @param reserved_vertex_size 頂点数の最大値，vectorのサイズ確保用
         * @param reserved_edge_size 辺数の最大値，vectorのサイズ確保用
         */
        Graph(int reserved_vertex_size=1,int reserved_edge_size=-1){
            g.reserve(reserved_vertex_size);
            edges.reserve(max(reserved_vertex_size,reserved_edge_size));
        }

        /**
         * @brief グラフの頂点数を返す
         * @return int 頂点数
         */
        inline int size(){
            return g.size();
        }

        /**
         * @brief vの次数を返す
         * @param v 頂点番号
         * @return int 次数
         */
        inline int degree(const int v){
            return g[v].size();
        }

        /**
         * @brief グラフ全体の辺の数を返す
         * @return int グラフ全体の辺の数
         */
        inline int degree(){
            return edges.size();
        }

        /**
         * @brief "無向"辺(a,b)を追加する．
         * @param a 頂点番号
         * @param b 頂点番号
         * @param params 重みとか，容量とか
         * @details paramsはemplace_backと同じノリで続けて足してけばOK
         */
        template<typename... Ts>
        inline void add_edge(int a,int b, Ts&&... params){
            const int id = edges.size();
            if((int)g.size()<=max(a,b)){
                g.resize(max(a,b)+1);
            }
            g[a].emplace_back(id);
            g[b].emplace_back(id);
            edges.emplace_back(id,a,b,forward<Ts>(params)...);
        }

        /**
         * @brief "有向"辺(a,b)を追加する．
         * @param a 頂点番号
         * @param b 頂点番号
         * @param params 重みとか，容量とか
         * @details paramsはemplace_backと同じノリで続けて足してけばOK
         */
        template<typename... Ts>
        inline void add_arc(int a,int b, Ts&&... params){
            const int id = edges.size();
            if((int)g.size()<=max(a,b)){
                g.resize(max(a,b)+1);
            }
            g[a].emplace_back(id);
            edges.emplace_back(id,a,b,forward<Ts>(params)...);
        }

        /**
        * @brief vの隣接頂点を返す
        * @param v int
        * @return vector<int>
        */
        inline vector<int> Ns(const int v){
            vector<int> ns(g[v].size());
            for(int i=0;i<degree(v);i++){
                ns[i] = edges[g[v][i]].versus(v);
            }
            return ns;
        }

        /**
        * @brief vに隣接する辺番号の集合を返す
        * @param v int
        * @return vector<Edge>
        */
        inline const vector<int>& operator[](const int v){
            return g[v];
        }

        /**
        * @brief 辺番号から辺の参照を取得する
        * @param edge_id
        * @return E&
        */
        inline E& i2e(const int edge_id){
            return edges[edge_id];
        }
    };
}
using namespace _Graph_;

namespace _Dinic_{
    /**
    * @file Dinic.cpp
    * @brief Dinic法の実装
    * @author btk15049
    * @date 2019/03/13
    * @datails
    *  \todo verify
    *  verify: WUPC F
    */

    #ifdef BTK
    #ifndef TEMPLATE
    #include "Template.cpp"
    #endif
    #ifndef GRAPH
    #include "Graph.cpp"
    #endif
    #endif

    /**
     * @brief フロー用の辺構造体
     * @tparam F 流量の型
     */
    template<typename F>
    struct FlowEdge{
        int id,a,b;
        F cap;
        int rev;
        /**
         * @brief Construct a new Edge object
         * @param id 辺番号
         * @param a 辺に接続する頂点番号
         * @param b 辺に接続する頂点番号
         */
        FlowEdge(int id=0,int a=0,int b=0,F cap=0,int rev=0):id(id),a(a),b(b),cap(cap),rev(rev){}
        /**
         * @brief 辺における，vの対になってる頂点番号を取得する
         * @param v 頂点番号
         * @return int vじゃない方の頂点番号
         */
        inline int versus(const int v)const{
            return a^b^v;
        }
    };

    /**
     * @brief フロー用のグラフクラス,Graphを継承
     * @tparam E 辺構造体
     */
    template<typename E>
    class FlowGraph:public Graph<E>{
    private:
        using Graph<E>::add_arc; // add_arcは外から呼び出せないようにする
    public:
        /**
         * @brief a->bへ流量fの辺を追加
         * @tparam F 流量の型
         * @param a 頂点番号
         * @param b 頂点番号
         * @param f 最大流量
         * @details Graph::add_edge をオーバーライドしている．
         */
        template<typename F>
        inline void add_edge(int a,int b,F f){
            const int id = this->degree();
            this->add_arc(a,b,f,id+1);
            this->add_arc(b,a,0,id);
        }
        /**
         * @brief Construct a new Flow Graph object
         * @details 完全転送してるので詳しくはGraphクラスのコンストラクタを参照．
         */
        template<typename... Ts>
        FlowGraph(Ts&&... params):Graph<E>(forward<Ts>(params)...){}
    };

    /**
     * @brief Dinic法の実装
     * @tparam F 流量の型
     * @tparam flow_inf 流量の最大値
     */
    template<typename F,F flow_inf>
    class Dinic{
    private:
        using E=FlowEdge<F>;
        FlowGraph<E> *G;
        /**
         * @brief 最短路求めるBFSをする
         * @param s 始点
         * @return vector<int> sから各頂点への最短距離
         */
        vector<int> bfs(const int s){
            int N = G->size();
            queue<int> que;
            vector<int> dist(N,-1);
            dist[s] = 0;
            que.push(s);
            for(;!que.empty();que.pop()){
                const int v=que.front();
                for(int id : (*G)[v]){
                    const E& e = G->i2e(id);
                    const int u = e.versus(v);
                    if(e.cap > 0&&dist[u]==-1){
                        dist[u] = dist[v] + 1;
                        que.push(u);
                    }
                }
            }
            return dist;
        }
        /**
         * @brief s->tに向けてできるだけフローを流す
         */
        F dfs(const int v,const int s,const F f,vector<unsigned>& I,vector<int>& D){
            if(v==s)return f;
            const vector<int>& edge_ids = (*G)[v];
            for(unsigned& i = I[v]; i < edge_ids.size(); i++){
                E& e = G->i2e(edge_ids[i]);
                E& re = G->i2e(e.rev);
                const int u = e.versus(v);
                if(re.cap>0 && D[v] > D[u]){
                    F d=dfs(u,s,min(f,re.cap),I,D);
                    if(d>0){
                        e.cap+=d;
                        re.cap-=d;
                        return d;
                    }
                }
            }
            return 0;
        }
    public:
        /**
         * @brief 現在の残余グラフから得られる最大流を求めて流す．
         * @param s 始点
         * @param t 終点
         * @return F 流量
         */
        F solve(const int s,const int t){
            F res=0;
            while(true){
                vector<int> dist = bfs(s);
                if(dist[t] < 0)break;
                vector<unsigned> iter(G->size(),0);
                while(true){
                    F f=dfs(t,s,flow_inf,iter,dist);
                    if(f==0)break;
                    res+=f;
                }
            }
            return res;
        }
        /**
         * @brief Construct a new Dinic object
         * @param G 最大流を流したいグラフ
         */
        Dinic(FlowGraph<E> &G):G(&G){}
    };
}
using namespace _Dinic_;

template<typename T>inline T& unused_var(T& v){return v;}

constexpr LL INF = 1e18;
int c[512];
int main(){
    int N,M;
    cin>>N>>M;
    int vs=N*2;
    const int S=vs++;
    const int T=vs++;
    const int SS = vs++;
    const int TT = vs++;
    FlowGraph<FlowEdge<LL>> g(512,1024);
    c[0]=0;
    c[N-1]=0;
    for(int i:range(1,N-1)){
        cin>>c[i];
    }
    g.add_edge(SS,S,INF);
    g.add_edge(T,TT,INF);
    for(int i:range(N)){
        if(c[i]==-1){
            g.add_edge(S,i,INF);
            g.add_edge(i+N,T,INF);
        }
        else{
            g.add_edge(i+N,i,c[i]);
        }
    }
    for(int i:range(M)){
        unused_var(i);
        int a,b;
        cin>>a>>b;
        a--;
        b--;
        g.add_edge(a,b+N,INF);
    }
    LL ret = Dinic<LL,INF>(g).solve(SS,TT);
    if(ret>=INF)ret=-1;
    cout << ret << endl;
    return 0;
}