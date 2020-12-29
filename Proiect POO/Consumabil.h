#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>
#include <vector>
using namespace std;

class Consumabil {
private:
	int id;
	string nume;
	string um;
	int cant;

public:
	Consumabil() {
		id = 0;
		nume = "";
		um = "";
		cant = 0;
	}
};