#include <bits/stdc++.h>

using namespace std;

#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define ALL(v) begin(v), end(v)

template <typename T>
inline bool chmin(T &l, T r) {
    bool f = l > r;
    if (f) l = r;
    return f;
}

int N;
int area[112][112];
constexpr int INF = 1e8;
int dx[4]         = {0, 1, 0, -1};
int dy[4]         = {1, 0, -1, 0};

int d[112][112];
bool input() {
    cin >> N;
    if (N == 0) return false;
    int A, B, C, D;
    cin >> A >> B >> C >> D;
    REP(i, 112)
    REP(j, 112) area[i][j]                   = INF;
    FOR(i, 1, 101) FOR(j, 1, 101) area[i][j] = 1;
    FOR(i, A, C + 1)
    FOR(j, B, D + 1) area[i][j] = 0;
    return true;
}
deque<int> qc, qx, qy;
void que_push_front(int x, int y, int c) {
    qx.push_front(x);
    qy.push_front(y);
    qc.push_front(c);
}
void que_push_back(int x, int y, int c) {
    qx.push_back(x);
    qy.push_back(y);
    qc.push_back(c);
}
void que_pop(int &x, int &y, int &c) {
    x = qx.front();
    y = qy.front();
    c = qc.front();
    qx.pop_front();
    qy.pop_front();
    qc.pop_front();
}
void bfs(int x, int y) {
    REP(i, 112) REP(j, 112) d[i][j] = INF;

    int c   = 0;
    d[x][y] = c;
    que_push_back(x, y, c);
    while (qx.size()) {
        que_pop(x, y, c);
        if (d[x][y] < c) continue;
        REP(i, 4) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (area[nx][ny] == 0) {
                if (chmin(d[nx][ny], d[x][y] + area[nx][ny])) {
                    que_push_front(nx, ny, d[nx][ny]);
                }
            }
            else {
                if (chmin(d[nx][ny], d[x][y] + area[nx][ny])) {
                    que_push_back(nx, ny, d[nx][ny]);
                }
            }
        }
    }
}
int main() {
    while (input()) {
        int x, y;
        cin >> x >> y;
        int ret = 0;
        REP(i, N) {
            int nx, ny;
            cin >> nx >> ny;
            bfs(x, y);
            ret += d[nx][ny];
            x = nx;
            y = ny;
        }
        cout << ret << endl;
    }
    return 0;
}