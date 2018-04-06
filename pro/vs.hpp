#pragma once
#define BTK
#define VS

#include<fstream>
#include <intrin.h>
#define _IOSTREAM_

std::ifstream cin("in");
std::ofstream cout("out");
class vs_stdio {
public:
	~vs_stdio(){
		cin.close();
		cout.close();
	}
}vsBTK;

