// https://atcoder.jp/contests/nikkei2019-2-final/tasks/nikkei2019_2_final_e
#define CIN_ONLY
#define DECIMAL_DIGITS 10
#define STATIC_MOD 1e9 + 7

#ifdef BTK
/*<head>*/
#    include "Template.hpp"
#    include "structure/SegmentManager.hpp"
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
/* #region structure/SegmentManager.hpp*/


struct Segment {
    int64_t l;
    int64_t r;
    Segment(int64_t l, int64_t r) : l(l), r(r) {}
    Segment(int64_t v) : l(v), r(v + 1) {}
    Segment() {}
    inline int len() { return r - l; }
};

inline bool isLeft(const int64_t v, const Segment& s) { return v < s.l; }

inline bool isRight(const int64_t v, const Segment& s) { return s.r <= v; }

inline bool out(const int64_t v, const Segment& s) {
    return isLeft(v, s) || isRight(v, s);
}

inline bool in(const int64_t v, const Segment s) { return !out(v, s); }

namespace std {
    string to_string(Segment s) {
        return "{" + to_string(s.l) + ", " + to_string(s.r) + "}";
    }
} // namespace std

class SegmentManager {
  public:
    SegmentManager();

    std::pair<Segment, std::vector<Segment>> add(Segment s);
    std::pair<std::vector<Segment>, std::vector<Segment>> erase(Segment s);

    std::vector<Segment> all();

  private:
    std::map<int64_t, Segment> data;
};

SegmentManager::SegmentManager() {}

std::pair<Segment, std::vector<Segment>> SegmentManager::add(Segment s) {
    std::vector<Segment> deleted;
    for (auto it                                     = data.lower_bound(s.l);
         it != data.end() && it->second.l <= s.r; it = next(it)) {
        chmin(s.l, it->second.l);
        chmax(s.r, it->second.r);
        deleted.push_back(it->second);
    }
    for (auto& it : deleted) {
        data.erase(it.r);
    }
    data[s.r] = s;
    return std::make_pair(s, deleted);
}

std::pair<std::vector<Segment>, std::vector<Segment>>
SegmentManager::erase(Segment s) {
    std::vector<Segment> deleted;
    std::vector<Segment> inserted;

    for (auto it                                    = data.upper_bound(s.l);
         it != data.end() && it->second.l < s.r; it = next(it)) {
        if (it->second.l < s.l) {
            inserted.push_back(Segment(it->second.l, s.l));
        }
        if (it->second.r > s.r) {
            inserted.push_back(Segment(s.r, it->second.r));
        }
        deleted.push_back(it->second);
    }
    for (auto& it : deleted) {
        data.erase(it.r);
    }
    for (auto& it : inserted) {
        data[it.r] = it;
    }

    return std::make_pair(inserted, deleted);
}

std::vector<Segment> SegmentManager::all() {
    std::vector<Segment> result;
    for (auto& it : data) {
        result.push_back(it.second);
    }
    return result;
}
/* #endregion */
/* #endregion */
/*</body>*/
#endif

int n, m, q;

vector<int> leaf[1123456];

vector<int> node[1123456];

void build(int l, int r, int k = 0) {
    if (r - l < 0) return;
    if (r - l == 1) {
        node[k] = leaf[l];
        sort(ALL(node[k]));
    }
    else {
        const int m = (l + r) / 2;
        int x       = 2 * k + 1;
        int y       = 2 * k + 2;
        build(l, m, x);
        build(m, r, y);
        for (auto it : node[x]) node[k].push_back(it);
        for (auto it : node[y]) node[k].push_back(it);
        sort(ALL(node[k]));
    }
}

int query(int nl, int nr, int ql, int qr, int k = 0) {
    if (ql <= nl && nr <= qr) {
        return distance(lower_bound(ALL(node[k]), ql),
                        upper_bound(ALL(node[k]), qr));
    }
    if (nr <= ql || qr <= nl) {
        return 0;
    }
    const int m = (nl + nr) / 2;
    return query(nl, m, ql, qr, k * 2 + 1) + query(m, nr, ql, qr, k * 2 + 2);
}


int main() {
    /* write here */
    cin >> n >> m >> q;
    string s;
    cin >> s;
    int ret = 0;
    SegmentManager seg;


    for (int i : range(m)) {
        unused_var(i);
        int l, r;
        cin >> l >> r;
        l--;
        leaf[r - 1].push_back(l);
    }
    build(0, n + 1);

    for (int i : range(n)) {
        if (s[i] == '0') {
            Segment inserted;
            vector<Segment> deleted;
            tie(inserted, deleted) = seg.add(Segment(i));
            ret += query(0, n + 1, inserted.l, inserted.r);
            // cerr << i << " " << to_string(inserted) << " " << ret << endl;
            for (auto &it : deleted) {
                ret -= query(0, n + 1, it.l, it.r);
            }
        }
    }
    // cerr << s << endl;
    // for (auto it : seg.all()) {
    //     cerr << " " << to_string(it);
    // }
    // cerr << endl;
    // cerr << ret << endl;
    for (int i : range(q)) {
        unused_var(i);
        int x;
        cin >> x;
        x--;

        if (s[x] == '1') {
            Segment inserted;
            vector<Segment> deleted;
            tie(inserted, deleted) = seg.add(Segment(x));
            ret += query(0, n + 1, inserted.l, inserted.r);
            for (auto &it : deleted) {
                ret -= query(0, n + 1, it.l, it.r);
            }
            s[x] = '0';
        }
        else if (s[x] == '0') {
            vector<Segment> inserted;
            vector<Segment> deleted;
            tie(inserted, deleted) = seg.erase(x);
            for (auto &it : inserted) {
                ret += query(0, n + 1, it.l, it.r);
            }
            for (auto &it : deleted) {
                ret -= query(0, n + 1, it.l, it.r);
            }
            s[x] = '1';
        }
        // cerr << s << endl;
        // for (auto it : seg.all()) {
        //    cerr << " " << to_string(it);
        //}
        // cerr << endl;
        cout << m - ret << "\n";
    }
    return 0;
}