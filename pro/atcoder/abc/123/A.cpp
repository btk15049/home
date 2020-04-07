// https://atcoder.jp/contests/abc123/tasks/abc123_a
#ifdef BTK
/*<head>*/
#    include "Template.hpp"
/*</head>*/
#else
/*<body>*/
/* #region header */
/* #region 1*/

#    include <bits/stdc++.h>

using namespace std;
/* #endregion */
/* #region 2*/
/**
 * @file MinMaxOperation.hpp
 * @author btk
 * @brief 最大値とか最小値を求める
 * @version 0.1
 * @date 2019-07-04
 *
 * @copyright Copyright (c) 2019
 *
 */

namespace _MinMaxOperation_ {
    /**
     * @brief 2項の最小値求める
     *
     * @tparam T
     */
    template <typename T>
    struct min_op {
        static T exec(const T l, const T r) { return l < r ? l : r; }
    };

    /**
     * @brief 2項の最大値求める
     *
     * @tparam T
     */
    template <typename T>
    struct max_op {
        static T exec(const T l, const T r) { return l > r ? l : r; }
    };

    /**
     * @brief テンプレート再帰の末尾
     *
     * @tparam F 二項演算
     * @tparam T
     * @param v
     * @return T
     */
    template <typename F, typename T>
    inline T multi_op(T&& v) {
        return v;
    }

    /**
     * @brief 複数項における演算の結果を返す
     *
     * @tparam F
     * @tparam T
     * @tparam Ts
     * @param head
     * @param tail
     * @return T
     */
    template <typename F, typename T, typename... Ts>
    inline T multi_op(const T head, Ts&&... tail) {
        return F::exec(head, multi_op<F>(tail...));
    }

    /**
     * @brief 複数項の最小値
     * @see multi_op
     * @tparam T
     * @tparam Ts
     * @param head
     * @param tail
     * @return T
     */
    template <typename T, typename... Ts>
    inline T multi_min(T&& head, Ts&&... tail) {
        return multi_op<min_op<T>>(head, tail...);
    }

    /**
     * @brief 複数項の最大値
     * @see multi_op
     * @tparam T
     * @tparam Ts
     * @param head
     * @param tail
     * @return T
     */
    template <typename T, typename... Ts>
    inline T multi_max(T&& head, Ts&&... tail) {
        return multi_op<max_op<T>>(head, tail...);
    }

    /**
     * @brief
     * 先頭の値をFで参照する関数に基づいて変更できたらする
     * @tparam F
     * @tparam T
     * @tparam Ts
     * @param target
     * @param candidates
     * @return true
     * @return false
     */
    template <typename F, typename T, typename... Ts>
    inline bool ch_op(T& target, Ts&&... candidates) {
        const T old = target;
        target      = multi_op<F>(target, candidates...);
        return old != target;
    }

    /**
     * @brief change min
     * @tparam T 型
     * @param target 変更する値
     * @param candidates
     * @return 更新があればtrue
     */
    template <typename T, typename... Ts>
    inline bool chmin(T& target, Ts&&... candidates) {
        return ch_op<min_op<T>>(target, candidates...);
    }

    /**
     * @brief chminのmax版
     * @see chmin
     *  @tparam T 型
     * @param target 変更する値
     * @param candidates
     * @return 更新があればtrue
     */
    template <typename T, typename... Ts>
    inline bool chmax(T& target, Ts&&... candidates) {
        return ch_op<max_op<T>>(target, candidates...);
    }
} // namespace _MinMaxOperation_
using namespace _MinMaxOperation_;
/* #endregion */
/* #region 3*/
/**
 * @file Template.hpp
 * @brief 競技プログラミング用テンプレート
 * @author btk15049
 * @date 2019/05/02
 */


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

int main() {
    const int n = 5;
    vector<int> v(n);
    cin >> v;
    int k;
    cin >> k;
    string ret = "Yay!";
    if (v.back() - v.front() > k) {
        ret = ":(";
    }
    cout << ret << endl;

    return 0;
}