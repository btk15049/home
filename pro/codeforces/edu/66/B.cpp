// http://codeforces.com/contest/1175/problem/B
/*<head>*/
// #include "Template.hpp"
/*</head>*/

/*<body>*/
/* #region header */
/**
 * @file Template.hpp
 * @brief ################
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
 * ALL###
 */
#define ALL(v) (v).begin(), (v).end()

/** @def
 * ##############
 */
#define REC(ret, ...) std::function<ret(__VA_ARGS__)>
/* #endregion */

namespace _Template_ {
    /**
     * @brief cin##############
     * @details CIN_ONLY##########
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
     * @tparam T #
     * @param l ##
     * @param r ###
     * @return ######true
     */
    template <typename T>
    inline bool chmin(T& l, T r) {
        bool a = l > r;
        if (a) l = r;
        return a;
    }
    /**
     * @brief chmin#max#
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
     * vector###cin#######
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
     * range#############
     * @details
     * #######[bg,ed)#####
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
     * python #### range-based for ###
     * @details
     * #######[bg,ed)#####
     * !############## (reverse_range)
     * ######O(1)
     * ####################unused_var###############
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
     * range#####################
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

void ed() {
    cout << "OVERFLOW!!!" << endl;
    exit(0);
}
int main() {
    int n;
    cin >> n;
    LL ret       = 0;
    double about = 0;
    vector<int> st;
    vector<LL> loops;
    for (int i : range(n)) {
        string s;
        cin >> s;
        if (s == "for") {
            int l;
            cin >> l;
            st.push_back(l);
            if (l >= 2) loops.push_back(l);
        }
        else if (s == "end") {
            int l = st.back();
            st.pop_back();
            if (l >= 2) loops.pop_back();
        }
        else {
            if (loops.size() >= 32) {
                ed();
            }
            LL l     = 1;
            double d = 1;
            for (auto& it : loops) {
                l *= it;
                d *= it;
            }
            ret += l;
            about += d;
        }
    }
    if (about <= 1e10 && ret < (1ll << 32)) {
        cout << ret << endl;
    }
    else
        ed();
    return 0;
}
