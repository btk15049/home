#ifndef VS
#include<bits/stdc++.h>
using namespace std;
#endif
/*
  generate set of "directed" n-omino
  
  n:size
  ------
  1:1
  2:2
  3:6
  4:19
  5:63
  6:216
  7:760
  8:2725
*/
namespace PolyOmino {
    const int dr[4] = { 0,0,1,-1 };
    const int dc[4] = { 1,-1,0,0 };

    typedef pair<int, int> pii;
    typedef vector<pii> V;
    const int INF = 1e9 + 7;
    inline void fit(V& o) {
        int rm = INF;
        int cm = INF;
        for (auto &it : o) {
            rm = min(rm,it.first);
            cm = min(cm,it.second);
        }
        for (auto &it : o) {
            it.first -= rm;
            it.second -= cm;
        }
        sort(o.begin(),o.end());
    }
    set<V> get(int size) {
        set<V> omino;
        omino.insert(V(1, pii(0, 0)));
        for(int i = 2; i <= size; i++) {
            set<V> nxt;
            for (const V &o : omino) {
                set<pii> used;
                for (const pii &pos : o) {
                    used.insert(pos);
                }
                for (const pii &pos : o) {
                    for(int d = 0; d < 4; d++) {
                        int nr = pos.first + dr[d];
                        int nc = pos.second + dc[d];
                        pii npos(nr, nc);
                        if (used.count(npos) == 0) {
                            V no = o;
                            no.push_back(npos);
                            fit(no);
                            nxt.insert(no);
                        }
                    }
                }
            }
            swap(omino, nxt);
        }
        return omino;
    }

}
