// https://atcoder.jp/contests/abc129/tasks/abc129_e
/*<head>*/
// #include "ModInt.hpp"
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
/* #region 2*/

/**
 * @file ModInt.hpp
 * @brief mod構造体
 * @author btk15049
 * @date 2019/03/08
 * @datails
 *  \todo verifyが足りない
 *  verify: CSA12E，RUPC day3 F
 */

//! [WARNING!] mod が入力で与えられる場合はconstexprを外す
constexpr int mod = 1e9 + 7;

namespace _ModInt_ {
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
            swap(a -= t * b, b);
            swap(u -= t * v, v);
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
    inline ModInt operator+(const ModInt l, const ModInt r) {
        return add(l, r);
    }

    /**
     * @param[in] l ModInt
     * @param[in] r ModInt
     */
    inline ModInt operator*(const ModInt l, const ModInt r) {
        return mul(l, r);
    }

    /**
     * @param[in] l ModInt
     * @param[in] r ModInt
     */
    inline ModInt operator-(const ModInt l, const ModInt r) {
        return add(l, -r);
    }

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
    inline ModInt operator^(const ModInt l, const long long r) {
        return pow(l, r);
    }

    /**
     * @namespace factorial
     * @brief 順列数関連の関数のまとめ
     * @details
     *   - combination
     *   - permutation
     */
    namespace factorial {
        //! 順列数を格納する配列のサイズ
        constexpr int size = 1123456;

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
            return factorial[n] * inverse_factorial[k]
                   * inverse_factorial[n - k];
        }
    } // namespace factorial
} // namespace _ModInt_
using namespace _ModInt_;
/* #endregion */
/* #endregion */
/*</body>*/
int S[112345];
int SS(int l, int r) { return S[r] - S[l]; }

int main() {
    string s;
    cin >> s;
    ModInt ret = 1;
    int N      = s.size();

    for (int i : range(N)) {
        S[i + 1] += S[i];
        if (s[i] == '1') {
            S[i + 1]++;
        }
    }
    for (int i : range(N)) {
        if (s[i] == '1') {
            ret = ret + (ModInt(2) ^ SS(0, i + 1));
        }
        if (i == 0) continue;
        ModInt pre = (ModInt(2) ^ SS(0, i)) - 1;
        ModInt lst = ModInt(3) ^ (N - i - 1);
        ret        = ret + pre * 2 * lst;
    }

    std::cout << *ret << endl;
    return 0;
}