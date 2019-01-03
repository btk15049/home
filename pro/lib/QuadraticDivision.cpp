#ifndef VS
#include<bits/stdc++.h>
using namespace std;
#endif

namespace quad{
	constexpr int b = 300;

	inline void baby_update(const int lb, const int ub, const int l, const int r){
		const int block_id = lb / b;
		for(int i = lb; i < ub ; i++){
			if(l<=i&&i<r){
				// inner block

			}
			else{
				// outer block

			}
		}
	}

	inline void giant_update(const int lb, const int ub){
		const int block_id = lb / b;

	}

	void update(const int l, const int r){
		for(int id = (l / b) * b ; id < r ; id+=b){
			if(id < l || r < id + b){
				baby_update(id ,id + b, l, r);
			}
			else{
				giant_update(id, id + b);
			}
		}
	}

	inline void baby_get(const int lb, const int ub, const int l, const int r){
		const int block_id = lb / b;
		for(int i = lb; i < ub ; i++){
			if(l<=i&&i<r){
				// inner block

			}
			else{
				// outer block

			}
		}
	}

	inline void giant_get(const int lb, const int ub){
		const int block_id = lb / b;

	}

	void get(const int l, const int r){
		for(int id = (l / b) * b ; id < r ; id+=b){
			if(id < l || r < id + b){
				baby_get(id ,id + b, l, r);
			}
			else{
				giant_get(id, id + b);
			}
		}
	}
}
