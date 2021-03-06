#ifndef _WIN32
#include<bits/stdc++.h>
#else
#include"../../../vs.hpp"
#endif
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

typedef LL INT;
class RememberWords {
public:
    
    bool calc(INT d1,INT d2,INT w1,INT w2){
        INT dx2=d2*(d2-1)/2;
        INT dx1=d1*(d1-1)/2;
        INT bottom=[&](){
            INT ub=1e9;
            INT lb=0;
            if(dx2>=w2)return (INT)0;
            while(ub-lb>1){
                const INT mid=(lb+ub)/2;
                if(mid*d2+dx2>=w2)ub=mid;
                else lb=mid;
            }
            return ub;
        }();
        INT top=[&](){
            INT ub=1e9+1;
            INT lb=0;
            while(ub-lb>1){
                const INT mid=(lb+ub)/2;
                INT a=mid>=d2?mid*d2-dx2:mid*(mid+1)/2;
                if(a<=w2)lb=mid;
                else ub=mid;
            }
            return lb;
        }();
        cout<<(LL)bottom<<endl;
        cout<<(LL)top<<endl;
        top++;
        if(bottom>0)bottom--;
        
        INT mx=top*d1+dx1;
        INT mn=bottom>=d1?bottom*d1-dx1:bottom*(bottom+1)/2;
        cout<<(LL)mn<<endl;
        cout<<(LL)mx<<endl;
        return (mn<=w1&&w1<=mx);
        

    }
    string isPossible(int d1, int d2, int w1, int w2) {
        if(calc(d1,d2,w1,w2))return "Possible";
        else return "Impossible";

    }
};















// BEGIN KAWIGIEDIT TESTING
// Generated by KawigiEdit-pf 2.3.0

using namespace std;
bool KawigiEdit_RunTest(int testNum, int p0, int p1, int p2, int p3, bool hasAnswer, string p4) {
	cout << "Test " << testNum << ": [" << p0 << "," << p1 << "," << p2 << "," << p3;
	cout << "]" << endl;
	RememberWords *obj;
	string answer;
	obj = new RememberWords();
	clock_t startTime = clock();
	answer = obj->isPossible(p0, p1, p2, p3);
	clock_t endTime = clock();
	delete obj;
	bool res;
	res = true;
	cout << "Time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
	if (hasAnswer) {
		res = answer == p4;
	}
	if (!res) {
		cout << "DOESN'T MATCH!!!!" << endl;
		if (hasAnswer) {
			cout << "Desired answer:" << endl;
			cout << "\t" << "\"" << p4 << "\"" << endl;
		}
		cout << "Your answer:" << endl;
		cout << "\t" << "\"" << answer << "\"" << endl;
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
	
	int p0;
	int p1;
	int p2;
	int p3;
	string p4;
	
	// ----- test 0 -----
	disabled = false;
	p0 = 2;
	p1 = 3;
	p2 = 7;
	p3 = 18;
	p4 = "Possible";
	all_right = (disabled || KawigiEdit_RunTest(0, p0, p1, p2, p3, true, p4) ) && all_right;
	tests_disabled = tests_disabled || disabled;
	// ------------------
	
	// ----- test 1 -----
	disabled = false;
	p0 = 1;
	p1 = 1;
	p2 = 3;
	p3 = 5;
	p4 = "Impossible";
	all_right = (disabled || KawigiEdit_RunTest(1, p0, p1, p2, p3, true, p4) ) && all_right;
	tests_disabled = tests_disabled || disabled;
	// ------------------
	
	// ----- test 2 -----
	disabled = false;
	p0 = 3;
	p1 = 5;
	p2 = 300;
	p3 = 500;
	p4 = "Possible";
	all_right = (disabled || KawigiEdit_RunTest(2, p0, p1, p2, p3, true, p4) ) && all_right;
	tests_disabled = tests_disabled || disabled;
	// ------------------
	
	// ----- test 3 -----
	disabled = false;
	p0 = 100;
	p1 = 1;
	p2 = 0;
	p3 = 2;
	p4 = "Impossible";
	all_right = (disabled || KawigiEdit_RunTest(3, p0, p1, p2, p3, true, p4) ) && all_right;
	tests_disabled = tests_disabled || disabled;
	// ------------------
	
	// ----- test 4 -----
	disabled = false;
	p0 = 1000000000;
	p1 = 1000000000;
	p2 = 1000000000;
	p3 = 1000000000;
	p4 = "Possible";
	all_right = (disabled || KawigiEdit_RunTest(4, p0, p1, p2, p3, true, p4) ) && all_right;
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
// For Fox Ciel it is the beginning of a new school year.
// Her school year will consist of two semesters.
// The first semester contains d1 days and the second semester contains d2 days.
// Surprisingly, there are no breaks during or between the semesters: the entire school year consists of d1+d2 consecutive days of classes.
// 
// 
// Fox Ciel is taking an English class during both semesters.
// For the class she needs to learn a lot of new words: exactly w1 words during the first semester and exactly w2 words during the second semester.
// 
// 
// Ciel can learn arbitrarily many words on any single day.
// However, she does not like to change her workload too much.
// Therefore, the number of words she will learn on any two consecutive days must differ by at most one.
// 
// 
// Formally, suppose the days of the school year are numbered from 1 to d1+d2.
// Suppose that Ciel will learn x[i] words on day i.
// Ciel will be happy if the numbers x[i] have the following properties:
// 
// x[1] + ... + x[d1] is exactly equal to w1
// x[d1+1] + ... + x[d1+d2] is exactly equal to w2
// for each valid i, | x[i+1] - x[i] | is at most 1
// 
// 
// You are given the ints d1, d2, w1, and w2.
// Return "Possible" if there is a schedule that makes Ciel happy, or "Impossible" if there is no such schedule.
// 
// DEFINITION
// Class:RememberWords
// Method:isPossible
// Parameters:int, int, int, int
// Returns:string
// Method signature:string isPossible(int d1, int d2, int w1, int w2)
// 
// 
// CONSTRAINTS
// -d1 will be between 1 and 1,000,000,000, inclusive.
// -d2 will be between 1 and 1,000,000,000, inclusive.
// -w1 will be between 0 and 1,000,000,000, inclusive.
// -w2 will be between 0 and 1,000,000,000, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// 2
// 3
// 7
// 18
// 
// Returns: "Possible"
// 
// 
// The school year has 2+3 = 5 days.
// Ciel needs to learn exactly 7 words during the first semester and exactly 18 words during the second semester.
// The only valid way to do so is to learn 3, 4, 5, 6, and 7 words during the five days of the school year.
// Note that 3+4 = 7 and 5+6+7 = 18.
// 
// 
// 1)
// 1
// 1
// 3
// 5
// 
// Returns: "Impossible"
// 
// 
// Here the school year has just 1+1 = 2 days.
// Ciel must learn 3 words on the first day and 5 words on the second day.
// However, |3 - 5| is more than 1, so Ciel will not be happy with this schedule.
// 
// 
// 2)
// 3
// 5
// 300
// 500
// 
// Returns: "Possible"
// 
// One possible solution is to learn 100 words every day.
// 
// 3)
// 100
// 1
// 0
// 2
// 
// Returns: "Impossible"
// 
// 
// 
// 4)
// 1000000000
// 1000000000
// 1000000000
// 1000000000
// 
// Returns: "Possible"
// 
// 
// 
// END KAWIGIEDIT TESTING
