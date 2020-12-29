#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>
#include <vector>
using namespace std;

class Incasare {
private:
	float inc_bilet;
	float inc_consum;
	float total;

public:
	Incasare() {
		inc_bilet = 0;
		inc_consum = 0;
		total = 0;
	}
};
