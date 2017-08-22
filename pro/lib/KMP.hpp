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
