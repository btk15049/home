// https://atcoder.jp/contests/abc131/tasks/abc131_f
/*<head>*/
// #include "Template.hpp"
/*</head>*/

/*<body>*/
/* #region header */
/* #region 1*/
/**
 * @file Template.hpp
 * @brief 競技プログラミング用テンプレート
 * @author btk15049
 * @date 2019/05/02
 */
#include <bits/stdc++.h>
using namespace std;

/* #region macro */
#ifdef BTK
#    define DEBUG if (1)
#    define CIN_ONLY if (0)
#else
#    define DEBUG if (0)
#    define CIN_ONLY if (1)
#endif
/** @def
 * ALLマクロ
 */
#define ALL(v) (v).begin(), (v).end()

/** @def
 * 再帰ラムダをするためのマクロ
 */
#define REC(ret, ...) std::function<ret(__VA_ARGS__)>
/* #endregion */

namespace _Template_ {
    /**
     * @brief cin高速化処理を行うための構造体
     * @details CIN_ONLYマクロで動作が変わる
     */
    struct cww {
        cww() {
            CIN_ONLY {
                ios::sync_with_stdio(false);
                cin.tie(0);
            }
        }
    } star;
    /**
     * @brief change min
     * @tparam T 型
     * @param l 参照
     * @param r 非参照
     * @return 更新があればtrue
     */
    template <typename T>
    inline bool chmin(T& l, T r) {
        bool a = l > r;
        if (a) l = r;
        return a;
    }
    /**
     * @brief chminのmax版
     * @see chmin
     */
    template <typename T>
    inline bool chmax(T& l, T r) {
        bool a = l < r;
        if (a) l = r;
        return a;
    }
    /**
     * @brief
     * vectorに直接cin流すためのやつ
     * @tparam T
     * @param is
     * @param v
     * @return istream&
     */
    template <typename T>
    istream& operator>>(istream& is, vector<T>& v) {
        for (auto& it : v) is >> it;
        return is;
    }
    /**
     * @brief
     * rangeを逆向きに操作したいとき用
     * @details
     * ループの範囲は[bg,ed)なので注意
     * @see range
     */
    class reverse_range {
      private:
        struct I {
            int x;
            int operator*() { return x - 1; }
            bool operator!=(I& lhs) { return x > lhs.x; }
            void operator++() { --x; }
        };
        I i, n;

      public:
        reverse_range(int n) : i({0}), n({n}) {}
        reverse_range(int i, int n) : i({i}), n({n}) {}
        I& begin() { return n; }
        I& end() { return i; }
    };
    /**
     * @brief
     * python みたいな range-based for を実現
     * @details
     * ループの範囲は[bg,ed)なので注意
     * !つけると逆向きにループが回る (reverse_range)
     * 空間計算量はO(1)
     * 使わない変数ができて警告が出がちなので，unused_varとかを使って警告消しするとよい
     */
    class range {
      private:
        struct I {
            int x;
            int operator*() { return x; }
            bool operator!=(I& lhs) { return x < lhs.x; }
            void operator++() { ++x; }
        };
        I i, n;

      public:
        range(int n) : i({0}), n({n}) {}
        range(int i, int n) : i({i}), n({n}) {}
        I& begin() { return i; }
        I& end() { return n; }
        reverse_range operator!() { return reverse_range(*i, *n); }
    };
    /**
     * @brief
     * rangeで生まれる使わない変数を消す用（警告消し）
     */
    template <typename T>
    inline T& unused_var(T& v) {
        return v;
    }
    using LL = long long;
} // namespace _Template_
using namespace _Template_;
/* #endregion */
/* #endregion */
/*</body>*/
namespace _DSU{
    constexpr int BUF = 512345*2;
    int ptr=0;
    int mem[BUF];
    int* get(int size){
        ptr+=size;
        return mem+ptr-size;
    }
    void reset(){
        ptr = 0;
    }
}
class UF{
private:
    int *par,*rank;
    public:
    int find(int x){
        if (par[x] == x) return x;
        else return par[x] = find(par[x]);
    }
    UF(int n):par(_DSU::get(n+10)),rank(_DSU::get(n+10)){
	for(int i = 0;i<n;i++){
            par[i] = i,rank[i] = 0;
        }
    }
    bool unite(int x, int y){
    	x = find(x);y = find(y);
	if (x == y)return false;
	if (rank[x] < rank[y])swap(x,y);
    par[y] = x;
    if (rank[x] == rank[y])rank[x]++;
	return true;
    }
    bool same(int x, int y){
        return find(x) == find(y);
    }
};
constexpr int S = 112345;
int main() {
    int N;
    cin >> N;
    UF uf(S*4);
    for(int i:range(N)){
        int x,y;
        cin>>x>>y;
        x--;y--;
        uf.unite(x,y+S);
    }
    vector<LL> X(4*S,0),Y(4*S,0);
    for(int i:range(S)){
        X[uf.find(i)]++;
        Y[uf.find(S+i)]++;
        //if(max(X[i],Y[i]))cout<<X[i]<<" "<<Y[i]<<endl;
    }
    LL ret=0;
    for(int i:range(4*S)){
        ret+=X[i]*Y[i];
    }
    cout<<ret-N<<endl;
    return 0;
}