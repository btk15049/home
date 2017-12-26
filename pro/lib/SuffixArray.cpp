#include<bits/stdc++.h>
using namespace std;
/*
  sa[0]=n //ãÛï∂éöóÒ
  lcp[i]:=suffix[sa[i]]Ç∆suffix[sa[i+1]]ÇÃã§í çÇÇ≥
 */

namespace latte{
    void create_begin_bucket(vector<int>&v,vector<int>&bucket){
        fill(bucket.begin(),bucket.end(),0);
        for(int i=0;i<(int)v.size();i++)bucket[v[i]]++;
        int sum=0;
        for(int i=0;i<(int)bucket.size();i++){bucket[i]+=sum;swap(sum,bucket[i]);}
    }

    void create_end_bucket(vector<int>&v,vector<int>&bucket){
        fill(bucket.begin(),bucket.end(),0);
        for(int i=0;i<(int)v.size();i++)bucket[v[i]]++;
        for(int i=1;i<(int)bucket.size();i++)bucket[i]+=bucket[i-1];
    }

    void induced_sort(vector<int>&v,vector<int>&sa,int mv,vector<int>&bucket,vector<int>&is_l){
        create_begin_bucket(v,bucket);
        for(int i=0;i<(int)v.size();i++)if(sa[i]>0&&is_l[sa[i]-1])sa[bucket[v[sa[i]-1]]++]=sa[i]-1;
    }

    void invert_induced_sort(vector<int>&v,vector<int>&sa,int mv,vector<int>&bucket,vector<int>&is_l){
        create_end_bucket(v,bucket);
        for(int i=v.size()-1;i>=0;i--)if(sa[i]>0&&!is_l[sa[i]-1])sa[--bucket[v[sa[i]-1]]]=sa[i]-1;
    }

    vector<int>sa_is(vector<int>v,int mv){
        if(v.size()==1)return vector<int>(1,0);

        vector<int>is_l(v.size());
        vector<int>bucket(mv+1);
        vector<int>sa(v.size(),-1);
        auto is_lms=[&](int x)->bool{return x>0&&is_l[x-1]&&!is_l[x];};

        is_l[v.size()-1]=0;
        for(int i=v.size()-2;i>=0;i--)is_l[i]=v[i]>v[i+1]||(v[i]==v[i+1]&&is_l[i+1]);
        create_end_bucket(v,bucket);
        for(int i=0;i<(int)v.size();i++)if(is_lms(i))sa[--bucket[v[i]]]=i;
        induced_sort(v,sa,mv,bucket,is_l);
        invert_induced_sort(v,sa,mv,bucket,is_l);

        int cur=0;
        vector<int>order(v.size());
        for(int i=0;i<(int)v.size();i++)if(is_lms(i))order[i]=cur++;

        vector<int>next_v(cur);
        cur=-1;
        int prev=-1;
        for(int i=0;i<(int)v.size();i++){
            if(!is_lms(sa[i]))continue;
            bool diff=false;
            for(int d=0;d<v.size();d++){
                if(prev==-1||v[sa[i]+d]!=v[prev+d]||is_l[sa[i]+d]!=is_l[prev+d]){
                    diff=true;
                    break;
                }
                else if(d>0&&is_lms(sa[i]+d))break;
            }
            if(diff){cur++;prev=sa[i];}
            next_v[order[sa[i]]]=cur;
        }

        vector<int>re_order(next_v.size());
        for(int i=0;i<(int)v.size();i++)if(is_lms(i))re_order[order[i]]=i;
        vector<int>next_sa=sa_is(next_v,cur);
        create_end_bucket(v,bucket);
        for(int i=0;i<sa.size();i++)sa[i]=-1;
        for(int i=next_sa.size()-1;i>=0;i--)sa[--bucket[v[re_order[next_sa[i]]]]]=re_order[next_sa[i]];
        induced_sort(v,sa,mv,bucket,is_l);
        invert_induced_sort(v,sa,mv,bucket,is_l);
        return sa;
    }

    vector<int> sa_is(string &s){
        vector<int>v(s.size()+1);
        for(int i=0;i<(int)s.size();i++)v[i]=s[i];
        return sa_is(v,*max_element(v.begin(),v.end()));
    }

    
}
namespace SA {
    int n, k;
    int R[500000];
    int T[500000];
    bool compare_sa(int i, int j) {
        if (R[i] != R[j])return R[i] < R[j];
        else {
            int ri = i + k <= n ? R[i + k] : -1;
            int rj = j + k <= n ? R[j + k] : -1;
            return ri < rj;
        }
    }
    vector<int> construct_sa(string& S) {
        n = S.size();
        vector<int> sa(n + 1);
        for (int i = 0; i <= n; i++) {
            sa[i] = i;
            R[i] = i < n ? S[i] : -1;
        }
 
        for (k = 1; k <= n; k *= 2) {
            sort(sa.begin(), sa.end(), compare_sa);
            T[sa[0]] = 0;
            for (int i = 1; i <= n; i++) 
                T[sa[i]] = T[sa[i - 1]] + (compare_sa(sa[i - 1], sa[i]) ? 1 : 0);
            for (int i = 0; i <= n; i++)
                R[i] = T[i];
        }
        return sa;
    }
    vector<int> construct_lcp(string& S, vector<int> &sa) {
        n = S.size();
        for (int i = 0; i <= n; i++)R[sa[i]] = i;
        int h = 0;
        vector<int> lcp(n + 1, 0);
        for (int i = 0; i < n; i++) {
            int j = sa[R[i] - 1];
            if (h > 0)h--;
            for (; j + h < n&&i + h < n; h++) {
                if (S[j + h] != S[i + h])break;
            }
            lcp[R[i] - 1] = h;
        }
        return lcp;
    }
}
