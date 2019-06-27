// https://atcoder.jp/contests/abc129/tasks/abc129_b
#ifdef BTK
/*<head>*/
#    include "Template.hpp"
/*</head>*/
#else
/*<body>*/
/* #region header */
/* #region 1*/
/**
 * @file Template.hpp
 * @brief 競技プログラミング用テンプレート
 * @author btk15049
 * @date 2019/05/02
 */
#    include <bits/stdc++.h>
using namespace std;

/* #region macro */
/**
 * @def DEBUG
 * @brief デバッグ用のif文　提出時はif(0)で実行されない
 */

/**
 * @def CIN_ONLY
 * @brief デバッグ用のif文　提出時はif(0)で実行されない
 */

#    ifdef BTK
#        define DEBUG if (1)
#        define CIN_ONLY if (0)
#    else
#        define DEBUG if (0)
#        define CIN_ONLY if (1)
#    endif
/**
 * @def ALL(v)
 * @brief
 * ALLマクロ
 */
#    define ALL(v) (v).begin(), (v).end()

/**
 * @def REC(ret, ...)
 * @brief
 * 再帰ラムダをするためのマクロ
 */
#    define REC(ret, ...) std::function<ret(__VA_ARGS__)>
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
     * @var star
     * @brief cin高速化を実体化
     */
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
        /**
         * @brief Construct a new reverse range object
         *
         * @param n
         */
        reverse_range(int n) : i({0}), n({n}) {}
        /**
         * @brief Construct a new reverse range object
         *
         * @param i
         * @param n
         */
        reverse_range(int i, int n) : i({i}), n({n}) {}
        /**
         * @brief
         * begin iterator
         * @return I&
         */
        I& begin() { return n; }
        /**
         * @brief
         * end iterator
         * @return I&
         */
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
        /**
         * @brief Construct a new range object
         *
         * @param n
         */
        range(int n) : i({0}), n({n}) {}
        /**
         * @brief Construct a new range object
         *
         * @param i
         * @param n
         */
        range(int i, int n) : i({i}), n({n}) {}
        /**
         * @brief
         * begin iterator
         * @return I&
         */
        I& begin() { return i; }
        /**
         * @brief
         * end iterator
         * @return I&
         */
        I& end() { return n; }
        /**
         * @brief
         * 逆向きに参照するrange(reverse_rangeを取得できるs)
         * @return reverse_range
         */
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
    //! LL
    using LL = long long;
} // namespace _Template_
using namespace _Template_;
/* #endregion */
/* #endregion */
/*</body>*/
#endif

int N;
int w[112];
int main() {
    cin >> N;
    for (int i : range(N)) cin >> w[i];
    int ret = 1e9;
    for (int i : range(N + 1)) {
        chmin(ret, abs(accumulate(w, w + i, 0) - accumulate(w + i, w + N, 0)));
    }
    cout << ret << endl;
    return 0;
}