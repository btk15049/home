//http://codeforces.com/contest/1042/problem/C
#include<bits/stdc++.h>

using namespace std;
typedef long long LL;

#ifdef BTK
#define DEBUG if(1)
#else
#define CIN_ONLY if(0)
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

int a[212345];
int main() {
    int n;
    scanf("%d",&n);
    vector<int> pos,zero,neg;
    for(int i:range(n)){
        scanf("%d",a+i);
        if(a[i]>0)pos.push_back(i+1);
        if(a[i]<0)neg.push_back(i+1);
        if(a[i]==0)zero.push_back(i+1);
    }
    
    int bot_id = -2;
    int top_id = -2;
    for(int i:range(n)){
        if(a[i]<0&&(bot_id==-2||a[bot_id]<a[i]))bot_id=i;
        if(a[i]>0&&(top_id==-2||a[top_id]>a[i]))top_id=i;
    }
    //cout<<pos.size()<<neg.size()<<zero.size()<<endl;
    bot_id++;top_id++;
    if(zero.size()>0){
        if(neg.size()%2==0){
            while(zero.size()>1){
                printf("1 %d %d\n",zero.back(),zero.front());
                zero.pop_back();
            }
            for(auto it:neg)pos.push_back(it);
            while(pos.size()>1){
                printf("1 %d %d\n",pos.back(),pos.front());
                pos.pop_back();

            }
            if(pos.size()>0)printf("2 %d\n",zero[0]);
        }
        else{
            if(neg.size()==1&&pos.size()==0){
                printf("2 %d\n",neg[0]);
                while(zero.size()>1){
                    printf("1 %d %d\n",zero.back(),zero.front());
                    zero.pop_back();
                }
            }
            else{
                for(int i:range(neg.size())){
                    if(neg[i]==bot_id){
                        swap(neg[i],neg.back());
                        neg.pop_back();
                        printf("1 %d %d\n",bot_id,zero[0]);
                        break;
                    }
                }
                while(zero.size()>1){
                    printf("1 %d %d\n",zero.back(),zero.front());
                    zero.pop_back();
                }            
                for(auto it:neg)pos.push_back(it);
                while(pos.size()>1){
                    printf("1 %d %d\n",pos.back(),pos.front());
                    pos.pop_back();
                }
                printf("2 %d\n",zero[0]);
            }
        }
    }
    else{
        if(neg.size()%2==0){
            for(auto it:neg)pos.push_back(it);
            while(pos.size()>1){
                printf("1 %d %d\n",pos.back(),pos.front());
                pos.pop_back();
            }
        }
        else{
            if(neg.size()==1&&pos.size()==0){
            }
            else{
                for(int i:range(neg.size())){
                    if(neg[i]==bot_id){
                        swap(neg[i],neg.back());
                        neg.pop_back();
                        printf("2 %d\n",bot_id);
                        break;
                    }
                }       
                for(auto it:neg)pos.push_back(it);
                while(pos.size()>1){
                    printf("1 %d %d\n",pos.back(),pos.front());
                    pos.pop_back();
                }
            }
        }
    }
    fflush(stdout);

    return 0;
}
