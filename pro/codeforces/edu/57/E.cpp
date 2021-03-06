// https://codeforces.com/problemset/problem/1096/E
#define DECIMAL_DIGITS 10
#define STATIC_MOD 998244353

#ifdef BTK
/*<head>*/
#    include "Template.hpp"
#    include "num/ModInt.hpp"
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
/* #region template/IncludeSTL.hpp*/
/**
 * @file IncludeSTL.hpp
 * @author btk
 * @brief 標準ライブラリをincludeするだけ
 * @version 0.1
 * @date 2019-07-21
 *
 * @copyright Copyright (c) 2019
 *
 */

/*<head>*/
#    pragma once
/*</head>*/


/*<stl>*/
#    include <bits/stdc++.h>
#    include <sys/types.h>
#    include <unistd.h>
using namespace std;
/*</stl>*/
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
/* #region Template.hpp*/
/**
 * @file Template.hpp
 * @brief 競技プログラミング用テンプレート
 * @author btk15049
 * @date 2019/05/02
 */


/* #endregion */
/* #region num/ModInt.hpp*/

#    include <utility>

/**
 * @file ModInt.hpp
 * @brief mod構造体
 * @author btk15049
 * @date 2019/03/08
 * @details
 *  \todo verifyが足りない
 *  verify: CSA12E，RUPC day3 F
 */

//! [WARNING!] mod が入力で与えられる場合はconstexprを外す
#    ifdef STATIC_MOD
constexpr int mod = STATIC_MOD;
#    else
int mod;
#    endif

/**
 * @brief mod構造体
 * @details
 * 整数をラップして，常に保持されているデータがmodされた状態になるよう管理．
 */
class ModInt {
  private:
    //! 中身
    int x;

  public:
    /**
     * @brief ゲッター
     * @details 出力時などは "cout << *ret << endl;"のようにやるとよい．
     */
    long long operator*() const { return x; }
    /**
     * @brief デフォルトコンストラクタ．0で初期化される．
     */
    ModInt() { x = 0; }

    /**
     * @brief intからのコンストラクタ
     * @param[in] y 設定したい値
     * @details
     * modをとらないので高速．ただしmodより大きい値や負の数を入れると事故るので注意．
     */
    ModInt(const int y) { x = y; }

    /**
     * @brief long longからのコンストラクタ
     * @param[in] y 設定したい値
     * @details 毎回modを取るので低速．
     */
    ModInt(const long long y) { x = (int)((mod + y % mod) % mod); }

    /**
     * @brief ModIntからの代入演算子
     * @param[in] o 設定したい値
     * @details 高速
     */
    ModInt(const ModInt& o) { this->x = *o; }
    /**
     * @brief 整数から高速にModIntを作りたいときに使う
     * @param[in] x 設定したい値
     * @details xが[0,mod)であることが保証されてないと正しく動かない．
     */
    static inline ModInt raw(const long long x) {
        // assert(x<mod);
        return ModInt((int)x);
    }

    /**
     * @brief 整数から安全にModIntを作りたいときに使う
     * @param[in] x 設定したい値
     * @details mod2回取るから遅い．負数でもOK．
     */
    static inline ModInt get(const long long x) { return ModInt(x); }

    /**
     * @brief intからの代入演算子
     * @param[in] o 設定したい値
     * @details
     * modをとらないので高速．ただしmodより大きい値や負の数を入れると事故るので注意．
     */
    ModInt& operator=(const int o) {
        this->x = o >= mod ? o - mod : o;
        return *this;
    }

    /**
     * @brief long longからの代入演算子
     * @param[in] o 設定したい値
     * @details mod2回取るから遅い．負数でもOK．
     */
    ModInt& operator=(const long long o) {
        this->x = (int)((mod + o % mod) % mod);
        return *this;
    }

    /**
     * @brief ModIntからの代入演算子
     * @param[in] o 設定したい値
     * @details 高速
     */
    ModInt& operator=(const ModInt o) {
        this->x = *o;
        return *this;
    }
};

/**
 * @param[in] l ModInt
 * @param[in] r ModInt
 * @details if文使って少し高速化．
 */
inline ModInt add(const ModInt l, const ModInt r) {
    const long long x = *l + *r;
    return ModInt::raw(x >= mod ? x - mod : x);
}

/**
 * @param[in] l ModInt
 * @param[in] r ModInt．
 */
inline ModInt mul(const ModInt l, const ModInt r) {
    return ModInt::raw(*l * *r % mod);
}

/**
 * @brief a^x %modを求める
 * @param[in] a ModInt
 * @param[in] x long long．
 */
inline ModInt pow(ModInt a, long long x) {
    ModInt ret = ModInt::raw(1);
    while (x) {
        if (x & 1) {
            ret = mul(ret, a);
        }
        a = mul(a, a);
        x >>= 1;
    }
    return ret;
}

/**
 * @brief x^-1 %modを求める
 * @param[in] x ModInt．
 * @details
 *   内部ではユークリッドの拡張互助法を使っている．
 *   O(log(mod))
 */
inline ModInt inv(const ModInt x) {
    long long a = *x, b = mod, u = 1, v = 0;
    while (b) {
        long long t = a / b;
        std::swap(a -= t * b, b);
        std::swap(u -= t * v, v);
    }
    return ModInt::get(u);
}

/**
 * @brief 負数を求める単項演算子
 * @param[in] x ModInt
 */
inline ModInt operator-(const ModInt x) { return add(mod, -*x); }

/**
 * @param[in] l ModInt
 * @param[in] r ModInt
 */
inline ModInt operator+(const ModInt l, const ModInt r) { return add(l, r); }

/**
 * @param[in] l ModInt
 * @param[in] r ModInt
 */
inline ModInt operator*(const ModInt l, const ModInt r) { return mul(l, r); }

/**
 * @param[in] l ModInt
 * @param[in] r ModInt
 */
inline ModInt operator-(const ModInt l, const ModInt r) { return add(l, -r); }

/**
 * @param[in] l ModInt
 * @param[in] r int
 * @details
 * 右辺は定数を想定しているのでmodをとらないrawを使ってModIntに変換している．ただしmodより大きい値や負の数を入れると事故るので注意．
 */
inline ModInt operator+(const ModInt l, const int r) {
    return add(l, ModInt::raw(r));
}

/**
 * @param[in] l ModInt
 * @param[in] r int
 */
inline ModInt operator+(const ModInt l, const long long r) {
    return add(l, ModInt::get(r));
}

/**
 * @param[in] l ModInt
 * @param[in] r int
 * @details
 * 右辺は定数を想定しているのでmodをとらないrawを使ってModIntに変換している．ただしmodより大きい値や負の数を入れると事故るので注意．
 */
inline ModInt operator*(const ModInt l, const int r) {
    return mul(l, ModInt::raw(r));
}

/**
 * @param[in] l ModInt
 * @param[in] r int
 */
inline ModInt operator*(const ModInt l, const long long r) {
    return mul(l, ModInt::get(r));
}

/**
 * @param[in] l ModInt
 * @param[in] r int
 * @details
 * 右辺は定数を想定しているのでmodをとらないrawを使ってModIntに変換している．ただしmodより大きい値や負の数を入れると事故るので注意．
 */
inline ModInt operator-(const ModInt l, const int r) {
    return add(l, ModInt::raw(mod - r));
}

/**
 * @param[in] l ModInt
 * @param[in] r int
 */
inline ModInt operator-(const ModInt l, const long long r) {
    return add(l, -ModInt::get(r));
}

/**
 * @param[in] l ModInt
 * @param[in] r int
 * @details
 * 右辺は定数を想定しているのでmodをとらないrawを使ってModIntに変換している．ただしmodより大きい値や負の数を入れると事故るので注意．
 */
inline ModInt operator/(const ModInt l, const int r) {
    return mul(l, inv(ModInt::raw(r)));
}

/**
 * @param[in] l ModInt
 * @param[in] r int
 */
inline ModInt operator/(const ModInt l, const long long r) {
    return mul(l, inv(ModInt::get(r)));
}

/**
* @param[in] l ModInt
* @param[in] r long long
* @details
*   pow(l,r)を呼び出すだけなのでpowを参照のこと．
計算量はO(log mod)
*/
inline ModInt operator^(const ModInt l, const long long r) { return pow(l, r); }

/**
 * @brief
 * +=の実装、各operator+を呼ぶだけ
 * @tparam T
 * @param l ModInt
 * @param r 足すやつ
 * @return ModInt&
 */
template <typename T>
ModInt& operator+=(ModInt& l, T r) {
    l = l + r;
    return l;
}

/**
 * @brief
 * -=の実装、各operator-を呼ぶだけ
 * @tparam T
 * @param l ModInt
 * @param r 引くやつ
 * @return ModInt&
 */
template <typename T>
ModInt& operator-=(ModInt& l, T r) {
    l = l - r;
    return l;
}

/**
 * @brief
 * *=の実装、各operator*を呼ぶだけ
 * @tparam T
 * @param l ModInt
 * @param r かけるやつ
 * @return ModInt&
 */
template <typename T>
ModInt& operator*=(ModInt& l, T r) {
    l = l * r;
    return l;
}

/**
 * @namespace factorial
 * @brief 順列数関連の関数のまとめ
 * @details
 *   - combination
 *   - permutation
 *   - multiChoose
 */
namespace factorial {
    //! 順列数を格納する配列のサイズ
    constexpr int size =
#    ifdef FACTORIAL_SIZE
        FACTORIAL_SIZE;
#    else
        3123456;
#    endif
    //! 前計算ができているかどうかのフラグ
    bool is_build = false;

    //! 順列数を格納する配列
    ModInt factorial[size];
    //! (順列数)^-1を格納する配列
    ModInt inverse_factorial[size];

    /**
     * @brief 順列数の前計算
     * @details
     *   順列数と，その逆元を[0,size)まで求める.
     *   計算量は，O(size + log(mod))
     */
    void build() {
        is_build     = true;
        factorial[0] = 1;
        for (int i = 1; i < size; i++) {
            factorial[i] = factorial[i - 1] * i;
        }
        inverse_factorial[size - 1] = inv(factorial[size - 1]);
        for (int i = size - 1; i >= 1; i--) {
            inverse_factorial[i - 1] = inverse_factorial[i] * i;
        }
    }

    /**
     * @brief nPkを求める
     * @details
     *   前計算がしてあれば O(1)．前計算してない場合は is_build
     * を読み取って前計算をする．
     */
    inline ModInt permutation(int n, int k) {
        if (k < 0 || k > n) return ModInt::raw(0);
        if (!is_build) build();
        return factorial[n] * inverse_factorial[n - k];
    }

    /**
     * @brief nCkを求める
     * @details
     *   前計算がしてあれば O(1)．前計算してない場合は is_build
     * を読み取って前計算をする．
     */
    inline ModInt combination(int n, int k) {
        if (k < 0 || k > n) return ModInt::raw(0);
        if (!is_build) build();
        return factorial[n] * inverse_factorial[k] * inverse_factorial[n - k];
    }

    /**
     * @brief 重複組合せ
     * @param n 何種類のものを
     * @param r いくつ並べるか
     * @return ModInt nHr
     */
    ModInt multiChoose(int n, int r) {
        if (n == 0 && r == 0) return ModInt::raw(1);
        return combination(n + r - 1, r);
    }

    /**
     * @brief 上限付き重複組合せ
     * @details
     * 包除原理を用いて，lim個以上の品物が1,2,...,i種類の場合を足したり引いたりしていく
     * 計算量は O(min(n, r / lim))
     * @param n 何種類のものを
     * @param r いくつ並べるか
     * @param lim 1種類のものを選べる上限
     * @return ModInt
     */
    ModInt multiChoose(int n, int r, int lim) {
        ModInt ret = 0;
        for (int i = 0; i <= n; i++) {
            if (i * (lim + 1) > r) break;
            ret += ((i & 1) ? mod - 1 : 1) * combination(n, i)
                   * multiChoose(n, r - i * (lim + 1));
        }
        return ret;
    }

} // namespace factorial
  /* #endregion */
  /* #endregion */
  /*</body>*/
#endif

int main() {
    /* write here */
    int p, s, r;
    scanf("%d%d%d", &p, &s, &r);
    ModInt ret = 0;
    for (int top : range(r, s + 1)) {
        ModInt tot = 0;
        for (int q : range(p)) {
            if (top * q > s - top) break;
            tot +=
                factorial::combination(p - 1, q)
                * factorial::multiChoose(p - q - 1, s - top - top * q, top - 1)
                * inv(q + 1);
        }
        ret += tot;
    }
    ret *= inv(factorial::multiChoose(p, s - r));
    printf("%lld\n", *ret);
    return 0;
}