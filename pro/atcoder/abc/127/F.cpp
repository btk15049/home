// https://atcoder.jp/contests/abc127/tasks/abc127_f
#define CIN_ONLY
#define DECIMAL_DIGITS 10
#define STATIC_MOD 1e9 + 7

#ifdef BTK
/*<head>*/
#    include "Template.hpp"
#    include "structure/BinaryIndexedTree.hpp"
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
/* #region template/Math.hpp*/

/**
 * @brief gcd, ceil等自作算数用関数を集める。stdと被るので名前空間を区切る
 */
namespace math {

    /**
     * @brief aとｂの最大公約数
     * @param a int64
     * @param b int64
     * @return int64 最大公約数
     */
    int64_t gcd(int64_t a, int64_t b) { return (b == 0) ? a : gcd(b, a % b); }

    /**
     * @brief aとｂの最小公倍数
     * @param a int64
     * @param b int64
     * @return int64 最小公倍数
     */
    int64_t lcm(int64_t a, int64_t b) { return (a / gcd(a, b)) * b; }


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
/* #endregion */
/* #region template/MinMaxOperation.hpp*/
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

/**
 * @brief 2項の最小値求める
 *
 * @tparam T
 */
template <typename T>
struct min_op {
    /**
     * @brief 本体
     *
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
struct max_op {
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
inline T multi_min(T head, Ts... tail) {
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
inline T multi_max(T head, Ts... tail) {
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
 * @version 0.1
 * @date 2020-02-02
 *
 * @copyright Copyright (c) 2020
 *
 */


/**
 * @brief コレクションを文字列に変換する関数
 * @tparam T コレクションの型、range-based for に対応している必要あり
 * @tparam U 区切り文字の型
 * @param v コレクション
 * @param delimiter 区切り文字
 * @return std::string delimiterで結合された文字列
 */
template <typename T, typename U>
std::string join(const T& v, const U delimiter) {
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
 * @tparam T 区切り文字の型
 * @param bg 開始
 * @param ed 終了
 * @param delimiter 区切り文字
 * @return std::string delimiterで結合された文字列
 */
template <typename ITR, typename T>
std::string join(const ITR bg, const ITR ed, const T delimiter) {
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
/* #endregion */
/* #region Template.hpp*/
/**
 * @file Template.hpp
 * @brief 競技プログラミング用テンプレート
 * @author btk15049
 * @date 2019/05/02
 */


/* #endregion */
/* #region structure/BinaryIndexedTree.hpp*/

/**
 * @brief BinaryIndexedTreeの演算を抽象化したクラス。
 * 演算の型をtemplateに埋め込む必要があるため、宣言が大変。
 * そのために名前空間BinaryIndexedTreePreset
 * が用意してあり、基本的にはそちらを使うと良い。
 *
 * @tparam T 扱うデータの型
 * @tparam AddOperation
 * 加算に相当する演算、関数オブジェクトを作ってdecltypeをするとよい
 * @tparam InvOperation
 * 逆元を取るための単項演算子に相当する演算、関数オブジェクトを作ってdecltypeをするとよい
 */
template <typename T, typename AddOperation, typename InvOperation>
class BinaryIndexedTree {
  private:
    const int _size;
    const AddOperation addOperation;
    const InvOperation invOperation;
    const std::unique_ptr<T[]> value;

  public:
    BinaryIndexedTree(int _size, AddOperation addOperation,
                      InvOperation invOperation, T zero);
    /**
     * @brief [0, _size) の範囲を持つBITを生成する（特殊化の実装が必要）
     * @param _size 要素数
     */
    BinaryIndexedTree(int _size);

    /**
     * @brief コンストラクタで指定したBITに格納できる要素数を取得する
     *
     * @return int 要素数
     */
    int size() const;

    /**
     * @brief 位置idにvを加算する
     *
     * @param id 位置
     * @param v 加算する値
     */
    void add(int id, T v);

    /**
     * @brief [0,n) に加算された値の総和を計算する
     *
     * @param n パラメータ
     * @return T 総和
     */
    T sum(int n) const;

    /**
     * @brief [l,r) に加算された値の総和を計算する
     *
     * @param l パラメータ
     * @param r パラメータ
     * @return T 総和
     */
    T sum(int l, int r) const;

    /**
     * @brief v[0]+v[1]+...+v[x]>=wとなる最小のxを求める
     * @param w
     * @return int32_t x
     */
    int32_t lowerBound(T w) const;

  private:
    void _add(int id, T v);
    T _sum(int id) const;

    // v[1]+v[2]+...+v[x]>=wとなる最小のxを求める
    // int lowerbound(T w) {
    // }
};

namespace BinaryIndexedTreePreset {
    namespace Int {
        using type = int32_t;
        namespace Sum {
            const auto add      = [](type l, type r) { return l + r; };
            const auto inv      = [](type v) { return -v; };
            constexpr type zero = 0;
            using Preset =
                BinaryIndexedTree<type, decltype(add), decltype(inv)>;
        } // namespace Sum
        namespace Xor {
            const auto add      = [](type l, type r) { return l ^ r; };
            const auto inv      = [](type v) { return v; };
            constexpr type zero = 0;
            using Preset =
                BinaryIndexedTree<type, decltype(add), decltype(inv)>;
        } // namespace Xor
        namespace Max {
            const auto add      = [](type l, type r) { return l > r ? l : r; };
            const auto inv      = [](type v) { return -v; };
            constexpr type zero = 0;
            using Preset =
                BinaryIndexedTree<type, decltype(add), decltype(inv)>;
        } // namespace Max

    } // namespace Int

    namespace Long {
        using type = int64_t;
        namespace Sum {
            const auto add      = [](type l, type r) { return l + r; };
            const auto inv      = [](type v) { return -v; };
            constexpr type zero = 0;
            using Preset =
                BinaryIndexedTree<type, decltype(add), decltype(inv)>;
        } // namespace Sum

        namespace Xor {
            const auto add      = [](type l, type r) { return l ^ r; };
            const auto inv      = [](type v) { return v; };
            constexpr type zero = 0;
            using Preset =
                BinaryIndexedTree<type, decltype(add), decltype(inv)>;
        } // namespace Xor

    } // namespace Long
} // namespace BinaryIndexedTreePreset

/**
 * @brief int32, 加算を行うBIT の特殊化実装, Presetを使う用に定義
 * @param _size
 * @return [0, size) の範囲を扱うBIT
 */
template <>
BinaryIndexedTree<BinaryIndexedTreePreset::Int::type,
                  decltype(BinaryIndexedTreePreset::Int::Sum::add),
                  decltype(BinaryIndexedTreePreset::Int::Sum::inv)>::
    BinaryIndexedTree(int _size);

/**
 * @brief int64, 加算を行うBIT の特殊化実装, Presetを使う用に定義
 * @param _size
 * @return [0, size) の範囲を扱うBIT
 */
template <>
BinaryIndexedTree<BinaryIndexedTreePreset::Long::type,
                  decltype(BinaryIndexedTreePreset::Long::Sum::add),
                  decltype(BinaryIndexedTreePreset::Long::Sum::inv)>::
    BinaryIndexedTree(int _size);

/**
 * @brief int64, 加算を行うBIT の特殊化実装, Presetを使う用に定義
 * @param _size
 * @return [0, size) の範囲を扱うBIT
 */
template <>
BinaryIndexedTree<BinaryIndexedTreePreset::Int::type,
                  decltype(BinaryIndexedTreePreset::Int::Max::add),
                  decltype(BinaryIndexedTreePreset::Int::Max::inv)>::
    BinaryIndexedTree(int _size);

/**
 * @brief int32, xor演算を行うBIT の特殊化実装, Presetを使う用に定義
 * @param _size
 * @return [0, size) の範囲を扱うBIT
 */
template <>
BinaryIndexedTree<BinaryIndexedTreePreset::Int::type,
                  decltype(BinaryIndexedTreePreset::Int::Xor::add),
                  decltype(BinaryIndexedTreePreset::Int::Xor::inv)>::
    BinaryIndexedTree(int _size);


/**
 * @brief int64, xor演算を行うBIT の特殊化実装, Presetを使う用に定義
 * @param _size
 * @return [0, size) の範囲を扱うBIT
 */
template <>
BinaryIndexedTree<BinaryIndexedTreePreset::Long::type,
                  decltype(BinaryIndexedTreePreset::Long::Xor::add),
                  decltype(BinaryIndexedTreePreset::Long::Xor::inv)>::
    BinaryIndexedTree(int _size);

/**
 * @brief v[0]+v[1]+...+v[x]>=wとなる最小のxを求める
 * @param w
 * @return int32_t x
 */
template <>
int32_t BinaryIndexedTree<BinaryIndexedTreePreset::Long::type,
                          decltype(BinaryIndexedTreePreset::Long::Sum::add),
                          decltype(BinaryIndexedTreePreset::Long::Sum::inv)>::
    lowerBound(BinaryIndexedTreePreset::Long::type w) const;

// ######################################################################################
// //


template <typename T, typename AddOperation, typename InvOperation>
BinaryIndexedTree<T, AddOperation, InvOperation>::BinaryIndexedTree(
    int _size, AddOperation addOperation, InvOperation invOperation, T zero)
    : _size(_size),
      addOperation(addOperation),
      invOperation(invOperation),
      value(new T[_size + 1]) {
    for (int i = 0; i <= _size; i++) {
        value[i] = zero;
    }
}

template <typename T, typename AddOperation, typename InvOperation>
int BinaryIndexedTree<T, AddOperation, InvOperation>::size() const {
    return _size;
}


template <typename T, typename AddOperation, typename InvOperation>
void BinaryIndexedTree<T, AddOperation, InvOperation>::_add(int id, T v) {
    while (id <= _size) {
        value[id] = addOperation(value[id], v);
        id += id & -id;
    }
}

template <typename T, typename AddOperation, typename InvOperation>
T BinaryIndexedTree<T, AddOperation, InvOperation>::_sum(int id) const {
    T s = 0;
    while (id > 0) {
        s = addOperation(s, value[id]);
        id -= id & -id;
    }
    return s;
}

template <typename T, typename AddOperation, typename InvOperation>
T BinaryIndexedTree<T, AddOperation, InvOperation>::sum(int id) const {
    return _sum(id);
}

template <typename T, typename AddOperation, typename InvOperation>
T BinaryIndexedTree<T, AddOperation, InvOperation>::sum(int l, int r) const {
    return addOperation(_sum(r), invOperation(_sum(l)));
}

template <typename T, typename AddOperation, typename InvOperation>
void BinaryIndexedTree<T, AddOperation, InvOperation>::add(int id, T v) {
    return _add(id + 1, v);
}


template <>
BinaryIndexedTree<BinaryIndexedTreePreset::Int::type,
                  decltype(BinaryIndexedTreePreset::Int::Sum::add),
                  decltype(BinaryIndexedTreePreset::Int::Sum::inv)>::
    BinaryIndexedTree(int _size)
    : BinaryIndexedTree(_size, BinaryIndexedTreePreset::Int::Sum::add,
                        BinaryIndexedTreePreset::Int::Sum::inv,
                        BinaryIndexedTreePreset::Int::Sum::zero) {}

template <>
BinaryIndexedTree<BinaryIndexedTreePreset::Int::type,
                  decltype(BinaryIndexedTreePreset::Int::Max::add),
                  decltype(BinaryIndexedTreePreset::Int::Max::inv)>::
    BinaryIndexedTree(int _size)
    : BinaryIndexedTree(_size, BinaryIndexedTreePreset::Int::Max::add,
                        BinaryIndexedTreePreset::Int::Max::inv,
                        BinaryIndexedTreePreset::Int::Max::zero) {}

template <>
BinaryIndexedTree<BinaryIndexedTreePreset::Long::type,
                  decltype(BinaryIndexedTreePreset::Long::Sum::add),
                  decltype(BinaryIndexedTreePreset::Long::Sum::inv)>::
    BinaryIndexedTree(int _size)
    : BinaryIndexedTree(_size, BinaryIndexedTreePreset::Long::Sum::add,
                        BinaryIndexedTreePreset::Long::Sum::inv,
                        BinaryIndexedTreePreset::Long::Sum::zero) {}

template <>
BinaryIndexedTree<BinaryIndexedTreePreset::Int::type,
                  decltype(BinaryIndexedTreePreset::Int::Xor::add),
                  decltype(BinaryIndexedTreePreset::Int::Xor::inv)>::
    BinaryIndexedTree(int _size)
    : BinaryIndexedTree(_size, BinaryIndexedTreePreset::Int::Xor::add,
                        BinaryIndexedTreePreset::Int::Xor::inv,
                        BinaryIndexedTreePreset::Int::Xor::zero) {}

template <>
BinaryIndexedTree<BinaryIndexedTreePreset::Long::type,
                  decltype(BinaryIndexedTreePreset::Long::Xor::add),
                  decltype(BinaryIndexedTreePreset::Long::Xor::inv)>::
    BinaryIndexedTree(int _size)
    : BinaryIndexedTree(_size, BinaryIndexedTreePreset::Long::Xor::add,
                        BinaryIndexedTreePreset::Long::Xor::inv,
                        BinaryIndexedTreePreset::Long::Xor::zero) {}


template <>
int32_t BinaryIndexedTree<BinaryIndexedTreePreset::Long::type,
                          decltype(BinaryIndexedTreePreset::Long::Sum::add),
                          decltype(BinaryIndexedTreePreset::Long::Sum::inv)>::
    lowerBound(BinaryIndexedTreePreset::Long::type w) const {
    if (w <= 0) return 0;
    int32_t x = 0;
    for (int k = (1 << (31 - __builtin_clz(_size))); k > 0; k >>= 1)
        if (x + k <= _size && value[x + k] < w) {
            w -= value[x + k];
            x += k;
        }
    return x;
}
/* #endregion */
/* #endregion */
/*</body>*/
#endif

LL latte[212345];
int malta = 0;

int t[212345];
int a[212345];
int b[212345];

int main() {
    /* write here */
    int Q;
    cin >> Q;
    for (int i : range(Q)) {
        cin >> t[i];
        if (t[i] == 1) {
            cin >> a[i] >> b[i];
            latte[malta++] = a[i];
        }
        else {
        }
    }

    sort(latte, latte + malta);
    malta = unique(latte, latte + malta) - latte;
    using namespace BinaryIndexedTreePreset::Long::Sum;
    Preset inserted(malta + 10);

    LL B = 0;
    Preset d(malta + 10);
    set<int> s;
    for (int i : range(Q)) {
        if (t[i] == 1) {
            B += b[i];
            int ap = lower_bound(latte, latte + malta, a[i]) - latte;
            d.add(ap, a[i]);
            inserted.add(ap, 1);
            s.insert(ap);
        }
        else {
            int inserted_all = inserted.sum(malta + 5);
            int c            = inserted.lowerBound((inserted_all) / 2);
            vector<int> cs(1, c);
            {
                auto it = s.lower_bound(c);
                if (it != s.begin()) {
                    it = prev(it);
                    cs.push_back(*it);
                }
                if (it != s.begin()) {
                    it = prev(it);
                    cs.push_back(*it);
                }
            }
            {
                auto it = next(s.lower_bound(c));
                if (it != s.end()) {
                    cs.push_back(*it);
                }
                it = next(it);
                if (it != s.end()) {
                    cs.push_back(*it);
                }
            }
            vector<LL> ret{(LL)1e18, 0};
            for (auto x : cs) {
                // cout << x << "-" << latte[x - 1] << endl;
                vector<LL> ans{B, latte[x]};
                ans[0] +=
                    d.sum(x, malta + 5) - inserted.sum(x, malta + 5) * latte[x];
                ans[0] += inserted.sum(x) * latte[x] - d.sum(x);


                chmin(ret, ans);
            }
            reverse(ALL(ret));
            cout << join(ret, ' ') << endl;
        }
    }
    return 0;
}