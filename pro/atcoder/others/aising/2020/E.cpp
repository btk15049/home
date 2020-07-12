// https://atcoder.jp/contests/aising2020/tasks/aising2020_e
#define CIN_ONLY
#define DECIMAL_DIGITS 10
#define STATIC_MOD 1e9 + 7

#ifdef BTK
/*<head>*/
#    include "Template.hpp"
/*</head>*/
#else
/*<body>*/
/* #region auto includes */
/* #region stl */
/*<stl>*/
#    include <bits/stdc++.h>
#    include <sys/types.h>
#    include <unistd.h>
using namespace std;
/*</stl>*/
/* #endregion */
/* #region template/Grid.hpp*/

/**
 * @brief グリッドをラップするための関数
 * @tparam T std::string や std;:vector を想定
 * @tparam U 周りに配置する要素の型
 * @param grid 入力、R > 0 でないとバグる
 * @param material 周りに配置する要素
 * @return std::vector<T> material で 周りを埋めた grid
 */
template <typename T, typename U>
inline std::vector<T> wrapGrid(std::vector<T> grid, U material) {
    std::vector<T> wrappedGrid(grid.size() + 2,
                               T(grid[0].size() + 2, material));
    for (std::size_t i = 0; i < grid.size(); i++) {
        for (std::size_t j = 0; j < grid[i].size(); j++) {
            wrappedGrid[i + 1][j + 1] = grid[i][j];
        }
    }
    return wrappedGrid;
}

/**
 * @brief
 *
 */
constexpr int dr4[] = {0, 1, 0, -1};
constexpr int dc4[] = {-1, 0, 1, 0};
/* #endregion */
/* #region template/Macro.hpp*/
/**
 * @file Macro.hpp
 * @author btk
 * @brief マクロとか，LLとか
 * @version 0.1
 * @date 2019-07-13
 *
 * @copyright Copyright (c) 2019
 *
 */


//! LL
using LL = long long;

/**
 * @def DEBUG
 * @brief デバッグ用のif文 提出時はif(0)で実行されない
 */

/*</head>*/
#    ifdef BTK
#        define DEBUG if (1)
#    else
#        ifdef CIN_ONLY
#            define FAST_IO
#        endif
#        define DEBUG if (0)
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

/**
 * @def VAR_NAME(var)
 * @brief 変数名を取得する
 */
#    define VAR_NAME(var) #    var

/**
 * @brief
 * rangeで生まれる使わない変数を消す用（警告消し）
 */
template <typename T>
inline T& unused_var(T& v) {
    return v;
}

template <typename T>
std::vector<T> nestingVector(std::size_t size) {
    return std::vector<T>(size);
}

template <typename T, typename... Ts>
inline auto nestingVector(std::size_t size, Ts... ts) {
    return std::vector<decltype(nestingVector<T>(ts...))>(
        size, nestingVector<T>(ts...));
}
/* #endregion */
/* #region template/IO.hpp*/
/**
 * @file IO.hpp
 * @author btk
 * @brief cin高速化とか，出力の小数桁固定とか
 * @version 0.1
 * @date 2019-07-13
 *
 * @copyright Copyright (c) 2019
 */


/**
 * @brief 入出力の設定を行うための構造体
 */
struct cww {
    /**
     * @brief Construct a new cww::cww object
     * @details
     * CIN_ONLYを定義すると，submit時にcinとscanfの同期を切る設定が走る
     * DECIMAL_DIGITSを定義すると，doubleの出力時指定した桁数分小数部を吐くようになる
     */
    cww() {
#    ifdef FAST_IO
        std::ios::sync_with_stdio(false);
        std::cin.tie(0);
#    endif
#    ifdef DECIMAL_DIGITS
        std::cout << std::fixed;
        std::cout << std::setprecision(DECIMAL_DIGITS);
#    endif
    }
};

//! 入出力設定構造体を実体化
cww star;

/**
 * @brief
 * vectorに直接cin流すためのやつ
 * @tparam T
 * @param is
 * @param v
 * @return istream&
 */
template <typename T>
std::istream& operator>>(std::istream& is, std::vector<T>& v) {
    for (auto& it : v) is >> it;
    return is;
}
/* #endregion */
/* #region template/IncludeSTL.hpp*/
/**
 * @file IncludeSTL.hpp
 * @author btk
 * @brief 標準ライブラリをincludeするだけ
 * @version 0.1
 * @date 2019-07-21
 * @todo 何故か2回includeされる（展開scriptに
 * @copyright Copyright (c) 2019
 *
 */


/* #endregion */
/* #region template/Loop.hpp*/
/**
 * @file Loop.hpp
 * @author btk
 * @brief rangeとかループ系のクラス
 * @version 0.1
 * @date 2019-07-13
 *
 * @copyright Copyright (c) 2019
 *
 */


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
/* #endregion */
/* #region template/ChainOperation.hpp*/
/**
 * @file ChainOperation.hpp
 * @author btk
 * @brief パラメータパックを利用した演算子結合を実現
 */


/**
 * @brief テンプレート再帰の末尾
 * @tparam F 二項演算
 * @tparam T
 * @param v
 * @return T
 */
template <typename F, typename T>
inline T chain(T&& v) {
    return v;
}

/**
 * @brief 複数項における演算の結果を返す
 * @tparam F
 * @tparam T
 * @tparam Ts
 * @param head
 * @param tail
 * @return T
 */
template <typename F, typename T, typename... Ts>
inline auto chain(const T head, Ts&&... tail) {
    return F::exec(head, chain<F>(tail...));
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
inline bool changeTarget(T& target, Ts&&... candidates) {
    const T old = target;
    target      = chain<F>(target, candidates...);
    return old != target;
}
/* #endregion */
/* #region template/Math.hpp*/
/**
 * @file Math.hpp
 * @author btk
 * @brief 最大値とか最小値を求める
 */

/**
 * @brief gcd, ceil等自作算数用関数を集める。stdと被るので名前空間を区切る
 */
namespace math {

    /**
     * @brief 拡張ユークリッド互除法
     * @details ax + by = gとなるx,yを求める
     * @param a 入力
     * @param b 入力
     * @param x 値引き継ぎ用の変数
     * @param y 値引き継ぎ用の変数
     * @return int64_t g:aとbの最大公約数
     */
    int64_t extgcd(int64_t a, int64_t b, int64_t& x, int64_t& y) {
        int64_t g = a;
        x         = 1;
        y         = 0;
        if (b != 0) g = extgcd(b, a % b, y, x), y -= (a / b) * x;
        return g;
    }

    namespace inner {
        /**
         * @brief 2項のgcdを求める
         * @tparam T
         */
        template <typename T>
        struct GCDFunc {
            /**
             * @brief 本体
             * @param l
             * @param r
             * @return T
             */
            static inline T exec(T l, T r) {
                while (r != 0) {
                    T u = l % r;
                    l   = r;
                    r   = u;
                }
                return l;
            }
        };

        /**
         * @brief 2項のgcdを求める
         * @tparam T
         */
        template <typename T>
        struct LCMFunc {
            /**
             * @brief 本体
             * @param l
             * @param r
             * @return T
             */
            static inline T exec(T l, T r) {
                return (l / GCDFunc<T>::exec(l, r)) * r;
            }
        };

    } // namespace inner

    /**
     * @brief valuesの最大公約数
     * @tparam Ts パラメータパック
     * @param values gcdを求めたい値の集合（2個以上）
     * @return int64 最大公約数
     */
    template <typename... Ts>
    inline int64_t gcd(Ts&&... values) {
        return chain<inner::GCDFunc<int64_t>>(values...);
    }

    /**
     * @brief valuesの最小公倍数
     * @tparam Ts パラメータパック
     * @param values lcmを求めたい値の集合（2個以上）
     * @return int64 最小公倍数
     */
    template <typename... Ts>
    inline int64_t lcm(Ts&&... values) {
        return chain<inner::LCMFunc<int64_t>>(values...);
    }

    /**
     * @brief u/dを切り上げした整数を求める
     * @todo 負の数への対応
     * @tparam T 整数型
     * @param u 入力
     * @param d 入力
     * @return T 切り上げ後の値
     */
    template <typename T>
    inline T ceil(T u, T d) {
        return (u + d - (T)1) / d;
    }

} // namespace math

/**
 * @brief 2項の最小値求める
 * @tparam T
 */
template <typename T>
struct minFunc {
    /**
     * @brief 本体
     * @param l
     * @param r
     * @return T
     */
    static T exec(const T l, const T r) { return l < r ? l : r; }
};

/**
 * @brief 2項の最大値求める
 *
 * @tparam T
 */
template <typename T>
struct maxFunc {
    /**
     * @brief 本体
     *
     * @param l
     * @param r
     * @return T
     */
    static T exec(const T l, const T r) { return l > r ? l : r; }
};

/**
 * @brief 複数項の最小値
 * @see chain
 * @tparam T
 * @tparam Ts
 * @param head
 * @param tail
 * @return T
 */
template <typename T, typename... Ts>
inline T minOf(T head, Ts... tail) {
    return chain<minFunc<T>>(head, tail...);
}

/**
 * @brief 複数項の最大値
 * @see chain
 * @tparam T
 * @tparam Ts
 * @param head
 * @param tail
 * @return T
 */
template <typename T, typename... Ts>
inline T maxOf(T head, Ts... tail) {
    return chain<maxFunc<T>>(head, tail...);
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
    return changeTarget<minFunc<T>>(target, candidates...);
}

/**
 * @brief chminのmax版
 * @see chmin
 * @tparam T 型
 * @param target 変更する値
 * @param candidates
 * @return 更新があればtrue
 */
template <typename T, typename... Ts>
inline bool chmax(T& target, Ts&&... candidates) {
    return changeTarget<maxFunc<T>>(target, candidates...);
}
/* #endregion */
/* #region template/Random.hpp*/
/**
 * @file Random.hpp
 * @author btk
 * @brief 乱数生成系
 * @version 0.1
 * @date 2019-07-13
 * @copyright Copyright (c) 2019
 */


//! 乱数のシード値をプロセスIDとして取得
const pid_t pid = getpid();

/**
 * @brief XorShift32の実装
 */
class XorShift32 {
  private:
    //! XorShiftの現在の値
    unsigned value;

    /**
     * @brief XorShift32のアルゴリズムに基づいて value を更新
     */
    inline void update() {
        value = value ^ (value << 13);
        value = value ^ (value >> 17);
        value = value ^ (value << 5);
    }

    /**
     * @brief 値を更新し，更新前の値を返却
     * @return unsigned 呼び出し時の value を用いる
     */
    inline unsigned get() {
        unsigned v = value;
        update();
        return v;
    }

  public:
    /**
     * @brief [0, 2^bit) の範囲の乱数値を取り出す
     * @tparam デフォルトは31
     * @return int
     */
    template <int bit = 31>
    inline int next_int() {
        return (int)(get() >> (32 - bit));
    }

    /**
     * @brief [-2^bit,2^bit)の範囲の乱数値を取り出す
     * @tparam デフォルトは31
     * @return int
     */
    template <int bit = 31>
    inline int next_signed() {
        unsigned v = get();
        return (int)((v >> (31 - bit)) - (1 << (bit)));
    }

    /**
     * @brief next_int呼び出し時の最大値を取得
     * @tparam 31
     * @return int
     */
    template <int bit = 31>
    inline int range_max() {
        return (int)((1u << bit) - 1);
    };

    /**
     * @brief Construct a new XorShift32 object
     * @param seed
     * @details 初期シードをvalueとするXorShift32のインスタンスを生成
     */
    XorShift32(const unsigned seed) {
        value = seed;
        update();
    }

    /**
     * @brief Construct a new XorShift 32 object
     * @details 初期シードをプロセスIDとするXorShift32のインスタンスを生成
     */
    XorShift32() : XorShift32(pid) {}
};
/* #endregion */
/* #region template/Strings.hpp*/
/**
 * @file Strings.hpp
 * @author btk
 * @brief 文字列を扱いやすくするライブラリ
 */


/**
 * @brief コレクションを文字列に変換する関数
 * @tparam T コレクションの型、range-based for に対応している必要あり
 * @tparam DelimiterType 区切り文字の型
 * @param v コレクション
 * @param delimiter 区切り文字
 * @return std::string delimiterで結合された文字列
 */
template <typename T, typename DelimiterType>
std::string join(const T& v, const DelimiterType& delimiter) {
    std::stringstream ss;
    bool isFirst = true;
    for (auto& it : v) {
        if (!isFirst) {
            ss << delimiter;
        }
        isFirst = false;
        ss << it;
    }
    return ss.str();
}

/**
 * @brief コレクションを文字列に変換する関数（イテレータ版）
 * @tparam ITR イテレータ型
 * @tparam DelimiterType 区切り文字の型
 * @param bg 開始
 * @param ed 終了
 * @param delimiter 区切り文字
 * @return std::string delimiterで結合された文字列
 */
template <typename ITR, typename DelimiterType>
std::string join(const ITR bg, const ITR ed, const DelimiterType& delimiter) {
    std::stringstream ss;
    bool isFirst = true;
    for (auto it = bg; it != ed; ++it) {
        if (!isFirst) {
            ss << delimiter;
        }
        isFirst = false;
        ss << *it;
    }
    return ss.str();
}

/**
 * @brief Strings.hppの内部関数
 */
namespace strings {

    /**
     * @brief std::size_tをWrapする構造体
     * @tparam i 本体
     */
    template <std::size_t i>
    struct IndexWrapper {};

    /**
     * @brief tuple用のjoin関数の内部で使われるテンプレート構造体（関数）
     * @tparam CurrentIndex 現在のindex
     * @tparam LastIndex 最後のindex
     * @tparam DelimiterType 区切り文字
     * @tparam Ts tupleに使用するパラメータパック
     */
    template <typename CurrentIndex, typename LastIndex, typename DelimiterType,
              typename... Ts>
    struct JoinFunc;


    /**
     * @brief tuple用join関数の再帰末尾用構造体 .joinが本体
     * @tparam i 現在のid = tupleの最後の要素のid
     * @tparam DelimiterType 区切り文字
     * @tparam Ts tupleに使用するパラメータパック
     */
    template <std::size_t i, typename DelimiterType, typename... Ts>
    struct JoinFunc<IndexWrapper<i>, IndexWrapper<i>, DelimiterType, Ts...> {
        /**
         * @brief tuple用join関数の末尾再帰
         * @param ss stringstream
         * @param values 文字列化したいtuple
         * @param delimiter 区切り文字
         * @return std::stringstream& 引数で渡したもの
         */
        static std::stringstream& join(std::stringstream& ss,
                                       const std::tuple<Ts...>& values,
                                       const DelimiterType& delimiter) {
            unused_var(delimiter);
            ss << std::get<i>(values);
            return ss;
        }
    };

    /**
     * @brief tuple用join関数の内部構造体
     * @tparam i 現在のid
     * @tparam j tupleの最後の要素のid
     * @tparam DelimiterType 区切り文字
     * @tparam Ts パラメータパック
     */
    template <std::size_t i, std::size_t j, typename DelimiterType,
              typename... Ts>
    struct JoinFunc<IndexWrapper<i>, IndexWrapper<j>, DelimiterType, Ts...> {
        /**
         * @brief tuple用join関数の本体
         * @param ss stringstream
         * @param values 文字列化したいtuple
         * @param delimiter 区切り文字
         * @return std::stringstream& 引数で渡したもの
         */
        static std::stringstream& join(std::stringstream& ss,
                                       const std::tuple<Ts...>& values,
                                       const DelimiterType& delimiter) {
            ss << std::get<i>(values);
            ss << delimiter;
            return JoinFunc<IndexWrapper<i + 1>, IndexWrapper<j>, DelimiterType,
                            Ts...>::join(ss, values, delimiter);
        }
    };
} // namespace strings


/**
 * @brief 複数の値をjoinする関数
 * @tparam DelimiterType 区切り文字の型
 * @tparam Ts パラメータパック
 * @param values 文字列として結合したいタプル
 * @param delimiter 区切り文字
 * @return std::string 結合後の文字列
 */
template <typename DelimiterType, typename... Ts>
std::string join(const std::tuple<Ts...>& values,
                 const DelimiterType& delimiter) {
    std::stringstream ss;
    constexpr std::size_t lastIndex =
        std::tuple_size<std::tuple<Ts...>>::value - 1u;
    return strings::JoinFunc<strings::IndexWrapper<0>,
                             strings::IndexWrapper<lastIndex>, DelimiterType,
                             Ts...>::join(ss, values, delimiter)
        .str();
}
/* #endregion */
/* #region Template.hpp*/
/**
 * @file Template.hpp
 * @brief 競技プログラミング用テンプレート
 * @author btk15049
 * @date 2019/05/02
 */


/* #endregion */
/* #endregion */
/*</body>*/
#endif

LL maximize(vector<vector<LL>>& v, int n) {
    LL ret = 0;
    priority_queue<LL> que;
    for (int i : range(n + 1, v.size())) {
        for (auto e : v[i]) {
            que.push(e);
        }
    }
    for (int i : !range(n)) {
        for (auto e : v[i + 1]) {
            que.push(e);
        }
        if (!que.empty()) {
            ret += que.top();
            que.pop();
        }
    }
    return ret;
}

void solve() {
    int N;
    cin >> N;
    vector<vector<LL>> L(N + 1), R(N + 1);
    int ln = 0, rn = 0;
    LL base = 0;
    for (int i : range(N)) {
        int k;
        LL l, r;
        cin >> k >> l >> r;
        LL t = min(l, r);
        base += t;
        l -= t;
        r -= t;

        if (l) {
            L[k].push_back(l);
            ln++;
        }
        if (r) {
            R[N - k].push_back(r);
            rn++;
        }
    }
    cout << base + maximize(L, ln) + maximize(R, rn) << "\n";
}

int main() {
    /* write here */

    int T;
    cin >> T;
    while (T--) {
        solve();
    }


    return 0;
}