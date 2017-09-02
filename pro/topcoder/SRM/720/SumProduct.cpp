#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define FOR(i,bg,ed) for(int i=(bg);i<(ed);i++)
#define REP(i,n) FOR(i,0,n)
#define ALL(v) (v).begin(),(v).end()
#define fi first
#define se second
#define pb push_back
#define DEBUG if(0)
#define REC(ret, ...) std::function<ret (__VA_ARGS__)>
template <typename T>inline void chmin(T &l,T r){l=min(l,r);}
template <typename T>inline void chmax(T &l,T r){l=max(l,r);}

const int mod=1e9+7;
LL ten[200];
LL comb[300][300];
void init(){
    REP(i,300){
        comb[i][0]=comb[i][i]=1;
        FOR(j,1,i)
            comb[i][j]=(comb[i-1][j-1]+comb[i-1][j])%mod;
    }
    ten[0]=1;
    FOR(i,1,200)ten[i]=(ten[i-1]*10)%mod;
}
typedef vector<LL> V;

LL solve(const int n,const vector<int> &c){
    V dp(n+1,0);
    dp[0]=1;
    REP(i,10){
        V nxt(n+1,0);
        REP(use,min(n,c[i])+1)
            FOR(used,use,n+1)
            nxt[used]+=comb[n-used+use][use]*dp[used-use]%mod;
        for(auto &it:nxt)it%=mod;
        dp=nxt;
    }
    return dp.back();
}
class SumProduct {
public:
    int findSum(vector <int> c, int n, int m) {
        init();
        LL res=0;
        LL K=0;
        REP(i,n)REP(j,m){
            K+=ten[i]*ten[j]%mod;
        }
        K%=mod;
        REP(a,10){
            c[a]--;
            REP(b,10){
                c[b]--;
                if(c[a]>=0&&c[b]>=0){
                    res+=a*b*solve(n+m-2,c);
                }
                    
                c[b]++;
            }
            c[a]++;
        }
        res%=mod;
            
        return res*K%mod;

    }
};















// BEGIN KAWIGIEDIT TESTING
// Generated by KawigiEdit-pf 2.3.0
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cmath>
using namespace std;
bool KawigiEdit_RunTest(int testNum, vector <int> p0, int p1, int p2, bool hasAnswer, int p3) {
    cout << "Test " << testNum << ": [" << "{";
    for (int i = 0; int(p0.size()) > i; ++i) {
        if (i > 0) {
            cout << ",";
        }
        cout << p0[i];
    }
    cout << "}" << "," << p1 << "," << p2;
    cout << "]" << endl;
    SumProduct *obj;
    int answer;
    obj = new SumProduct();
    clock_t startTime = clock();
    answer = obj->findSum(p0, p1, p2);
    clock_t endTime = clock();
    delete obj;
    bool res;
    res = true;
    cout << "Time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
    if (hasAnswer) {
        res = answer == p3;
    }
    if (!res) {
        cout << "DOESN'T MATCH!!!!" << endl;
        if (hasAnswer) {
            cout << "Desired answer:" << endl;
            cout << "\t" << p3 << endl;
        }
        cout << "Your answer:" << endl;
        cout << "\t" << answer << endl;
    } else if (double(endTime - startTime) / CLOCKS_PER_SEC >= 2) {
        cout << "FAIL the timeout" << endl;
        res = false;
    } else if (hasAnswer) {
        cout << "Match :-)" << endl;
    } else {
        cout << "OK, but is it right?" << endl;
    }
    cout << "" << endl;
    return res;
}
int main() {
    bool all_right;
    bool disabled;
    bool tests_disabled;
    all_right = true;
    tests_disabled = false;
	
    vector <int> p0;
    int p1;
    int p2;
    int p3;
	
    // ----- test 0 -----
    disabled = false;
    p0 = {0,2,1,1,0,0,0,0,0,0};
    p1 = 2;
    p2 = 2;
    p3 = 4114;
    all_right = (disabled || KawigiEdit_RunTest(0, p0, p1, p2, true, p3) ) && all_right;
    tests_disabled = tests_disabled || disabled;
    // ------------------
	
    // ----- test 1 -----
    disabled = false;
    p0 = {1,6,0,0,0,0,0,0,0,0};
    p1 = 1;
    p2 = 2;
    p3 = 22;
    all_right = (disabled || KawigiEdit_RunTest(1, p0, p1, p2, true, p3) ) && all_right;
    tests_disabled = tests_disabled || disabled;
    // ------------------
	
    // ----- test 2 -----
    disabled = false;
    p0 = {1,2,3,4,5,6,7,8,9,10};
    p1 = 15;
    p2 = 3;
    p3 = 340242570;
    all_right = (disabled || KawigiEdit_RunTest(2, p0, p1, p2, true, p3) ) && all_right;
    tests_disabled = tests_disabled || disabled;
    // ------------------
	
    // ----- test 3 -----
    disabled = false;
    p0 = {3,14,15,92,65,35,89,79,32,38};
    p1 = 46;
    p2 = 26;
    p3 = 417461139;
    all_right = (disabled || KawigiEdit_RunTest(3, p0, p1, p2, true, p3) ) && all_right;
    tests_disabled = tests_disabled || disabled;
    // ------------------
	
    // ----- test 4 -----
    disabled = false;
    p0 = {100,100,100,100,100,100,100,100,100,100};
    p1 = 100;
    p2 = 100;
    p3 = 372980218;
    all_right = (disabled || KawigiEdit_RunTest(4, p0, p1, p2, true, p3) ) && all_right;
    tests_disabled = tests_disabled || disabled;
    // ------------------
	
    if (all_right) {
        if (tests_disabled) {
            cout << "You're a stud (but some test cases were disabled)!" << endl;
        } else {
            cout << "You're a stud (at least on given cases)!" << endl;
        }
    } else {
        cout << "Some of the test cases had errors." << endl;
    }
    return 0;
}
// PROBLEM STATEMENT
// 
// You are given an array amount with exactly 10 elements, where the i-th element denotes the number of copies of the digit i you have.
// 
// 
// 
// You would like to construct construct two nonnegative integers A and B.
// The base-10 representation of A must have exactly blank1 digits.
// The base-10 representation of B must have exactly blank2 digits.
// It is allowed for A and B to contain leading zeros.
// In addition, the total number of appearances of digit i in the numbers A and B must be at most amount[i].
// It's guaranteed that the sum of amount is at least blank1 + blank2.
// 
// 
// 
// For every distinct ordered pair (A,B) which you can construct, compute the product A * B.
// Return the sum of all these products, modulo 10^9+7.
// 
// 
// 
// 
// DEFINITION
// Class:SumProduct
// Method:findSum
// Parameters:vector <int>, int, int
// Returns:int
// Method signature:int findSum(vector <int> amount, int blank1, int blank2)
// 
// 
// CONSTRAINTS
// -amount will have exactly 10 elements.
// -Each element of amount will be between 0 and 100.
// -blank1, blank2 will be between 1 and 100, inclusive.
// -The sum of elements in amount will be at least blank1 + blank2.
// 
// 
// EXAMPLES
// 
// 0)
// {0,2,1,1,0,0,0,0,0,0}
// 2
// 2
// 
// Returns: 4114
// 
// The different choices for (A,B) are (11, 23), (11, 32), (12, 13), (12, 31), (13, 12), (13, 21), (21, 13), (21, 31), (31, 12), (31, 21), (23, 11), (32, 11).
// 
// The sum of all products A * B is 4114.
// 
// 1)
// {1,6,0,0,0,0,0,0,0,0}
// 1
// 2
// 
// Returns: 22
// 
// Remember that the numbers are allowed to have leading zeros.
// 
// 2)
// {1,2,3,4,5,6,7,8,9,10}
// 15
// 3
// 
// Returns: 340242570
// 
// Don't forget about the mod.
// 
// 3)
// {3,14,15,92,65,35,89,79,32,38}
// 46
// 26
// 
// Returns: 417461139
// 
// 
// 
// 4)
// {100,100,100,100,100,100,100,100,100,100}
// 100
// 100
// 
// Returns: 372980218
// 
// 
// 
// END KAWIGIEDIT TESTING