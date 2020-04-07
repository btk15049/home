// http://codeforces.com/contest/1163/problem/C1
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


template <typename T>
class Fraction {
  private:
    T gcd(T a, T b) { return (b == 0) ? a : gcd(b, a % b); }

    T over;
    T under;

    Fraction(const T over, const T under, const T g)
        : over(over / g), under(under / g) {
        if (this->under < 0) {
            this->under = -this->under;
            this->over  = -this->over;
        }
    }


  public:
    /**
     * @brief Construct a new Fraction object
     *
     * @param over 分子
     * @param under 分母
     */
    Fraction(const T over = 0, const T under = 1)
        : Fraction(over, under, gcd(abs(over), abs(under))) {}

    /**
     * @brief Construct a new Fraction object
     * コピーコンストラクタ
     * @param other
     */
    Fraction(const Fraction& other) {
        this->over  = other.child();
        this->under = other.parent();
    }

    Fraction& operator=(const Fraction& other) {
        this->over  = other.child();
        this->under = other.parent();
        return *this;
    }
    inline T child() const { return over; }

    inline T parent() const { return under; }

    /**
     * @brief inf
     * @return Fraction
     */
    static Fraction inf() { return Fraction(1, 0); }

    inline Fraction operator-() const { return Fraction(-over, under); }
    inline Fraction add(const Fraction& other) const {
        return Fraction(over * other.parent + other.child * under,
                        under * other.parent);
    }
    inline Fraction sub(const Fraction& other) const {
        return Fraction(over * other.parent() - other.child() * under,
                        under * other.parent());
    }
    inline Fraction mul(const Fraction& other) const {
        return Fraction(over * other.child(), under * other.parent());
    }

    inline Fraction div(const Fraction& other) const {
        return Fraction(over * other.parent(), under * other.child());
    }

    inline Fraction inverse() const { return Fraction(under, over); }

    inline string to_string() const {
        return "(" + std::to_string(over) + "/" + std::to_string(under) + ")";
    }

    inline bool operator<(const Fraction& other) const {
        if (under == other.parent()) {
            return over < other.child();
        }
        else {
            return over * other.parent() < other.child() * under;
        }
    }
    inline bool operator>(const Fraction& other) const {
        if (under == other.parent()) {
            return over > other.child();
        }
        else {
            return over * other.parent() > other.child() * under;
        }
    }
    inline bool operator==(const Fraction& other) const {
        return over == other.child() && under == other.parent();
    }
};
int n;
int r[212345];
int c[212345];
using pt   = pair<int, int>;
using vec  = Fraction<int>;
using line = pair<vec, pt>;
int main() {
    int n;
    cin >> n;
    for (int i : range(n)) {
        cin >> r[i] >> c[i];
    }
    set<line> ls;
    for (int i : range(n)) {
        map<vec, pt> ils;
        for (int j : range(n)) {
            if (i == j) continue;
            vec v(r[i] - r[j], c[i] - c[j]);
            pt p(r[j], c[j]);
            if (v.parent() == 0 && v.child() < 0) v = -v;
            chmin(p, pt(r[i], c[i]));
            if (ils.count(v) == 0 || ils[v] > p) {
                ils[v] = p;
            }
        }
        for (auto& it : ils) {
            ls.insert(line(it.first, it.second));
        }
    }
    LL all = ls.size();
    // cerr << all << endl;
    map<vec, LL> cnt;
    for (auto& it : ls) {
        // cerr << it.first.to_string() << " ";
        // cerr << it.second.first << "," << it.second.second << endl;
        cnt[it.first]++;
    }
    LL ret = 0;
    for (auto& it : cnt) {
        ret += it.second * (all - it.second);
    }
    cout << ret / 2 << endl;
    return 0;
}