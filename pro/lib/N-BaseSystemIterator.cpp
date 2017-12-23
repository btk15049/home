#include <bits/stdc++.h>
template <typename ITR>
bool next_value(int base,ITR bg,ITR ed){
    int c=1;
    for(; bg != ed && c==1; ++bg){
        (*bg)+=c;
        if((c = ((*bg) == base)))(*bg)=0;
    }
    return !c;
}
