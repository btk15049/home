#ifndef VS
#ifdef BTK
#include<bits/stdc++.h>
using namespace std;
#endif
#endif
namespace PersistentTrie {
    using RET = int;
    constexpr int BUF = 3623456;
    constexpr int MAX_VER = 512345;

    constexpr char BASE = 'a';
    constexpr int EDGE_SIZE = 'z' - 'a' + 1;
    constexpr RET NONE = -1;
    

    struct node {
        int nxt[EDGE_SIZE];
        RET val;
    }nd[BUF];
	
    namespace buf {
        int id = 0;
        inline int get() {
            for (int i = 0; i < EDGE_SIZE; i++) {
                nd[id].nxt[i] = -1;
            }
            nd[id].val = NONE;
            return id++;
        }
        inline int get(node o) {
            nd[id] = o;
            return id++;
        }
    }

    int top_ptr[MAX_VER];
    int ver = 0; // next version number(version[ver-1] is current)

    /*
      match new latest version to version[k]
      return value : latest version number
    */
    inline int undo(int k) {
        top_ptr[ver] = top_ptr[k];
        return ver++;
    }

    inline int init() {
        ver = 0;
        top_ptr[ver] = buf::get();
        return ver++;
    }

    /*
      trie[key] = val
      return value : latest version number
    */
    inline int set(string key, RET val) {
        int v = top_ptr[ver] = buf::get(nd[top_ptr[ver - 1]]);
        for (auto &it : key) {
            int& nxt = nd[v].nxt[it - BASE];
            if (nxt == -1)nxt = buf::get();
            else nxt = buf::get(nd[nxt]);
            v = nxt;
        }
        nd[v].val = val;
        return ver++;
    }
}
