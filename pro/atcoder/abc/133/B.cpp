// https://atcoder.jp/contests/abc133/tasks/abc133_b
#include <bits/stdc++.h>
#include <sys/types.h>
#include <unistd.h>
#define CIN_ONLY
#define DECIMAL_DIGITS 10

#ifdef BTK
/*<head>*/
#    include "Template.hpp"
#    include "num/Matrix.hpp"
/*</head>*/
#else
/*<body>*/
/* #region header */
/* #region 1*/
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


using namespace std;

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
 * @brief
 * rangeで生まれる使わない変数を消す用（警告消し）
 */
template <typename T>
inline T& unused_var(T& v) {
    return v;
}
/* #endregion */
/* #region 2*/
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
        ios::sync_with_stdio(false);
        cin.tie(0);
#    endif
#    ifdef DECIMAL_DIGITS
        cout << fixed;
        cout << setprecision(DECIMAL_DIGITS);
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
istream& operator>>(istream& is, vector<T>& v) {
    for (auto& it : v) is >> it;
    return is;
}
/* #endregion */
/* #region 3*/
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
/* #region 4*/
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
/* #endregion */
/* #region 5*/
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
/* #region 6*/
/**
 * @file Template.hpp
 * @brief 競技プログラミング用テンプレート
 * @author btk15049
 * @date 2019/05/02
 */

/* #endregion */
/* #region 7*/
/**
 * @file Matrix.hpp
 * @author btk
 * @brief 行列累乗
 * @version 0.1
 * @date 2019-06-10
 *
 * @copyright Copyright (c) 2019
 *
 */


#    include <array>

/**
 * @brief
 * 行列クラス
 * @tparam T
 * @tparam row_size 縦
 * @tparam col_size 横
 * @details
 * 速度が気になるようであればバッファ管理はarrayからNDRangeに変えるかも
 */
template <typename T, size_t row_size, size_t col_size>
class Matrix {
  public:
    //! 行サイズを4の倍数に
    static constexpr int fixed_col_size = ((col_size + 3) / 4) * 4;
    //! 列サイズを4の倍数に
    static constexpr int fixed_row_size = ((row_size + 3) / 4) * 4;
    //! 行ベクトル 横
    using col_array = array<T, fixed_col_size>;
    //! 列ベクトル 縦
    using row_array = array<T, fixed_row_size>;
    //! 行列
    using matrix = array<col_array, row_size>;

  private:
    //! 本体
    matrix value;

  public:
    /**
     * @brief
     * idx行目の行ベクトルの参照を取得
     * @param idx
     * @return col_array&
     */
    inline col_array& operator[](const int idx) { return value[idx]; }
};

/**
 * @brief
 * 行列積
 * @tparam T
 * @tparam r1
 * @tparam c1
 * @tparam c2
 * @param in1
 * @param in2
 * @param out
 */
template <typename T, size_t r1, size_t c1, size_t c2>
void mul(Matrix<T, r1, c1>& in1, Matrix<T, c1, c2>& in2,
         Matrix<T, r1, c2>& out) {
    for (int i : range(r1)) {
        for (int j : range(c2)) {
            out[i][j] = 0;
        }
    }
    T sum[4], tmp;
    for (int k : range(c1)) {
        for (size_t i = 0; i < r1; i += 4) {
            sum[0] = in1[i][k];
            sum[1] = in1[i + 1][k];
            sum[2] = in1[i + 2][k];
            sum[3] = in1[i + 3][k];
            for (int j : range(c2)) {
                tmp = in2[k][j];
                out[i + 0][j] += sum[0] * tmp;
                out[i + 1][j] += sum[1] * tmp;
                out[i + 2][j] += sum[2] * tmp;
                out[i + 3][j] += sum[3] * tmp;
            }
        }
    }
}

/**
 * @brief
 * 行列とベクトルの積
 * @tparam T
 * @tparam r
 * @tparam c
 * @param m
 * @param in
 * @param out
 */
template <typename T, size_t r, size_t c>
inline void mul(Matrix<T, r, c> m, array<T, c> in, array<T, r>& out) {
    for (int i : range(r)) {
        out[i] = 0;
        for (int j : range(c)) {
            out[i] += m[i][j] * in[j];
        }
    }
}

/**
 * @brief
 * 行列累乗用のクラス
 * @tparam T
 * @tparam r
 * @tparam size = 64
 */
template <typename T, size_t r, int size = 64>
class Chain {
    using matrix = Matrix<T, r, r>;
    using vec    = array<T, r>;

  private:
    matrix bin[size];

  public:
    /**
     * @brief Construct a new Chain object
     * 行列累乗用にビルドをしておく
     * @param m
     */
    Chain(matrix m) {
        bin[0] = m;
        for (int i : range(1, size)) {
            mul(bin[i - 1], bin[i - 1], bin[i]);
        }
    }

    /**
     * @brief
     * コンストラクタで与えた正方行列を M,
     * 引数のベクトルを v として M^n * v を計算
     * @param v
     * @param n
     * @return vec
     * @details
     * O(r^2 log n)
     */
    vec compute(vec v, unsigned long long n) {
        for (int i = 0; n > 0; i++, n >>= 1) {
            if (n & 1) {
                vec nv;
                mul(bin[i], v, nv);
                swap(v, nv);
            }
        }
        return v;
    }
};
/* #endregion */
/* #endregion */
/*</body>*/
#endif

int X[10][10];
int main() {
    int N, D;
    cin >> N >> D;
    for (int i : range(N)) {
        for (int j : range(D)) {
            cin >> X[i][j];
        }
    }
    int ret = 0;
    for (int i : range(N)) {
        for (int j : range(i + 1, N)) {
            int c = 0;
            for (int k : range(D)) {
                c += (X[i][k] - X[j][k]) * (X[i][k] - X[j][k]);
            }
            int d = sqrt(c);
            ret += (d * d == c) ? 1 : 0;
        }
    }
    cout << ret << endl;
    return 0;
}