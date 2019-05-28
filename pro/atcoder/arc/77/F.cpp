// https://atcoder.jp/contests/arc077/tasks/arc077_d
/*<head>*/
// #include "KMP.hpp"
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

/**
 * @file KMP.hpp
 * @author btk
 * @brief KMP
 * @date 2019-05-27
 *
 * @copyright Copyright (c) 2019
 *
 */


namespace _KMP_ {
    class KMP {
      private:
        string keyword;
        vector<int> table;

      public:
        KMP(string keyword, string eow = "$") : keyword(keyword + eow) {
            const int n = this->keyword.size();
            table.resize(n);
            table[0] = -1;
            for (int i = 2, j = 0; i < n;) {
                if (keyword[i - 1] == keyword[j])
                    table[i++] = ++j;
                else if (j > 0)
                    j = table[j];
                else
                    table[i++] = 0;
            }
        }

        inline bool advance(const char next_char, int& reading_len) {
            if (next_char != keyword[reading_len]) {
                while (reading_len >= 0 && keyword[reading_len] != next_char) {
                    reading_len = table[reading_len];
                }
            }
            reading_len++;
            return reading_len == (int)keyword.size() - 1;
        }

        inline int find(string& sentence, int& reading_len, int tail_pos = 0) {
            const int sentence_size = sentence.size();
            for (; tail_pos < sentence_size; tail_pos++) {
                if (advance(sentence[tail_pos], reading_len)) {
                    return tail_pos + 1;
                }
            }
            return -1;
        }

        vector<int> find_all(string sentence) {
            int reading_len = 0;
            int tail_pos    = 0;
            vector<int> position;
            while (1) {
                tail_pos = find(sentence, reading_len, tail_pos);
                if (tail_pos == -1) {
                    break;
                }
                else {
                    position.push_back(tail_pos - keyword.size() + 1);
                }
            }
            return position;
        }

        /**
         * @brief keyword[0,i)の最小周期を求める
         * @return int 最小周期長
         */
        int period(int i = 0) {
            if (i == 0) i = (int)keyword.size() - 1;
            return i - table[i];
        }
    };
} // namespace _KMP_
using namespace _KMP_;
/*
#include<bits/stdc++.h>
using namespace std;
typedef vector<int> V;
typedef vector<V> VV;
//KMP
int kmp_search(string S,string word,V& table){
int n=S.size();
int m=word.size();
int i=0,j=0;
for(;j<n&&i<m;i++,j++)
while(i>=0&&word[i]!=S[j])i=table[i];
if(i==m)return j-m;
else return -1;
}


V kmp_table_build(string word){
int n=word.size()+1;
V table(n,0);
table[0]=-1;
for(int i=2,j=0;i<n;){
if(word[i-1]==word[j])table[i++]=++j;
else if(j>0)j=table[j];
else table[i++]=0;
}
return table;
}
*/

/* #endregion */
/*</body>*/


typedef __int128 INT;

using V  = vector<LL>;
using VV = vector<V>;

V f(string s, INT k) {
    LL x = s.size();
    V ret(26, 0);
    LL loop = k / x;
    for (auto& it : s) ret[it - 'a'] += loop;
    k -= loop * x;
    for (int i : range((int)k)) ret[s[i] - 'a']++;
    return ret;
}
V g(string& s1, VV& c, vector<INT>& l, INT k, int id) {
    if (k == 0) return V(26, 0);
    if (id <= 1) {
        V ret(26, 0);
        for (int i : range((int)k)) ret[s1[i] - 'a']++;
        return ret;
    }
    if (l[id - 1] <= k) {
        V ret  = c[id - 1];
        V rest = g(s1, c, l, k - l[id - 1], id - 2);
        for (int i : range(26)) ret[i] += rest[i];
        return ret;
    }
    else {
        return g(s1, c, l, k, id - 1);
    }
}

int main() {
    string s;
    LL l, r;
    cin >> s >> l >> r;
    LL n = s.size() / 2;
    s    = s.substr(0, n);
    KMP finder(s);
    int x = finder.period();
    if (n % x == 0) {
        s      = s.substr(0, x);
        auto a = f(s, r);
        auto b = f(s, l - 1);
        for (int i : range(26)) cout << " " + (!i) << a[i] - b[i];
        cout << endl;
    }
    else {
        VV cnt(128, V(26, 0));
        vector<INT> len(128);
        for (int i : range(n)) cnt[0][s[i] - 'a']++;
        len[0] = n;
        len[1] = n + x;
        cnt[1] = cnt[0];
        for (int i : range(x)) cnt[1][s[i] - 'a']++;
        int id = -1;
        for (int i : range(2, 128)) {
            len[i] = len[i - 1] + len[i - 2];
            for (int j : range(26)) cnt[i][j] += cnt[i - 1][j] + cnt[i - 2][j];
            if (len[i] > r) {
                id = i;
                break;
            }
        }
        s      = s + s.substr(0, x);
        auto a = g(s, cnt, len, r, id);
        auto b = g(s, cnt, len, l - 1, id);
        for (int i : range(26)) cout << " " + (!i) << a[i] - b[i];
        cout << endl;
    }
    return 0;
}