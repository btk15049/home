//
#include <bits/stdc++.h>
#include <sys/types.h>
#include <unistd.h>
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
/* #endregion */
/*</body>*/
#endif


XorShift32 rdGen;

namespace IN {
    int N;
    int like[3];
    int lb[30][30];
    int ub[30][30];
    void init() {
        cin >> N;
        for (int i : range(3)) {
            cin >> like[i];
        }
        for (int i : range(N)) {
            for (int j : range(N)) {
                cin >> lb[i][j];
            }
        }
        for (int i : range(N)) {
            for (int j : range(N)) {
                cin >> ub[i][j];
                ub[i][j]++;
            }
        }
    }
} // namespace IN

string to_string(vector<int> v) {
    string ret = to_string(v.front());
    for (int i : range(1, v.size())) {
        ret += "," + to_string(v[i]);
    }
    return ret;
}

namespace SV {
    int B[30][30];

    int dp[30][10][10][10][10][10];
    int ch[30][10][10][10][10][10];

    inline int Copt(const int col) {
        using namespace IN;
        /* #region  loop*/
        for (int a : range(lb[col][0], ub[col][0])) {
            for (int b : range(lb[col][1], ub[col][1])) {
                for (int c : range(lb[col][2], ub[col][2])) {
                    for (int d : range(lb[col][3], ub[col][3])) {
                        for (int e : range(lb[col][4], ub[col][4])) {
                            int &target = dp[0][a][b][c][d][e];
                            target      = 0;
                            int S[5]    = {a, b, c, d, e};
                            for (int i : range(4)) {
                                int s = S[i];
                                for (int j : range(i + 1, 5)) {
                                    s += S[j];
                                    if (s == like[0]) target += like[0];
                                    if (s == like[1]) target += like[1];
                                    if (s == like[2]) target += like[2];
                                }
                            }
                            // cerr << to_string({a, b, c, d, e}) << " " <<
                            // target
                            //     << endl;
                            //;
                        }
                    }
                }
            }
        }
        /* #endregion  */

        /* #region loop */
        for (int i : range(0, N - 5)) {
            memset(dp[i + 1], -1, 100000 * sizeof(int));
            for (int a : range(lb[col][i + 0], ub[col][i + 0])) {
                for (int b : range(lb[col][i + 1], ub[col][i + 1])) {
                    for (int c : range(lb[col][i + 2], ub[col][i + 2])) {
                        for (int d : range(lb[col][i + 3], ub[col][i + 3])) {
                            for (int e :
                                 range(lb[col][i + 4], ub[col][i + 4])) {
                                for (int f :
                                     range(lb[col][i + 5], ub[col][i + 5])) {
                                    int &pre = dp[i][a][b][c][d][e];
                                    int &nxt = dp[i + 1][b][c][d][e][f];
                                    int ans  = pre;
                                    int S[5] = {e, d, c, b, a};
                                    int s    = f;
                                    for (int j : range(5)) {
                                        s += S[j];
                                        if (s == like[0]) ans += like[0];
                                        if (s == like[1]) ans += like[1];
                                        if (s == like[2]) ans += like[2];
                                    }
                                    if (chmax(nxt, ans)) {
                                        ch[i + 1][b][c][d][e][f] = a;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        /* #endregion loop */

        /* #region  */
        pair<int, vector<int>> top(-1, {});
        int i = N - 5;
        for (int a : range(lb[col][i + 0], ub[col][i + 0])) {
            for (int b : range(lb[col][i + 1], ub[col][i + 1])) {
                for (int c : range(lb[col][i + 2], ub[col][i + 2])) {
                    for (int d : range(lb[col][i + 3], ub[col][i + 3])) {
                        for (int e : range(lb[col][i + 4], ub[col][i + 4])) {
                            chmax(top, make_pair(dp[i][a][b][c][d][e],
                                                 vector<int>{a, b, c, d, e}));
                        }
                    }
                }
            }
        }
        auto cur = top.second;
        for (int j : range(5)) {
            B[col][i + j] = cur[j];
        }

        while (i > 0) {
            int b = cur[0];
            int c = cur[1];
            int d = cur[2];
            int e = cur[3];
            int f = cur[4];
            int a = ch[i][b][c][d][e][f];
            cur   = {a, b, c, d, e};
            i--;
            B[col][i] = a;
            // for (int j : range(5)) cerr << cur[j] << " ";
            // cerr << endl;
        }
        /* #endregion */
        return top.first;
    } // namespace SV

    int rsc(int p) {
        using namespace IN;
        int ret = 0;
        for (int i : range(N)) {
            int s = B[p][i];
            int j = i + 1;
            while (j < N && s < like[2]) {
                s += B[p][j];
                if (s == like[0]) ret += like[0];
                if (s == like[1]) ret += like[1];
                if (s == like[2]) ret += like[2];
                j++;
            }
        }
        return ret;
    }

    int csc(int p) {
        using namespace IN;
        int ret = 0;
        for (int i : range(N)) {
            int s = B[i][p];
            int j = i + 1;
            while (j < N && s < like[2]) {
                s += B[j][p];
                if (s == like[0]) ret += like[0];
                if (s == like[1]) ret += like[1];
                if (s == like[2]) ret += like[2];
                j++;
            }
        }
        return ret;
    }


    // diff が大きいほどtrue
    bool temp(int diff) { return rdGen.next_int<>() < diff * diff; }

    void solve() {
        using namespace IN;
        int sum = 0;
        for (int i : range(N)) {
            int ans = Copt(i);
            // DEBUG cerr << ans << endl;
            sum += ans;
        }

        sum = 0;
        for (int i : range(N)) sum += csc(i) + rsc(i);
        DEBUG cerr << VAR_NAME(sum) << " " << sum << endl;

        for (int i : range(1000000)) {
            int r = rdGen.next_int() % (N);
            int c = rdGen.next_int() % (N - 1);
            pair<int, int> top(-10000, 0);
            int og = rsc(r) + csc(c) + csc(c + 1);
            for (int k : range(-9, 10)) {
                if (k == 0) continue;
                if (B[r][c] - k < lb[r][c] || B[r][c + 1] + k >= ub[r][c + 1]) {
                    continue;
                }
                if (B[r][c] - k >= ub[r][c] || B[r][c + 1] + k < lb[r][c + 1]) {
                    continue;
                }
                B[r][c] -= k;
                B[r][c + 1] += k;

                int sc = rsc(r) + csc(c) + csc(c + 1);
                chmax(top, make_pair(sc, k));
                B[r][c] += k;
                B[r][c + 1] -= k;
            }
            if (top.first == -10000
                || (top.first - og <= 0 && temp(og - top.first))) {
                // do nothing
            }
            else {
                B[r][c] -= top.second;
                B[r][c + 1] += top.second;
                DEBUG {
                    int sc = rsc(r) + csc(c) + csc(c + 1);
                    cerr << sc - og << endl;
                }
            }
        }
        sum = 0;
        for (int i : range(N)) sum += csc(i) + rsc(i);
        DEBUG cerr << VAR_NAME(sum) << " " << sum << endl;
    };


    void output() {
        string s(IN::N, ' ');
        s.back() = '\n';
        for (int i : range(IN::N)) {
            for (int j : range(IN::N)) {
                cout << B[i][j] << s[j];
            }
        }
    }

} // namespace SV
int main() {
    IN::init();
    SV::solve();
    SV::output();
    return 0;
}