#include<bits/stdc++.h>
using namespace std;
namespace timer{
    std::chrono::high_resolution_clock::time_point begin_time;
    inline void set() {
        using namespace std::chrono;
        begin_time = high_resolution_clock::now();
    }
    inline int get(){
        using namespace std::chrono;
        auto ed=high_resolution_clock::now();
        auto t=ed-begin_time;
        return duration_cast<milliseconds>(t).count();
    }
    inline bool check(int lim) {
        using namespace std::chrono;
        return(get()< lim);
    }
}
