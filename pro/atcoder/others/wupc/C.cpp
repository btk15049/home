//https://atcoder.jp/contests/wupc2019/tasks/wupc2019_c
#include<bits/stdc++.h>
using namespace std;
#define TEMPLATE
#ifdef BTK
#define DEBUG if(1)
#else
#define CIN_ONLY if(0)
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

Graph<> g(212345);
int vis[212345];
int p[212345];
int dfs(int v){
    if(vis[v])return -1;
    vis[v]=1;
    vector<int> unused;
    for(int u:g.Ns(v)){
        if(dfs(u)==u){
            unused.push_back(u);
        }
    }
    for(int i:range(unused.size()/2)){
        const int x=unused[2*i];
        const int y=unused[2*i+1];
        p[x]=y+1;
        p[y]=x+1;
    }
    if(unused.size()%2==0){
        return v;
    }
    else{
        const int x=unused.back();
        const int y=v;
        p[x]=y+1;
        p[y]=x+1;
        return -1;
    }
}
inline int get_int(){
    int a;
    scanf("%d",&a);
    return a;
}
int main(){
    int N=get_int();
    int M=get_int();
    for(int i:range(M)){
        int a=get_int()-1;
        int b=get_int()-1;
        g.add_edge(a,b);
    }
    if(dfs(0)==0){
        const int x=g.Ns(0).front();
        const int y=p[x]-1;
        p[0]=x+1;
        p[x]=y+1;
        p[y]=1;
    }
    string sp(N,' ');sp.back()='\n';
    for(int i:range(N)){
        printf("%d%c",p[i],sp[i]);
    }
    return 0;
}