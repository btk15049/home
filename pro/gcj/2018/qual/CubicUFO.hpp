#include<bits/stdc++.h>

using namespace std;
typedef long long LL;

#ifdef BTK
#define DEBUG if(1)
#else
#define CIN_ONLY if(1)
struct cww {cww() {CIN_ONLY{ios::sync_with_stdio(false); cin.tie(0);}}
}star;
#define DEBUG if(0)
#endif

#define ALL(v) (v).begin(),(v).end()
#define REC(ret, ...) std::function<ret (__VA_ARGS__)>
template <typename T>inline bool chmin(T &l, T r){bool a = l>r; if (a)l = r; return a;}
template <typename T>inline bool chmax(T &l, T r){bool a = l<r; if (a)l = r; return a;}
template <typename T>istream& operator>>(istream &is, vector<T> &v){for (auto &it : v)is >> it;return is;}

class range {private: struct I { int x; int operator*() { return x; }bool operator!=(I& lhs) { return x<lhs.x; }void operator++() { ++x; } }; I i, n;public:range(int n) :i({ 0 }), n({ n }) {}range(int i, int n) :i({ i }), n({ n }) {}I& begin() { return i; }I& end() { return n; }};

#define IL inline 
namespace geo {
	typedef long double D;
	typedef bool B;
	typedef complex<D> P;
	typedef pair<P, P> L;  //line
	typedef pair<P, P> LS; //line segment
	typedef pair<P, D> C;  //circle
	typedef vector<P> Poly;
	const D EPS = 1e-10;
#define X real()
#define Y imag()
#define FOR(i,bg,ed) for(int i=(bg);i<(ed);i++)
#define REP(i,n) FOR(i,0,n)
	B comp(const P& l, const P& r) { return (l.X == r.X) ? l.Y < r.Y : l.X < r.X; }
	//A dot B
	IL D dot(P a, P b) { return a.X*b.X + a.Y*b.Y; }
	//A cross B
	IL D cross(P a, P b) { return a.X*b.Y - a.Y*b.X; }
	IL D ccw(P a, P b, P c) {
		return cross(b - a, c - a);
	}

	IL int sgn(P a, P b, P c) {
		if (cross(b - a, c - a) > EPS)return 1;
		if (cross(b - a, c - a) < -EPS)return -1;
		if (dot(b - a, c - a) < -EPS)return 2; // b-a-c
		if (dot(a - b, c - b) < -EPS)return -2; // a-b-c
		return 0;
	}
	IL Poly convex_hull(Poly p) {
		int n = p.size();
		Poly res(2 * n);
		int k = 0, t;
		sort(ALL(p), comp);
		REP(i, n) {
			while (k > 1 && ccw(res[k - 2], res[k - 1], p[i]) < EPS)k--;
			res[k++] = p[i];
		}
		t = k;
		REP(j, n - 1) {
			int i = n - 2 - j;
			while (k > t && ccw(res[k - 2], res[k - 1], p[i]) < EPS)k--;
			res[k++] = p[i];
		}
		res.resize(k - 1);
		return res;
	}
	IL D area(Poly& l) {
		double res = 0;
		int n = l.size();
		REP(i, n)res += abs(cross(l[i], l[(i + 1) % n]));
		return abs(res) / 2.0;
	}
}
using namespace geo;


D calc(vector<D> v, vector<D> u) {
	return v[0] * u[0] + v[1] * u[1] + v[2] * u[2];
}
vector<D> rot_y(vector<D> v, D theta) {
	return {
		calc(v,{ cosl(theta),0.0,sinl(theta)}),
		calc(v,{ 0.0,1.0,0.0 }),
		calc(v,{ -sinl(theta),0.0,cosl(theta) })
	};
}
vector<D> rot_z(vector<D> v, D theta) {
	return {
		calc(v,{ cosl(theta),-sinl(theta),0.0 }),
		calc(v,{ sinl(theta), cosl(theta), 0.0 }),
		calc(v,{ 0.0,0.0,1.0 })
	};
}

const D pi = acosl(-1.0);
const D quo = pi/4;
const D INF = acosl(sqrt(1.0 / 3.0));
D area(vector<vector<D>> pts, D theta) {
	Poly x;
	for (auto &it : pts) {
		auto y = rot_z(it, theta);
		x.push_back(P(y[0], y[2]));
	}
	x = convex_hull(x);
	return area(x);
}
vector<D> ave(vector<vector<D>> v) {
	for (int i : range(1, 4)) {
		v[0][0] += v[i][0];
		v[0][1] += v[i][1];
		v[0][2] += v[i][2];
	}
	v[0][0] /= 4;
	v[0][1] /= 4;
	v[0][2] /= 4;
	return v[0];
}
void solve() {
	D A;
	cin >> A;
	vector<vector<D>> pts;
	for (D x : {-0.5, 0.5}) {
		for (D y : {-0.5, 0.5}) {
			for (D z : {-0.5, 0.5}) {
				pts.push_back(
					rot_y(
						{ x,y,z }
						, quo)
				);
			}
		}
	}
	D lb = 0;
	D ub = INF;
	for (int i : range(100)) {
		const double mid = (lb + ub) / 2;
		(area(pts, mid) <= A ? lb : ub) = mid;
	}
	DEBUG cout << area(pts, lb) << endl;
	for (int i : range(8)) {
		pts[i] = rot_z(pts[i],lb);
	}
	
	vector<vector<D>> ret;
	ret.push_back(ave({ pts[0],pts[1],pts[2],pts[3]}));
	ret.push_back(ave({ pts[0],pts[1],pts[4],pts[5] }));
	ret.push_back(ave({ pts[0],pts[2],pts[4],pts[6] }));
	string mayo = "  \n";
	for (int i : range(3)) {
		for (int j : range(3)) {
			cout << ret[i][j] << mayo[j];
		}
	}

}
int main() {
	int T;
	cin >> T;
	cout << fixed;
	cout << setprecision(12);
	for(int i:range(1,T+1)) {
		cout << "Case #" << i << ":" << endl;
		solve();
	}
	return 0;
}
