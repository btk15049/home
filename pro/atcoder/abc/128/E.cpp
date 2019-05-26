// https://atcoder.jp/contests/abc128/tasks/abc128_e
/*<head>*/
// #include "Template.hpp"
/*</head>*/

/*<body>*/
/* #region header */
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
/*</body>*/

constexpr int S=412345;
int s[S];
int t[S];
LL x[S];
LL d[S];
LL ret[S];
inline LL compute_start_time(LL tm,LL ps){
    cerr << ps-tm << " ";
    return ps-tm;
}

vector<pair<int,LL>> query[S];
int main() {
    int N,Q;
    cin>>N>>Q;
    for(int i:range(N)){
        cin>>s[i]>>t[i]>>x[i];
    }
    for(int i:range(Q)){
        cin>>d[i];
        d[i]=-d[i];
    }
    reverse(d,d+Q);
    for(int i:range(N)){
        int b=upper_bound(d,d+Q,compute_start_time(t[i],x[i]))-d; // OK
        int e=upper_bound(d,d+Q,compute_start_time(s[i],x[i]))-d; //NG
        //swap(b,e);
        if(b>=e)continue;
        query[b].push_back({e,x[i]});
        cerr << b << " ";
        cerr << e << " ";
        cerr << x[i] << "\n";
    }
    set<pair<LL,int>> ps_min;
    set<pair<int,LL>> id_min;
    for(int i:range(Q)){
        while(id_min.size()>0&&id_min.begin()->first<=i){
            auto it = *id_min.begin();
            ps_min.erase({it.second,it.first});
            id_min.erase(it);
        }
        for(auto &it:query[i]){
            id_min.insert(it);
            ps_min.insert({it.second,it.first});
        }

        if(ps_min.size()){
            ret[i]=ps_min.begin()->first;
        }
        else{
            ret[i]=-1;
        }

    }
    reverse(ret,ret+Q);
    for(int i:range(Q))cout<<ret[i]<<"\n";
    return 0;
}